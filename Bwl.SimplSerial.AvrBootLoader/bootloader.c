#include "cfgs.h"

#include <avr/boot.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/setbaud.h>
#include <util/delay.h>

#define IS_BOOTLOADER
#include "../Bwl.SimplSerial.AvrExampleProgram/libs/bwl_uart.c"
#include "../Bwl.SimplSerial.AvrExampleProgram/libs/bwl_simplserial.c"

#include "../guid"

volatile struct
{
unsigned char dev_prod[16];
unsigned char dev_name[16];
unsigned char dev_guid[16];	
} bootloader=
{
"BwlBootV1.4:    ",
DEV_NAME,
DEV_GUID
};

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

FUSES = FUSES_VALUE;

void sserial_send_start(){TX_START_MACRO}
void sserial_send_end(){TX_END_MACRO}

volatile int bootloader_run_time=0;

void sserial_process_request()
{
	int page=((sserial_request.data[0]<<8)+sserial_request.data[1]);
	long pageaddr=SPM_PAGESIZE*page;
	
	sserial_response.datalength=1;
	sserial_response.data[0]=0;
	sserial_response.result=sserial_request.command+1;
	bootloader_run_time=0;
	
	if (sserial_request.command==100)
	{
		sserial_response.data[16]=SPM_PAGESIZE>>8;
		sserial_response.data[17]=SPM_PAGESIZE&255;
		
		sserial_response.data[18]=0;
		sserial_response.data[19]=(FLASHEND>>8)&255;
		sserial_response.data[20]=FLASHEND&255;
		
		sserial_response.datalength=22;		
		sserial_send_response();
	}

	if (sserial_request.command==102)
	{
		boot_page_erase_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_send_response();
	}
	if (sserial_request.command==104)
	{
		long wordoffset=((sserial_request.data[2]<<8)+sserial_request.data[3]);
		for (byte i=0; i<8; i+=2)
		{
			uint16_t word1=(sserial_request.data[5+i]<<8)+(sserial_request.data[4+i]);
			boot_page_fill_safe(pageaddr+wordoffset+i,word1);
		}
		sserial_send_response();
	}
	if (sserial_request.command==106)
	{
		boot_page_write_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_send_response();
	}
}

void bootloader_run_sometime()
{
	for (byte j=0; j<BOOTLOADER_TIME; j++)
	for (bootloader_run_time=0; bootloader_run_time<10000l; bootloader_run_time++)
	{
		sserial_poll_uart();
		_delay_us(100);
		wdt_reset();
	}
}

void bootloader_run_infinite()
{
	{
		sserial_poll_uart();
		_delay_us(100);
		wdt_reset();
	}while(1);
}

int main(void)
{	
	wdt_enable(WDTO_2S);
	uart_init_withdivider(UBRR_VALUE);
	for (byte i=0; i<16; i++)
	{
		sserial_devname[i]=bootloader.dev_prod[i];
		sserial_devname[16+i]=bootloader.dev_name[i];
		sserial_devguid[i]=bootloader.dev_guid[i];
	}
	bootloader_run_sometime();
	boot_rww_enable_safe();
	GOTO_PROG;
}



