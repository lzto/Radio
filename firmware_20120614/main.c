#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

#include <stdio.h>
#include <string.h>

#include "requests.h"

#include "usbdrv/usbdrv.h"
#include "usbdrv/oddebug.h"

#include "tea5767.h"
#include "lcd1602.h"

////////////////////////////////////////////////////
//EEPROM Area
//eeprom layout
//Byte:
//0:RADIO_MODE:JAP or USA
//1:Freq
//2:Freq
//3:Freq
//4:Freq
//5:BACKLIGHT_STATE
uint8_t EEMEM eprom_country = 0;
uint32_t EEMEM eprom_freq = 88700;
//uint8_t EEMEM eprom_blstate = 1;
///////////////////////////////////////////////////


enum MODE{READY,GETFREQ,STEP,SETFREQ} mode;

long freq;

char rx_signal_power = 0xFF;
unsigned char count = 0x00;
//////////////////////////////////
#define FLAG_BL 0x80
#define FLAG_LCD_FREQ 0x40
#define FLAG_LCD_RXPWR 0x20
#define FLAG_TEASET 0x10

unsigned char flag = 0xF0;
//1 1 1 1    0 0 0 0
//|-LCD_BL 1-on 0-off
//  |-UPDATE_FREQ 1-update
//    |-UPDATE_RX_POWER 1-update
//      |-TEA5767-UPDATE_FREQ
//      -------------
//           |-UNDEF
//             |-UNDEF
//               |-UNDEF
//                 |-UNDEF
////////////////////////////////////
char buff[32];

#define SLOGEN1 "OpenWave Radio\0"
#define SLOGEN2 "Initialized.\0"

PROGMEM const char usbHidReportDescriptor[22] = {    /* USB report descriptor */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Generic Desktop)
    0x09, 0x01,                    // USAGE (Vendor Usage 1)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x09, 0x00,                    //   USAGE (Undefined)
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)
    0xc0                           // END_COLLECTION
};

uchar usbFunctionWrite(uchar *data, uchar len)//read data from host
{
	if(mode==SETFREQ)
	{
		memcpy(buff+count+23,data,len);
		count+=len;

		if(len>=4)
		{
			memcpy(&freq,buff+23,4);
			flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);//update everything
			mode = READY;
			count = 0;
			return 1;
		}
		return 0;
	}
	return 1;
}


usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;
	if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR)
	{
		if(rq->bRequest == CUSTOM_RQ_SET_STATUS)
		{
			mode = STEP;
			if(rq->wValue.bytes[0] & 1)
			{//freq+
				freq+=100;
				flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);//update everything
			}else
			{//freq-
				freq-=100;
				flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);//update everything
			}
			return 0;
		}else if(rq->bRequest == CUSTOM_RQ_GET_STATUS)
		{
			mode = GETFREQ;
			static unsigned char dataBuffer[5];     /* buffer must stay valid when usbFunctionSetup returns */
			memcpy(dataBuffer,&freq,4);
			dataBuffer[4] = rx_signal_power;
			usbMsgPtr = dataBuffer;         /* tell the driver which data to return */
			return 5;                       /* tell the driver to send 1 byte */
		}
	}else if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
	{
		/* calss requests USBRQ_HID_GET_REPORT and USBRQ_HID_SET_REPORT*/
		if(rq->bRequest == CUSTOM_RQ_SET_FREQ)
		{
			count = 0;
			mode=SETFREQ;//call usbFunctionWrite
			return USB_NO_MSG;
		}
	}
	return 0;   /* default for not implemented requests: return no data back to host */
}

void ShowFreq()
{
	sprintf(buff,"%d.%d MHz        ",(int)(freq/100)/10,(int)(freq/100)%10);
	buff[16]=0;
	lcd_1602_write_string((unsigned char)0x00,(unsigned char)0x00,buff);
}

void ShowSignalQuality()
{
	sprintf(buff,"Signal : %d      ",rx_signal_power);
	buff[16]=0;
	lcd_1602_write_string((unsigned char)0x00,(unsigned char)0x01,buff);
}

void system_init()
{
	lcd_1602_init();
	//CLRBIT(LCD_BL_PORT,LCD_BL);
	//Buttons
	PORTB |= ((1<<PB1)|(1<<PB2));//PB1 and PB2
	DDRB |= ((1<<PB1)|(1<<PB2));//PB1 and PB2
	eeprom_read_block((void*)&freq,(const void*)&eprom_freq,4);
	/*if(eeprom_read_byte(&eprom_blstate)==0)
	{
		flag &=~FLAG_BL;
	}*/
}

void main() __attribute__ ((noreturn));
void main()
{
	unsigned int time_cnt = 0;
	unsigned char key_cnt = 256;
	unsigned char key_cnt_l = 0;
	system_init();

	wdt_enable(WDTO_1S);

	usbInit();
	usbDeviceDisconnect();

	_delay_ms(key_cnt);
	
//////////
	TEA5767_INIT(eeprom_read_byte(&eprom_country));
	//TEA5767_INIT(0x01);

	mode = READY;
 	usbDeviceConnect();

	sei();
	
	for(;;)
	{
		wdt_reset();
		usbPoll();
		time_cnt++;
		if(time_cnt<490)
		{
			//LCD Backlight
			if(flag & FLAG_BL)
			{
				//ON
				CLRBIT(LCD_BL_PORT,LCD_BL);
			}else
			{
				//OFF
				SETBIT(LCD_BL_PORT,LCD_BL);
			}
		}else if(time_cnt<1000)
		{
			//update tea5767 module
			if(flag & FLAG_TEASET)
			{
				set_frequency(freq);
				eeprom_update_block ((const void*)&freq,(void*)&eprom_freq,4);
				flag &= ~FLAG_TEASET;
			}
		}else if(time_cnt<1510)
		{
			//update lcd_freq
			if(flag & FLAG_LCD_FREQ)
			{
				ShowFreq();
				flag &= ~FLAG_LCD_FREQ;
			}
		}else if(time_cnt<1600)
		{	//update lcd_rx_power
			if(flag & FLAG_LCD_RXPWR)
			{
				read5767((unsigned char*)buff+27);
				rx_signal_power = (buff[3+27]>>4)&0x0F;
				ShowSignalQuality();
				flag &= ~FLAG_LCD_RXPWR;
			}
		}else
		{
			//Buttons
			if((PINB&(1<<PB1))==0x00)//PB1 freq+
			{
				key_cnt++;
				if(key_cnt>12)
				{
					freq+=100;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
					key_cnt = 0;
					key_cnt_l++;
				}
				if(key_cnt_l>12)
				{
					freq+=1000;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
					key_cnt_l = 0;
				}
			}else if((PINB&(1<<PB2))==0x00)//PB2 freq-
			{
				key_cnt++;
				if(key_cnt>12)
				{
					freq-=100;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
					key_cnt = 0;
					key_cnt_l++;
				}
				if(key_cnt_l>5)
				{
					freq-=1000;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
					key_cnt_l = 0;
				}
			}else
			{
				key_cnt = 0;
				key_cnt_l = 0;
			}
			time_cnt = 0;
		}
	}
}

