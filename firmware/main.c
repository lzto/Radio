#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>

#include <stdio.h>
#include <string.h>

#include "tostring.h"

#include "requests.h"

#include "usbdrv/usbdrv.h"
#include "usbdrv/oddebug.h"

#include "tea5767.h"
#include "lcd1602.h"

#define FIX_POINTER(_ptr) __asm__ __volatile__("" : "=b" (_ptr) : "0" (_ptr))

////////////////////////////////////////////////////
//EEPROM Area
//eeprom layout
//Byte:
//0:RADIO_MODE:JAP or USA
//1:BACKLIGHT_STATE
//2:current_channel
//3:channel_count
//4:Freq
//5:Freq
//6:Freq
//7:Freq
//8~15:Not used
//16:channel_data
uint8_t EEMEM eprom_country = 0;
uint8_t EEMEM eprom_blstate = 1;
uint8_t EEMEM eprom_current_channel = 0;
uint8_t EEMEM eprom_channel_count = 0x00;
uint32_t EEMEM eprom_freq = 88700;
#define CHANNEL_DATA_OFFSET (16)

////////////////////////////////////////////////////
//IR table
/*unsigned long ir_table[]=
{
	0xba45ff00,0xb946ff00,0xb847ff00,//ch-,ch,ch+
	0xbb44ff00,0xbf40ff00,0xbc43ff00,//|<<,>>|,>||
	0xf807ff00,0xea15ff00,0xf609ff00,//Vol-,Vol+,EQ
	0xe916ff00,0xe619ff00,0xf20dff00,//0,100+,200+
	0xf30cff00,0xe718ff00,0xa15eff00,//1,2,3
	0xf708ff00,0xe31cff00,0xa55aff00,//4,5,6
	0xbd42ff00,0xad52ff00,0xb54aff00//7,8,9
};*/
#define ir_channel_minus 0xba45
#define ir_channel 0xb946
#define ir_channel_plus 0xb847
#define ir_prev 0xbb44
#define ir_next 0xbf40
#define ir_play_pause 0xbc43
#define ir_vol_minus 0xf807
#define ir_vol_plus 0xea15
#define ir_vol_eq 0xf609
#define ir_zero 0xe916
#define ir_one_hundred_plus 0xe619
#define ir_two_hundred_plus 0xf20d
#define ir_one 0xf30c
#define ir_two 0xe718
#define ir_three 0xa15e
#define ir_four 0xf708
#define ir_five 0xe31c
#define ir_six 0xa55a
#define ir_seven 0xbd42
#define ir_eight 0xad52
#define ir_nine 0xb54a

///////////////////////////////////////////////////


enum MODE{READY,GETFREQ,STEP,SETFREQ,PROGCHANNELS} mode;

long freq;
unsigned char current_channel = 0x00;
unsigned char channel_count = 0x00;

char rx_signal_power = 0xFF;
unsigned char count = 0x00;
//////////////////////////////////
#define FLAG_BL 0x80
#define FLAG_LCD_FREQ 0x40
#define FLAG_LCD_RXPWR 0x20
#define FLAG_TEASET 0x10
#define FLAG_IR_DATA_READY 0x08
#define FLAG_CHANNEL_SIG 0x04
#define FLAG_CHANNEL_SIG_UNCHECKED 0x02
#define FLAG_STEREO 0x01

unsigned char flag __asm__("r12") = 0xF2;
//1 1 1 1    1 1 1 0
//|-LCD_BL 1-on 0-off
//  |-UPDATE_FREQ 1-update
//    |-UPDATE_RX_POWER 1-update
//      |-TEA5767-UPDATE_FREQ
//      -------------
//           |-GOT NEW IR_DATA
//             |-SHOW CHANNEL_SIG
//               |-CHANNEL_SIG_UNCHECKED
//                 |-STEREO
////////////////////////////////////
//buffer layout:
//0~18: lcd buffer
//19~22: ir_buffer
//23~26: usb_write_buffer
//27~32: read_tea5767_buffer
//33~48: buf2
char buff[64];

#define IR_DATA_OFFSET 19

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

////////////////////////
//use int1 for ir
ISR(INT1_vect)
{
	unsigned char i = 0;
	unsigned char j = 0;
	unsigned char k = 0;
	unsigned char* addr = (unsigned char*)(buff+IR_DATA_OFFSET);
	FIX_POINTER(addr);

	GICR &=  ~(1 << INT1);
	for(i = 0;i <14;i++)
	{
		_delay_us(400);
		if(PIND & (1 << PD3))    //9MS内有高电平，则判断为干扰，退出处理程序
		{
			GICR |= (1 << INT1);
			return;
		}
	}
	while(!(PIND & (1 << PD3)));  //等待9ms低电平过去
	for(i = 0;i < 4;i++)
	{
		for(j = 0;j <8;j++)
		{
			while(PIND & (1 << PD3)); //4.5ms H
			while(!(PIND & (1 << PD3))); //等待变高电平
			while(PIND & (1 << PD3))  //计算高电平时间
			{
				_delay_us(100);
				if(++k >= 30)             //高电平时间过长，则退出处理程序
				{
					GICR |= (1 << INT1);    //使能外部中断
					return;            //
				}
			}
			addr[i] = addr[i] >> 1;        //接受一位数据
			if(k >= 8)
			{
				addr[i] = addr[i] | 0x80;   //高电平时间大于0.56，则为数据1
			}
			k = 0;                  //计时清零
		}
	}
	flag |= FLAG_IR_DATA_READY;
	GICR |= (1 << INT1);    //使能外部中断
}
////////////////////////

uchar usbFunctionWrite(uchar *data, uchar len)//read data from host
{
	switch(mode)
	{
		case(SETFREQ):
		{
			memcpy(buff+count+23,data,len);
			count+=len;

			if(len>=4)
			{
				memcpy(&freq,buff+23,4);
				flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);//update everything
				flag &= (~FLAG_CHANNEL_SIG);
				mode = READY;
				count = 0;
				break;
			}
			return 0;
		}
		case(PROGCHANNELS):
		{
			if(channel_count == 0xFF)
			{
				memcpy(&channel_count,data,1);
				eeprom_update_block((const void*)&channel_count,(void*)&eprom_channel_count,1);
				data++;
				len--;
			}
			eeprom_update_block((const void*)data, (void*) CHANNEL_DATA_OFFSET + count, len);
			count+=len;
			if((count)>=(channel_count*4))
			{
				count = 0;
				break;
			}
			return 0;
		}
		default:
			break;
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
			}else
			{//freq-
				freq-=100;
			}
			flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);
			flag &= (~FLAG_CHANNEL_SIG);
			return 0;
		}else if(rq->bRequest == CUSTOM_RQ_GET_STATUS)
		{
			mode = GETFREQ;
			static unsigned char dataBuffer[5];     /* buffer must stay valid when usbFunctionSetup returns */
			memcpy(dataBuffer,&freq,4);
			dataBuffer[4] = rx_signal_power;
			usbMsgPtr = dataBuffer;         /* tell the driver which data to return */
			return 5;
		}
	}else if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS)
	{
		/* calss requests USBRQ_HID_GET_REPORT and USBRQ_HID_SET_REPORT*/
		if(rq->bRequest == CUSTOM_RQ_SET_FREQ)
		{
			count = 0;
			mode = SETFREQ;//call usbFunctionWrite
			return USB_NO_MSG;
		}else if(rq->bRequest == CUSTOM_RQ_PROG_CHANNELS)
		{
			count = 0;
			channel_count = 0xFF;
			mode = PROGCHANNELS;
			return USB_NO_MSG;
		}
	}
	return 0;   /* default for not implemented requests: return no data back to host */
}

void ShowFreq()
{
	//HACK!
	char* buf2 = (buff+32);

	//sprintf(buff,"%d.%d MHz        ",(int)(freq/100)/10,(int)(freq/100)%10);
	ToLCDString(buff,"% MHz        ",(int)(freq/100),1);
	//buff[16]=0;
	if(flag&FLAG_CHANNEL_SIG)
	{
		memcpy(buf2,buff,16);
		buf2[11] = 'C';
		buf2[12] = 'H';
		buf2[13] = ':';
		buf2[14] = '%';
		ToLCDString(buff,buf2,(int)(current_channel),0);
	}
	lcd_1602_write_string((unsigned char)0x00,buff);
}

void ShowSignalQuality()
{
	//sprintf(buff,"Signal : %d      ",rx_signal_power);
	if(flag&FLAG_STEREO)
	{
		ToLCDString(buff,"Signal: %  STER ",rx_signal_power,0);
	}else
	{
		ToLCDString(buff,"Signal: %  MONO ",rx_signal_power,0);
	}

	//buff[16]=0;
	lcd_1602_write_string((unsigned char)0x01,buff);
}

void system_init()
{
	lcd_1602_init();
	//Buttons
	PORTB |= ((1<<PB1)|(1<<PB2));//PB1 and PB2
	DDRB |= ((1<<PB1)|(1<<PB2));//PB1 and PB2
	eeprom_read_block((void*)&freq,(const void*)&eprom_freq,4);
	channel_count = eeprom_read_byte(&eprom_channel_count);
	current_channel = eeprom_read_byte(&eprom_current_channel);
	//flag |= FLAG_CHANNEL_SIG_UNCHECKED;
	/*if(eeprom_read_byte(&eprom_blstate)==0)
	{
		flag &=~FLAG_BL;
	}*/
}


void main() __attribute__ ((noreturn));
void main()
{
	long temp_l = 0;
	int temp = 0;
	unsigned int time_cnt = 0;
	unsigned char key_cnt = 0;
	unsigned char key_cnt_l = 0;
//IR
	unsigned char ir_key_cnt = 0;
	unsigned char ir_temp_channel = 0;
///////
	system_init();

	wdt_enable(WDTO_1S);

	usbInit();
	usbDeviceDisconnect();

	_delay_ms(0xFF);
	
//////////
	TEA5767_INIT(eeprom_read_byte(&eprom_country));

	mode = READY;
 	usbDeviceConnect();

//Enable int1 for ir
	DDRD |= (1<<PD3);
	PORTD |= (1<<PD3);
	MCUCR |= (1<<ISC00);
	GIMSK |= (1<<INT1);
///////////////////

	sei();
	
	for(;;)
	{
		wdt_reset();
		usbPoll();
		//time_cnt++;
		if(++time_cnt<490)
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
		}else if(time_cnt<520)
		{
			//deal with ir data
			if(flag & FLAG_IR_DATA_READY)
			{
				memcpy(&temp,buff+IR_DATA_OFFSET+2,2);
				if(ir_key_cnt==0)
				{
					ir_temp_channel = 0;
				}else
				{
					ir_temp_channel*=10;
				}
				switch(temp)
				{
					case(ir_channel_minus):
					{
						ir_key_cnt = 0;
						flag |= (FLAG_CHANNEL_SIG);
						if(current_channel>0)
						{
							current_channel--;
							eeprom_read_block((void*)&freq,(const void*)(CHANNEL_DATA_OFFSET + current_channel*4),4);
							eeprom_update_block ((const void*)&current_channel,(void*)&eprom_current_channel,4);
						}
						break;
					}
					case(ir_channel_plus):
					{
						ir_key_cnt = 0;
						flag |= (FLAG_CHANNEL_SIG);
						if(current_channel<channel_count-1)
						{
							current_channel++;
							eeprom_read_block((void*)&freq,(const void*)(CHANNEL_DATA_OFFSET + current_channel*4),4);
							eeprom_update_block ((const void*)&current_channel,(void*)&eprom_current_channel,4);
						}
						break;
					}
					case(ir_prev):
					{
						ir_key_cnt = 0;
						flag &= (~FLAG_CHANNEL_SIG);
						flag |= (FLAG_CHANNEL_SIG_UNCHECKED);
						freq-=100;
						break;
					}
					case(ir_next):
					{
						ir_key_cnt = 0;
						flag &= (~FLAG_CHANNEL_SIG);
						flag |= (FLAG_CHANNEL_SIG_UNCHECKED);
						freq+=100;
						break;
					}
					//Numbers
					case(ir_one):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=1;
						break;
					}
					case(ir_two):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=2;
						break;
					}
					case(ir_three):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=3;
						break;
					}
					case(ir_four):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=4;
						break;
					}
					case(ir_five):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=5;
						break;
					}
					case(ir_six):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=6;
						break;
					}
					case(ir_seven):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=7;
						break;
					}
					case(ir_eight):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=8;
						break;
					}
					case(ir_nine):
					{
						ir_key_cnt = 1;
						ir_temp_channel+=9;
						break;
					}
					case(ir_zero):
					{
						ir_key_cnt = 1;
						break;
					}
					default:;
				}
				flag &= ~FLAG_IR_DATA_READY;
				flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
			}
		}else if(time_cnt<1000)
		{
			//update tea5767 module
			if(flag & FLAG_TEASET)
			{
				//76~108MHZ
				if(freq>108000)
				{
					freq=108000;
				}else if(freq<71000)
				{
					freq = 71000;
				}
				set_frequency(freq);
				eeprom_update_block ((const void*)&freq,(void*)&eprom_freq,4);
				flag &= ~FLAG_TEASET;
			}
		//}else if(time_cnt<1510)
		//{
			//update lcd_freq
			if(flag & FLAG_LCD_FREQ)
			{
				ShowFreq();
				flag &= ~FLAG_LCD_FREQ;
			}
		//}else if(time_cnt<1600)
		//{	//update lcd_rx_power
			if(flag & FLAG_LCD_RXPWR)
			{
				read5767((unsigned char*)buff+27);
				rx_signal_power = (buff[3+27]>>4)&0x0F;
				if((buff[27+2]>>7)&0x0F)
				{
					flag |= FLAG_STEREO;
				}else
				{
					flag &= ~FLAG_STEREO;
				}
				ShowSignalQuality();
				flag &= ~FLAG_LCD_RXPWR;
			}
		}else
		{
			//set channel to ir_channel
			if(ir_key_cnt >0)
			{
				if(++ir_key_cnt>60)
				{
					flag |= (FLAG_CHANNEL_SIG|FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET);
					if((ir_temp_channel<channel_count)&&(ir_temp_channel>=0))
					{
						current_channel = ir_temp_channel;
						eeprom_read_block((void*)&freq,(const void*)(CHANNEL_DATA_OFFSET + current_channel*4),4);
						eeprom_update_block ((const void*)&current_channel,(void*)&eprom_current_channel,4);
					}
					ir_key_cnt=0;
				}
			}
			//Buttons
			if((PINB&(1<<PB1))==0x00)//PB1 freq+
			{
				key_cnt++;
				if(key_cnt>12)
				{
					freq+=100;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);
					flag &= (~FLAG_CHANNEL_SIG);
					key_cnt = 0;
					key_cnt_l++;
				}
				if(key_cnt_l>12)
				{
					freq+=1000;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);
					flag &= (~FLAG_CHANNEL_SIG);
					key_cnt_l = 0;
				}
			}else if((PINB&(1<<PB2))==0x00)//PB2 freq-
			{
				key_cnt++;
				if(key_cnt>12)
				{
					freq-=100;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);
					flag &= (~FLAG_CHANNEL_SIG);
					key_cnt = 0;
					key_cnt_l++;
				}
				if(key_cnt_l>5)
				{
					freq-=1000;
					flag |= (FLAG_LCD_FREQ|FLAG_LCD_RXPWR|FLAG_TEASET|FLAG_CHANNEL_SIG_UNCHECKED);
					flag &= (~FLAG_CHANNEL_SIG);
					key_cnt_l = 0;
				}
			}else
			{
				key_cnt = 0;
				key_cnt_l = 0;
			}
			time_cnt = 0;
			//Update Channel Flag
			if(((flag & FLAG_CHANNEL_SIG)==0x00)&&
					(flag & FLAG_CHANNEL_SIG_UNCHECKED))
			{
				for(temp = 0;temp<channel_count;temp++)
				{
					eeprom_read_block((void*)&temp_l,(const void*)(CHANNEL_DATA_OFFSET + temp*4),4);
					if(freq==temp_l)
					{
						current_channel = temp;
						flag |= (FLAG_CHANNEL_SIG|FLAG_LCD_FREQ|FLAG_LCD_RXPWR);
						break;
					}
				}
				flag &=~FLAG_CHANNEL_SIG_UNCHECKED;
			}
		}
	}
}

