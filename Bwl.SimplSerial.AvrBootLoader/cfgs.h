#undef __AVR_ATmega168PA__
#undef __AVR_ATmega328P__
#undef __AVR_ATmega88PA__
#undef __AVR_ATmega324PA__
#undef __AVR_ATmega2560__

#ifdef CFG_TESTPLATFORM_ONE
	#define CFG CFG_TESTPLATFORM_ONE
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 3
	#define DEV_NAME "BwlTestPl1.1*8"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for Bwl.TestPlatform.One, 8MHz, 9.6kHz, 3 sec"
	#define __AVR_ATmega328P__
	#define FUSES_VALUE  { 0xDC, 0xCA , 0xFD, }// low high extended
#endif

#ifdef CFG_CFMODEM_03
	#define CFG CFG_CFMODEM_03
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 30
	#define DEV_NAME "CfRFM69-03"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#define FUSES_VALUE  { 0xDC, 0xCA , 0xFD, }// low high extended
	#pragma message "Loader for Cf_Modem_03 (RFM69HW), 16MHz, 9.6kHz, 30 sec"
	#define __AVR_ATmega328P__
#endif

#ifdef CFG_ARDUINO_328P
	#define CFG CFG_ARDUINO_328P
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 3
	#define DEV_NAME "Arduino328P"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for Arduino Nano 328P, 16MHz, 9.6kHz, 3 sec"
	#define __AVR_ATmega328P__
	#define FUSES_VALUE  { 0xDC, 0xCA , 0xFD, }// low high extended
#endif

#ifdef CFG_TRAFFICLIGHT_ONE
	#define CFG CFG_TRAFFICLIGHT_ONE
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 5
	#define DEV_NAME "CfTrafLight1.2"
	#define TX_START_MACRO 	DDRD|=(1<<2);PORTD|=(1<<2);
	#define TX_END_MACRO 	DDRD|=(1<<2);PORTD&=(~(1<<2));
    #define FUSES_VALUE  { 0xFD, 0xCD , 0xF8, }// low high extended	BOOTSZ = 1024W_1C00
	#pragma message "Loader for Cleverflow TrafficLight 1.1, 8MHz, 9.6kHz, 5 sec"
	#define __AVR_ATmega168PA__
#endif

#ifdef CFG_GENERIC_AVR_PCB
	#define CFG CFG_GENERIC_AVR_PCB
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "GenAvrPcb10.14"
	#define TX_START_MACRO 	DDRB|=(1<<5);PORTB|=(1<<5);
	#define TX_END_MACRO 	DDRB|=(1<<5);PORTB&=(~(1<<5));
    #define FUSES_VALUE  { 0xFD, 0xCD , 0xF8, }// low high extended
	#pragma message "Loader for Bwl Genereic AVR PCB with USB 10.2014, 8MHz, 9.6kHz, 10 sec"
	#define __AVR_ATmega168PA__
#endif

#ifdef CFG_GENERIC_AVR_PCB_M328
	#define CFG CFG_GENERIC_AVR_PCB
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "GenAvrPcb04.15"
	#define TX_START_MACRO 	DDRB|=(1<<5);PORTB|=(1<<5);
	#define TX_END_MACRO 	DDRB|=(1<<5);PORTB&=(~(1<<5));
	#define FUSES_VALUE   {0xDC, 0xCA , 0xFD, }// low high extended
	#pragma message "Loader for Bwl Genereic AVR PCB (mega328) with USB 04.2015, 8MHz, 9.6kHz, 10 sec"
	#define __AVR_ATmega328P__
#endif

#ifdef CFG_GENERIC_AVR_PCB_OLD
	#define __AVR_ATmega88PA__
	#define CFG CFG_GENERIC_AVR_PCB_OLD
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "GenAvrPcbOLD"
	#define TX_START_MACRO 	DDRB|=(1<<5);PORTB|=(1<<5);
	#define TX_END_MACRO 	DDRB|=(1<<5);PORTB&=(~(1<<5));
	#define FUSES_VALUE   {0xDC,0xCD,0xF9 }// low high extended
	#pragma message "Loader for OLD !!! Bwl Genereic AVR PCB with ??.201?, 8MHz, 9.6kHz, 20 sec"
#endif

#ifdef CFG_HITONWIRE_2013
	#define __AVR_ATmega88PA__
	#define CFG CFG_HITONWIRE_2013
	#define F_CPU 4000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "Cf.HitonWire1.0"
	#define TX_START_MACRO 	DDRD|=(1<<2);PORTD|=(1<<2);
	#define TX_END_MACRO 	DDRD|=(1<<2);PORTD&=(~(1<<2));
	#define FUSES_VALUE   {0xDC,0xCD,0xF8 }// low high extended
	#pragma message "Loader for Cf.HitonWire1.0 (Cf.MD2.r2) 05.2013, ATMega88PA 4MHz, 9.6kHz, 10 sec"
#endif

#ifdef CFG_M324_GENERIC
	#define __AVR_ATmega324PA__
	#define CFG CFG_M324_GENERIC
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "Mega324-8MHz"
	#define TX_START_MACRO 	{};
	#define TX_END_MACRO 	{};
	#define FUSES_VALUE   {0xDE,0x92,0xFD }// low high extended
	#pragma message "Loader for generic ATMega328PA 8MHz, 9.6kHz, 10 sec"
#endif

#ifdef CFG_M324_GENERIC_16MHZ
	#define __AVR_ATmega324PA__
	#define CFG CFG_M324_GENERIC_16MHZ
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "Mega324-16MHz"
	#define TX_START_MACRO 	{};
	#define TX_END_MACRO 	{};
	#define FUSES_VALUE   {0xDE,0x92,0xFD }// low high extended
	#pragma message "Loader for generic ATMega328PA 16MHz, 9.6kHz, 10 sec"
#endif

#ifdef CFG_M2560_GENERIC
	#define __AVR_ATmega2560__
	#define CFG CFG_M2560_GENERIC
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "Mega2560-8MHz"
	#define TX_START_MACRO 	{};
	#define TX_END_MACRO 	{};
	#define FUSES_VALUE   {0xDE,0x92,0xFD }// low high extended
	#pragma message "Loader for generic ATMega2560 8MHz, 9.6kHz, 10 sec"
#endif

#ifndef	CFG
#pragma message "No configuration defined! Select one in project configuration manager and\or define new in cfgs.h"
#endif
