#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#define DEBUG_LEVEL 0

#include "requests.h"

#include "usbdrv/usbdrv.h"
#include "usbdrv/oddebug.h"

#include "DRadio/DRadio.h"
#include "DRadio/TEA5767.h"

enum MODE{READY,GETFREQ,STEP,SETFREQ} mode;

long int freq = 99100;
unsigned char dataBuf[4];
unsigned char count;


PROGMEM char usbHidReportDescriptor[22] = {    /* USB report descriptor */
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
	switch(mode)
	{
		case(SETFREQ):
		{
			memcpy(&dataBuf[count],data,len);
			count+=len;
			if(count>=4)
			{
				memcpy(&freq,&dataBuf,4);
				set_frequency(freq);
				mode = READY;
				count = 0;
				return 1;
			}
			return 0;
			break;
		}
		default:
		{
			break;
		}
	}
	return 1;
}


usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t    *rq = (void *)data;
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_VENDOR){
        DBG1(0x50, &rq->bRequest, 1);   /* debug output: print our request */
        if(rq->bRequest == CUSTOM_RQ_SET_STATUS)
		{
			mode = STEP;
            if(rq->wValue.bytes[0] & 1){ //freq+
                freq+=100;
				set_frequency(freq);
            }else{						//freq-
                freq-=100;
				set_frequency(freq);
            }
        }else if(rq->bRequest == CUSTOM_RQ_GET_STATUS)
		{
			mode = GETFREQ;
            static uchar dataBuffer[4];     /* buffer must stay valid when usbFunctionSetup returns */
            memcpy(dataBuffer,&freq,4);
            usbMsgPtr = dataBuffer;         /* tell the driver which data to return */
            return 4;                       /* tell the driver to send 1 byte */
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
    }else
	{
	}
    return 0;   /* default for not implemented requests: return no data back to host */
}




//TIMER1 initialize - prescale:1
// WGM: 0) Normal, TOP=0xFFFF
// desired value: 8KHz
// actual value:  8.000KHz (0.0%)
void init_Timer1(void)
{
	TCCR1B = 0x00; //stop
	TCNT1H = 0xFA; //setup
	TCNT1L = 0x24;
	OCR1AH = 0x05;
	OCR1AL = 0xDC;
	OCR1BH = 0x05;
	OCR1BL = 0xDC;
	ICR1H  = 0x05;
	ICR1L  = 0xDC;
	TCCR1A = 0x00;
	TCCR1B = 0x01; //start Timer
	TIMSK = 0x04; //timer interrupt sources
}



void init_ADC()
{
	DDRC   &= ~(0x03);
	PORTC  &= ~(0x03);
	ADMUX   = 0xE1;//ADC1,注意数据左调，这个很重要，不然，声音会很小
	ADCSRA  = ((1<<ADEN) | (1<<ADSC) | 0x04);//128分频//这个128是错的，应该是16分频
	//ADCSRA  = ((1<<ADEN) | (1<<ADSC) | 0x07);//这个才是128分频
	SFIOR   = 0x10;
}


int main()
{

	count = 0;
//    odDebugInit();
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */

	//_delay_ms(250);

	//init_USART();
	//init_Timer1();
	//init_ADC();

	R_Init();
	R_Enable();
	_delay_ms(10);

	TEA5767_INTI();


	set_frequency(freq);
	//set_frequency(99100);//99.1Mhz
	//set_frequency(80400);//80.4Mhz
	//set_frequency(88700);//88.7Mhz
	mode = READY;
    usbDeviceConnect();

	sei();

	while(1)
	{
	    usbPoll();
		if(bit_is_clear(PINC,2))
		{
			freq+=100;
			set_frequency(freq);
			_delay_us(400000);
			debug("+\r\n");
		}else if(bit_is_clear(PINC,3))
		{
			freq-=100;
			set_frequency(freq);
			_delay_us(400000);
			debug("-\r\n");
		}
	}
	return 0;
}

/*SIGNAL(SIG_OVERFLOW1)//Timer1 interrupt
{

	TCNT1H = 0xFA; //reload counter high value
	TCNT1L = 0x24; //reload counter low value	if(SampCnt<15)
	ADCSRA |= (1<<ADSC);//开始新的转换

	//debug("ADCL");
	dip_c(ADCL);
	//debug("\r\n");
	//debug("ADCH");
	dip_c(ADCH);
	debug("\r\n");
}*/

