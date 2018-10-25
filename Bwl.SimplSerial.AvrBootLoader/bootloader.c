#include <avr/boot.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
	"BwlBootV1.7:   ",
	DEV_NAME,
	DEV_GUID
};

void var_delay_ms(int ms)
{
	for (int i=0; i<ms; i++)_delay_ms(1.0);
}

FUSES = FUSES_VALUE;

void sserial_send_start(unsigned char portindex){TX_START_MACRO}
void sserial_send_end(unsigned char portindex){TX_END_MACRO}

volatile int bootloader_run_time=0;

void sserial_process_request(unsigned char portindex)
{
	int page=((sserial_request.data[0]<<8)+sserial_request.data[1]);
	long pageaddr=SPM_PAGESIZE*page;
	
	sserial_response.datalength=1;
	sserial_response.data[0]=0;
	sserial_response.result=sserial_request.command+1;
	
	if (sserial_request.command==100)
	{
		bootloader_run_time=0;
		/*sserial_response.data[0]=boot_signature_byte_get(0);
		sserial_response.data[1]=boot_signature_byte_get(2);
		sserial_response.data[2]=boot_signature_byte_get(4);
		
		sserial_response.data[3]=boot_lock_fuse_bits_get(0);
		sserial_response.data[4]=boot_lock_fuse_bits_get(1);
		sserial_response.data[5]=boot_lock_fuse_bits_get(2);
		sserial_response.data[6]=boot_lock_fuse_bits_get(3);*/
		
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
		bootloader_run_time=0;
		boot_page_erase_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_send_response();
	}

	if (sserial_request.command==104)
	{
		bootloader_run_time=0;
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
		bootloader_run_time=0;
		boot_page_write_safe(pageaddr);
		boot_spm_busy_wait ();
		sserial_send_response();
	}

/*
#if SPM_PAGESIZE==128
#warning 128
#endif 
#if SPM_PAGESIZE==256
#warning 256
#endif
#if FLASHEND==0x7FFF
#warning 0x7FFF
#endif
*/
 
	//fastmode erase all
	if (sserial_request.command==110)
	{
		bootloader_run_time=0;
		for (long i=0; i<FLASHEND-4096; i+=SPM_PAGESIZE)
		{
			wdt_reset();
			boot_page_erase_safe(i);
		}
		boot_spm_busy_wait ();
		sserial_send_response();
	}
	//fast mode fill
	if (sserial_request.command==108)
	{
		bootloader_run_time=0;
		long wordoffset=((sserial_request.data[2]<<8)+sserial_request.data[3]);
		for (byte i=0; i<sserial_request.datalength-4; i+=2)
		{
			uint16_t word1=(sserial_request.data[5+i]<<8)+(sserial_request.data[4+i]);
			boot_page_fill_safe(pageaddr+wordoffset+i,word1);
		}
		sserial_send_response();
	}
}

void bootloader_poll_uart()
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
 
void bootloader_init_uart()
{
	uart_init_withdivider_x2(0,GET_UBRR_X2(F_CPU, BAUD));
	#ifdef UDR1
	uart_init_withdivider_x2(1,GET_UBRR_X2(F_CPU, BAUD));
	#endif
	#ifdef UDR2
	uart_init_withdivider_x2(2,GET_UBRR_X2(F_CPU, BAUD));
	uart_init_withdivider_x2(3,GET_UBRR_X2(F_CPU, BAUD));
	#endif
}

void bootloader_run_sometime()
{
	for (bootloader_run_time=0; bootloader_run_time<BOOTLOADER_TIME; bootloader_run_time++)
	for (int j=0; j<10000l; j++)
	{
		bootloader_poll_uart();
		_delay_us(100);
		wdt_reset();
	}
}

void bootloader_run_infinite()
{
	{
		bootloader_poll_uart();
		_delay_us(100);
		wdt_reset();
	}while(1);
}

int main(void)
{
	cli();
	wdt_enable(WDTO_8S);
	bootloader_init_uart();
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



