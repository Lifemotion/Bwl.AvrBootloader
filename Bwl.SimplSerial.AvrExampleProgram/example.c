#define BAUD 9600
#define F_CPU 16000000UL
#include <util/setbaud.h>
#include <util/delay.h>

#include "libs/bwl_uart.h"
#include "libs/bwl_simplserial.h"

void sserial_send_start()
{}

void sserial_send_end()
{}
	
void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}


void sserial_process_request()
{
	if (sserial_request.command==1)
	{
		sserial_response.result=0;
		sserial_response.datalength=6;
		sserial_send_response();
	}
}

void poll_uart()
{
	sserial_poll_uart(0);
	#ifdef UDR1
	sserial_poll_uart(1);
	#endif
	#ifdef UDR2
	sserial_poll_uart(2);
	sserial_poll_uart(3);
	#endif
}

void init_uart()
{
	uart_init_withdivider(0,UBRR_VALUE);
	#ifdef UDR1
	uart_init_withdivider(1,UBRR_VALUE);
	#endif
	#ifdef UDR2
	uart_init_withdivider(2,UBRR_VALUE);
	uart_init_withdivider(3,UBRR_VALUE);
	#endif
}

int main(void)
{
	wdt_enable(WDTO_4S);
	sserial_find_bootloader();
	init_uart();
	while(1)
	{
		poll_uart();
		wdt_reset();
	}
}