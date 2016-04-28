/*
 * Bwl SimplSerial Lib
 *
 * Author: Igor Koshelev 
 * Licensed: open-source Apache license
 *
 * Version: 27.04.2016 V1.3.2 (single-port)
 */ 

#ifndef BWL_GAPUART_H_
#define BWL_GAPUART_H_

#include <util/crc16.h>
#include <avr/wdt.h>

typedef unsigned char byte;

byte sserial_devguid[16];
byte sserial_devname[32];
byte sserial_bootname[16];
byte sserial_bootloader_present;
uint16_t sserial_address;

#define SSERIAL_VERSION "V1.3.2"
#define CATUART_MAX_PACKET_LENGTH 128

struct
{
	uint16_t		 address_to;
	unsigned	char command;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	int datalength;	
} sserial_request;

struct
{
	unsigned	char result;
	unsigned	char data[CATUART_MAX_PACKET_LENGTH];
	unsigned	int datalength;
} sserial_response;

//должны быть реализованы
extern void sserial_send_start();
extern void sserial_send_end();
extern void sserial_process_request();
void uart_send( unsigned char);
unsigned char uart_get( void );
unsigned char uart_received( void );
void var_delay_ms(int ms);
/*
void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}
*/

//вызывать
void sserial_poll_uart();
void sserial_send_response();
void sserial_find_bootloader();
void sserial_append_devname(byte startIndex, byte length, char* newname);

#endif /* BWL_GAPUART_H_ */

#if defined(__AVR_ATmega88PA__)
#define GOTO_PROG 	{boot_rww_enable_safe(); asm("ldi r30,0"); asm("ldi r31,0"); asm("ijmp");};
#define GOTO_BOOT 	asm volatile("rjmp 0x1800"::);
#endif

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#define GOTO_PROG 	asm volatile("jmp 0x0000"::);
#define GOTO_BOOT 	asm volatile("jmp 0x7800"::);
#endif

#if  defined(__AVR_ATmega168PA__)
#define GOTO_PROG 	asm volatile("jmp 0x0000"::);
#define GOTO_BOOT 	asm volatile("jmp 0x3800"::);
#endif

#if defined(__AVR_ATmega324PA__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324A__)
#define GOTO_PROG 	asm volatile("jmp 0x0000"::);
#define GOTO_BOOT 	asm volatile("jmp 0x7800"::);
#endif

#if defined(__AVR_ATmega2560__)
#define GOTO_PROG 	asm volatile("jmp 0x00000"::);
#define GOTO_BOOT 	asm volatile("jmp 0x3F000"::);
#endif