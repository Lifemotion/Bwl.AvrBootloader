#ifdef CFG_TESTPLATFORM_ONE
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 3
	#define DEV_NAME "BwlTestPl1.0"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for Bwl.TestPlatform.One, 16MHz, 9.6kHz, 3 sec"
	#ifndef __AVR_ATmega328P__
	#error "Wrong part"
	#endif
#endif

#ifdef CFG_CFMODEM_03
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 30
	#define DEV_NAME "CfRFM69-03"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for Cf_Modem_03 (RFM69HW), 16MHz, 9.6kHz, 30 sec"
	#ifndef __AVR_ATmega328P__
	#error "Wrong part"
	#endif
#endif

#ifdef CFG_ARDUINO_328P
	#define F_CPU 16000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 3
	#define DEV_NAME "Arduino328P"
	#define TX_START_MACRO 	{}
	#define TX_END_MACRO 	{}
	#pragma message "Loader for Arduino Nano 328P, 16MHz, 9.6kHz, 3 sec"
	#ifndef __AVR_ATmega328P__
		#error "Wrong part"
	#endif
#endif

#ifdef CFG_TRAFFICLIGHT_ONE
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 20
	#define DEV_NAME "CfTrafLight1.0"
	#define TX_START_MACRO 	DDRD|=(1<<2);PORTD|=(1<<2);
	#define TX_END_MACRO 	DDRD|=(1<<2);PORTD&=(~(1<<2));
	#pragma message "Loader for Cleverflow TrafficLight 1.0, 8MHz, 9.6kHz, 20 sec"
	#ifndef __AVR_ATmega168PA__
	#error "Wrong part"
	#endif
#endif

#ifdef CFG_GENERIC_AVR_PCB
	#define F_CPU 8000000UL
	#define BAUD 9600
	#define BOOTLOADER_TIME 10
	#define DEV_NAME "GenAvrPcb10.14"
	#define TX_START_MACRO 	DDRB|=(1<<5);PORTB|=(1<<5);
	#define TX_END_MACRO 	DDRB|=(1<<5);PORTB&=(~(1<<5));
	#pragma message "Loader for Bwl Genereic AVR PCB with USB 10.2014, 8MHz, 9.6kHz, 20 sec"
	#ifndef __AVR_ATmega168PA__
	#error "Wrong part"
	#endif
#endif
