--PORTUGU�S--

*DECIS�ES ESTRUTURAIS*
- Projetar e montar um ventilator de baixo custo (pre�o limite US$500,00)
- Usar pe�as e engenharia acessiveis a todos
- Manter a simplicidade como uma filosofia para todos
- N�o confiar em um �nico hardware ou dispositivo, pensar na modularidade como algo essencial, nem todos tem acesso as mesmas coisas.
- A escala do projeto demanda que um n�mero aproximado de 3Mi de aparelhos sejam construidos mundialmente nos pr�ximos meses


*REQUISITOS T�CNICOS*
- Projetar um Produto Minimamente Vi�vel que:
- Tenha um fole como dispositivo de bombeamento de ar, pensamos em materiais de f�cil disponibilidade como camaras de pneus.
- Utilizar pe�as comumente achadas na industria automotiva como motores de limpa-parabrisa
- Considerar que 12V � uma realidade visto que talvez estes respiradores precisem funcionar sem energia AC
- Um paciente cr�tico n�o poder� sofrer Bronco-trauma, portanto o desenvolvimento de um sensor integrado ao circuito eletr�nico que previna este tipo de problemas
- Sistema de filtragem na exaust�o para minimizar o cont�gio da doen�a em ambientes hospitalares
- Sistema de humidifica��o da admiss�o de ar a fim de n�o ressecar as vias respirat�rias
- Ajuste proporcional de 1/1 at� 1/6 no tempo de ventila��o entre inspira��o e expira��o
- Ajuste volum�trico de ventila��o para pacientes com diferentes capacidades respirat�rias. Considerar at� 2N/m como torque para ventilar alguem com 120Kg
- Limite m�ximo de ventila��o de 1,6L


*MODELAGEM DA MVP*
- Motor de LimpaParabrisa 12V
- Camara de Pneu para montagem do Fole
- Uso de barras roscadas na estrutura rigida da arma��o
- Uso de Acr�lico ou outros materiais de f�cil limpeza (preferencialmente Inox por�m n�o exlusivo dado o grau de emerg�ncia)
- Controle Electronico com Arduino (estudando a viabilidade da simplifica��o eletr�nica)
- Sensor de press�o no Intake (vendo a viabilidade de venturi ou BMP120)
- Uso de filtro de exaust�o de Oz�nio e HEPA E13 para filtragem de particulas at� 1�m poss�vel adapta��o de luz UV para aniquila��o biol�gica
- Constru��o de valvulas PEEP e Venturi com impressora 3D, estudando a possibilidade de encontrar parceiro industrial que viavilize a inje��o pl�stica para maior velocidade de produ��o


-- ENGLISH --

*STRUCTURAL DESIGNS*
- Design and assemble a low cost ventilator (limit price US $ 500.00)
- Use parts and engineering accessible to everyone
- Maintaining simplicity as a philosophy for everyone
- Do not rely on a single hardware or device, think of modularity as essential, not everyone has access to the same things.
- The scale of the project demands that an approximate number of 3Mi devices be built worldwide in the coming months

*TECHNICAL REQUIREMENTS*
- Design a Minimally Viable Product that:
- Have a bellows as an air pumping device, we think of easily available materials like tire chambers.
- Use parts commonly found in the automotive industry such as wiper motors
- Consider that 12V is a reality as these respirators may need to work without AC power
- A critical patient must not suffer Bronco-trauma, so the development of a sensor integrated in the electronic circuit that prevents this type of problems
- Exhaust filtering system to minimize the spread of disease in hospital environments
- Air intake humidification system in order not to dry out the airways
- Proportional adjustment from 1/1 to 1/6 in the ventilation time between inspiration and expiration
- Volumetric ventilation adjustment for patients with different breathing capacities. Consider up to 2N / m as torque to ventilate someone with 120Kg
- Maximum ventilation limit of 1.6L
- Considering 10 ~ 30 breathing cycles a minute

*MVP MODELING*
- Windshield Wiper Motor 12V
- Tire Chamber for Assembly of Bellows
- Use of threaded bars in the rigid frame structure
- Use of Acrylic or other materials for easy cleaning (preferably stainless steel but not exclusive given the degree of emergence)
- Electronic Control with Arduino (studying the feasibility of electronic simplification)
- Intake pressure sensor (seeing the viability of venturi or BMP120)
- Use of ozone and HEPA E13 exhaust filter to filter particles up to 1�m possible adaptation of UV light for biological annihilation
- Construction of PEEP and Venturi valves with 3D printer, studying the possibility of finding an industrial partner that makes plastic injection viable for greater production speed