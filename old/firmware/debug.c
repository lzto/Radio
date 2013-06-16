//使用AVR Studio 4.12 + WinAVR编译
//create by arcdevil @20051224
#include <avr/io.h>
#include <util/delay.h>
#include <avr/signal.h>
#include <avr/interrupt.h>
//常量定义
//#define BAUDRATE        9600 //波特率
#define BAUDRATE 19200

unsigned char sec,min,hour;
unsigned int i = 0;
unsigned char temp;


//向串口写数
void put_c(unsigned char c)
{
 while( !(UCSRA & (1<<UDRE)) );
 UDR=c;
}

//从串口读数
unsigned char USART_Receive( void )
{
   //等待接受标志
   while ( !(UCSRA & (1<<RXC)) )
   ;
   //读接收数据
   return UDR;
}

//向串口写字符串
void put_s(unsigned char *ptr)
{
 while (*ptr)
 {
  put_c(*ptr++);
 }
 put_c(0x0D);//回车
 put_c(0x0A);//换行  
}

//串口以BCD传送16进数
void dip_c(unsigned char c)
{
    unsigned char t;
 t = c/10;
 put_c(t+0x30);
 t = c%10;
 put_c(t+0x30);
    
}

//初始化timer0
void timer0_init(void)
{
	TCCR0 = 0x05;
	TCNT0 = 0x4c; //定时时间50ms
	TIMSK = _BV(OCIE1A);
}

//50ms中断
SIGNAL(SIG_OVERFLOW0)
{

	TCNT0 = 0x4c;

	if(++i == 20)
	{
		i = 0; 
		if (++sec == 60)  
		{
 			sec = 0;
 			if (++min == 60) 
 			{
			     min = 0;
     if (++hour == 24)  
  {   
       hour = 0;
     }
   }
 }
 put_c(0x0d);
 dip_c(hour);
    put_c(':');
 dip_c(min);
 put_c(':');
 dip_c(sec);
 }

}

//USART 初始化
void init_USART(void)
{
    //USART 9600 8, n,1  PC上位机软件(超级终端等)也要设成同样的设置才能通讯
    UCSRC = (1<<URSEL) | 0x06;
    
	//异步，8位数据，无奇偶校验，一个停止位，无倍速   
    //U2X=0时的公式计算
    UBRRL= (F_CPU/BAUDRATE/16-1)%256;
    UBRRH= (F_CPU/BAUDRATE/16-1)/256;

    UCSRA = 0x00;
    //UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	//使能接收中断，使能接收，使能发送
	UCSRB = (1<<RXEN)|(1<<TXEN);

}

void debug(char *str)
{
	put_s(str);
	//timer0_init();
	//sei();
}

