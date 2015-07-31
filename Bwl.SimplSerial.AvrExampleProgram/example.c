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

int main(void)
{
	wdt_enable(WDTO_4S);
	sserial_find_bootloader();
	uart_init_withdivider(UBRR_VALUE);
	while(1)
	{
		sserial_poll_uart();
		wdt_reset();
	}
}