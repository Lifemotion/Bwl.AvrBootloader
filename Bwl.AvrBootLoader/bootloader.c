

#include "cfgs.h"

#include <avr/boot.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/setbaud.h>
#include <util/delay.h>

#include "libs/bwl_uart.c"
#include "libs/bwl_simplserial.c"

#include "../guid"

volatile struct
{
unsigned char dev_prod[16];
unsigned char dev_name[16];
unsigned char dev_guid[16];	
} bootloader=
{
"BwlBootV1.1:    ",
DEV_NAME,
DEV_GUID
};

#if defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)|| defined(__AVR_ATmega168PA__)
#else
#error "Device not suppoted"
#endif

FUSES = FUSES_VALUE;

void sserial_send_start()
{
	TX_START_MACRO
}

void sserial_send_end()
{
	TX_END_MACRO
}

volatile int bootloader_run_time=0;

void bootloader_jump_to_main()
{
	//boot_rww_enable_safe	();
	boot_spm_busy_wait ();
	asm volatile("jmp 0x0000"::);
}

void sserial_process_request()
{
	if (sserial_request.command==100)
	{
		sserial_response.result=101;
		
		/*sserial_response.data[1]='B';
		sserial_response.data[2]='w';
		sserial_response.data[3]='l';
		sserial_response.data[4]='L';
		sserial_response.data[5]='d';
		sserial_response.data[6]='r';*/
		#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
		/*		sserial_response.data[11]=boot_signature_byte_get(0);
				sserial_response.data[13]=boot_signature_byte_get(2);
				sserial_response.data[15]=boot_signature_byte_get(4);*/
		#endif
		sserial_response.data[21]=__fuse.low;

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
		int page=((sserial_request.data[0]<<8)+sserial_request.data[1]);
		long pageaddr=SPM_PAGESIZE*page;
		boot_page_erase_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_response.result=103;
		sserial_response.datalength=1;
		sserial_response.data[0]=0;
		bootloader_run_time=0;
		sserial_send_response();
	}
	if (sserial_request.command==104)
	{
		int page=((sserial_request.data[0]<<8)+sserial_request.data[1]);
		long pageaddr=SPM_PAGESIZE*page;
		long wordoffset=((sserial_request.data[2]<<8)+sserial_request.data[3]);
		for (byte i=0; i<8; i+=2)
		{
			uint16_t word1=(sserial_request.data[5+i]<<8)+(sserial_request.data[4+i]);
			boot_page_fill_safe(pageaddr+wordoffset+i,word1);
		}
		sserial_response.result=105;
		sserial_response.datalength=1;
		sserial_response.data[0]=0;
		bootloader_run_time=0;
		sserial_send_response();
	}
	if (sserial_request.command==106)
	{
		int page=((sserial_request.data[0]<<8)+sserial_request.data[1]);
		long pageaddr=SPM_PAGESIZE*page;
		boot_page_write_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_response.result=107;
		sserial_response.datalength=1;
		sserial_response.data[0]=0;
		bootloader_run_time=0;
		sserial_send_response();
	}
}

void bootloader_run_sometime()
{
	for (int j=0; j<BOOTLOADER_TIME; j++)
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

void bootloader_init()
{
	wdt_enable(WDTO_2S);
	uart_init_withdivider(UBRR_VALUE);
}

int main(void)
{	
	bootloader_init();	
	//while(1) uart_send(1);
	for (byte i=0; i<16; i++)
	{
		sserial_devname[i]=bootloader.dev_prod[i];
	}
	for (byte i=0; i<16; i++)
	{
		sserial_devname[12+i]=bootloader.dev_name[i];
		sserial_devguid[i]=bootloader.dev_guid[i];
	}

	bootloader_run_sometime();
	bootloader_jump_to_main();
}



