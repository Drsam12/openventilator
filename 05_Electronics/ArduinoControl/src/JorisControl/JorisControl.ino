/*
Copyright (c) 2020, Joris Robijn
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following condition is met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "RotaryEncoder.h"
#include "VerticalGraph.h"
#include "RespirationAnalysis.h"
#include "CircularBuffer.h"
#include "ADCReader.h"
#include "KeyScanner.h"
#include "MainScreen.h"
#include "MenuScreen.h"
#include "MemoryFree.h"


/*
Timer output  Arduino output  Chip pin  Pin name
OC0A  6 12  PD6
OC0B  5 11  PD5
OC1A  9 15  PB1
OC1B  10  16  PB2
OC2A  11  17  PB3
OC2B  3 5 PD3

https://etechnophiles.com/change-frequency-pwm-pins-arduino-uno/
TCCR0B = TCCR0B & B11111000 | B00000011; // for PWM frequency of 976.56 Hz (The DEFAULT) Needed for millis to work correctly!
TCCR1B = TCCR1B & B11111000 | B00000011; // for PWM frequency of 490.20 Hz (The DEFAULT)
TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
*/

#define DOUT_LCD_EN 9
#define DOUT_LCD_RS 8
#define DOUT_LCD_DB4 7
#define DOUT_LCD_DB5 6
#define DOUT_LCD_DB6 5
#define DOUT_LCD_DB7 4
#define DIN_ROTENC_A 2  // Needs to be on this pin because it needs interrupt on change
#define DIN_ROTENC_B 3  // Needs to be on this pin because it needs interrupt on change
#define DOUT_KEYS_X0 8   // These key pins are shared with the LCD
#define DOUT_KEYS_X1 7   // On all of them, a diode needs to be connected with 
#define DOUT_KEYS_X2 6   // the cathode towards the pin, and the anode towards
#define DOUT_KEYS_X3 5   // the switch and then the KEYS_Y0 pin.
#define DOUT_KEYS_X4 4
#define DIN_KEYS_Y0 10  // This pin reads the key status. It is internally pulled up.
#define DOUT_MOTOR_PWM 11 // This PWM pin is on Timer 2
#define DIN_MOTOR_PARK 12
#define DOUT_BUZZER 13

#define AIN_VSUPPLY A0
#define AIN_IMOTOR A1
#define AIN_LUNGPRES A2
#define AIN_LUNGFLOW A3 // Differential pressure to detect flow

// Free pins: A4 (=SDA) and A5 (=SCK)

LiquidCrystal lcd( DOUT_LCD_RS, DOUT_LCD_EN, DOUT_LCD_DB4, DOUT_LCD_DB5, DOUT_LCD_DB6, DOUT_LCD_DB7 );
RotaryEncoder rotEnc( DIN_ROTENC_A, DIN_ROTENC_B ); 
VerticalGraph vgraph;
CircularBuffer circBuf;
RespirationAnalysis an;
byte ADCPins[4] = { AIN_VSUPPLY, AIN_IMOTOR, AIN_LUNGPRES, AIN_LUNGFLOW };
//ADCReader ADCR( 4, ADCPins );
ADCReader ADCR( AIN_LUNGPRES );

#define VSUPPLYRATIO ((20/3)+1) // 20k and 3k resistor

uint8_t X_pinList[] = {10};
uint8_t Y_pinList[] = {};
Key directKeyList[] = {KEY_ENTER};
Key matrixKeyList[] = {};
KeyScanner keySc( 1, 0, X_pinList, Y_pinList, directKeyList, matrixKeyList );

void setup() {
  // put your setup code here, to run once:
  Serial.begin( 115200 );
  if( circBuf.init( 2, 40 ) != 0 ) {
    Serial.println( "Buffer allocation failed" );
  }
  ADCR.init( 500 ); // This sets averaging. On Arduino Uno (on 16 MHz), you will get 250 samples per 13 seconds (sorry I couldn't get a nicer fraction). That's one every 52 ms exactly.
  keySc.init();
  lcd.begin( 20, 4 );
  lcd.noAutoscroll();
  rotEnc.init();
  vgraph.prepare();
  switchScreen( mainScreen );

  Serial.print( freeMemory() );
  Serial.println( F(" bytes free") );
}

void loop() {

  float VA0, p0;

  // The timing of this loop has to be based on the availability of data. Each cycle should not take longer than the sample time (which actually is an averaged sample).
  while( !ADCR.isSampleReady() ) // this also works on carry-over
    delay( 1 );
  
  long t = millis();
  long s = ADCR.getSample();
  
  VA0 = 0.004883 * s / ADCR.getAveraging();
  p0 = (VA0 - 0.2) / 0.04413;

  Serial.print( "p0=" );
  Serial.println( p0 );

  float row[2];
  row[0] = t;
  row[1] = p0;
  int ar = circBuf.appendRow( row );

  measValues[M_p] = p0;
  //flow = values[M_Q];
  //measValues[M_Vsup] = p0;
  //measValues[M_Vmot = p0;
  //measValues[M_Imot] = p0;
  //measValues[M_Pmot] = measValues[V_Vmot] * measValues[V_Imot];

  //an.processData( p0, 0 );

  measValues[M_pMax] = an.getPP();
  measValues[M_PEEP] = an.getPEEP();
  measValues[M_RR] = an.getRR();
  measValues[M_EI] = an.getEI();

  activeScreen->process();
  activeScreen->draw();
}
