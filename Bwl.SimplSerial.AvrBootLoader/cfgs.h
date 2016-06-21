#undef __AVR_ATmega168PA__
#undef __AVR_ATmega328P__
#undef __AVR_ATmega88PA__
#undef __AVR_ATmega324PA__
#undef __AVR_ATmega324A__
#undef __AVR_ATmega324P__
#undef __AVR_ATmega324__
#undef __AVR_ATmega2560__

#ifdef CFG_M328_GENERIC
	#define CFG CFG_M328_GENERIC
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 3
	#define DEV_NAME "ATMega328P"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for ATMega328P or Arduino Nano 328P, 16MHz, 9.6kHz, 3 sec"
	#define __AVR_ATmega328P__
	#define FUSES_VALUE  { 0xDE, 0xC0 , 0xDD, }// low high extended
		//BODLEVEL = 2V7
		//WDTON = [X]
		//EESAVE = [X]
		//BOOTSZ = 2048W_3800
		//BOOTRST = [X]
		//CKDIV8 = [ ]
		//SUT_CKSEL = EXTXOSC_8MHZ_XX_258CK_14CK_65MS
#endif

#ifdef CFG_GENERIC_AVR_PCB_M328
	#define CFG CFG_GENERIC_AVR_PCB
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "GenAvrPcb04.15"
	#define TX_START_MACRO 	DDRB|=(1<<5);PORTB|=(1<<5);
	#define TX_END_MACRO 	DDRB|=(1<<5);PORTB&=(~(1<<5));
	#define FUSES_VALUE  { 0xDE, 0xC0 , 0xDD, }// low high extended
	#pragma message "Loader for Bwl Genereic AVR PCB (mega328) with USB 04.2015, 8MHz, 9.6kHz, 10 sec"
	#define __AVR_ATmega328P__
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
	#define FUSES_VALUE   {0xDE,0x88,0xFD }// low high extended
	#pragma message "Loader for generic ATMega328PA 8MHz, 9.6kHz, 10 sec"
	//BODLEVEL = 2V7
	//JTAGEN = [X]
	//WDTON = [X]
	//EESAVE = [X]
	//BOOTSZ = 2048W_3800
	//BOOTRST = [X]
	//CKDIV8 = [ ]
	//SUT_CKSEL = EXTXOSC_8MHZ_XX_258CK_65MS
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
	#define FUSES_VALUE   {0xDE,0x88,0xFD }// low high extended
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
	#define FUSES_VALUE   {0xDE,0x82,0xFD }// low high extended
	#pragma message "Loader for generic ATMega2560 8MHz, 9.6kHz, 10 sec"
	//BODLEVEL = 2V7
	//JTAGEN = [X]
	//WDTON = [X]
	//EESAVE = [X]
	//BOOTSZ = 2048W_1F800
	//BOOTRST = [X]
	//SUT_CKSEL = EXTXOSC_8MHZ_XX_258CK_65MS
#endif

#ifdef CFG_M2560_GENERIC_16MHZ
	#define __AVR_ATmega2560__
	#define CFG CFG_M2560_GENERIC
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "Mega2560-16MHz"
	#define TX_START_MACRO 	{};
	#define TX_END_MACRO 	{};
	#define FUSES_VALUE   {0xDE,0x82,0xFD }// low high extended
	#pragma message "Loader for generic ATMega2560 16MHz, 9.6kHz, 10 sec"
	//BODLEVEL = 2V7
	//JTAGEN = [X]
	//WDTON = [X]
	//EESAVE = [X]
	//BOOTSZ = 2048W_1F800
	//BOOTRST = [X]
	//SUT_CKSEL = EXTXOSC_8MHZ_XX_258CK_65MS
#endif

#define UART_INDEX_0 0

#ifndef	CFG
#pragma message "No configuration defined! Select one in project configuration manager and\or define new in cfgs.h"
#endif
