#include "tea5767.h"

unsigned char set5767(unsigned char *dat) 
{
	unsigned char i = 0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // SEND START SIGNAL 
	while (!(TWCR & (1<<TWINT)));           // WAIT FOR START SIG 等待START信号发送完成
//	if ((TWSR & 0xF8) != START)
//		return 0;

	TWDR = SLA_W;                            // send address 写TEA5767的地址
	TWCR = (1<<TWINT)|(1<<TWEN);             //清TWI中断标志，使能发送。。。
	while (!(TWCR & (1<<TWINT)));            //等待发送完成。。。
//	if ((TWSR & 0xF8) !=MT_SLA_ACK)
//		return 0;  //ACK

	for(i=0;i<5;i++)
	{
		TWDR = dat[i];                  //写数据
		TWCR = (1<<TWINT)|(1<<TWEN);         // send data 
		while (!(TWCR & (1<<TWINT)));        //等待发送完成
//		if ((TWSR & 0xF8) != MT_DATA_ACK)
//			return 0;//ACK
	}
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL 
	
	return 1;
}

unsigned char read5767(unsigned char *readdata)
{
	unsigned char i = 0;
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // SEND START SIGNAL
	while (!(TWCR & (1<<TWINT)));           // WAIT FOR START SIG 等待起始信号发送成功
	TWDR = SLA_R;//读tea5767
	TWCR=(1<<TWINT)|(1<<TWEN);    // send address 发送地址&读
	while (!(TWCR & (1<<TWINT)));           //等待发送完成
	for(i=0;i<5;i++) //接收5个字节
	{
		TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);      // read data 使能自动应答
		while (!(TWCR & (1<<TWINT)));             //是否收到一个字节
		readdata[i] = TWDR ;                      //保存到缓冲区
	}
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////
unsigned char TEA5767_INIT(unsigned char radio_mode)
{
	PORTC |= 0x30;
	DDRC |= 0x30;

	TWSR = 0x00;
	TWBR = 12*12;	//分频系数 SCL frequency = CPU Clock frequency/(16+2*(TWBR)*4)
				//约 70KHz 的时钟频率
	TWAR = 0x00;
	TWCR = (1<<TWEN);  //SEND STOP SIGNAL

	senddata[0] = 0x29;  //load 88.3MHz BIT6用于选择是否搜台模式1是/0否 0x29
	                     //BIT7 MUTE1/NO MUTE0    PLL13...8
	
	senddata[1] = 0xF5;  // PLL7...0   F1
	senddata[2] = 0x60;  //bit7 用于选择向上1/向下搜台0  ADC选择 0x20 ADC 5
	                                                           //0x40 ADC 7
								   //0x60 ADC 10
	if(radio_mode==0x00)
		senddata[3] = MODE_JAP;  //bit5 用于选择日本1/欧洲模式0
	else if (radio_mode==0x01)
		senddata[3] = MODE_USA;

	senddata[4] = 0x00;  //不用改
	return (set5767(senddata));
}

/////////////////////////////////////////////////////////////////////////////////////////////
//手动设置频率
void set_frequency(unsigned long frequency) //设定频率KHz
{
	unsigned int PLL;
//	if(senddata[2]&0x10)
//		PLL=(unsigned int)((float)((frequency+225)*4)/(float)32.768);
//	else
		PLL=(unsigned int)((float)((frequency-225)*4)/(float)32.768);

	senddata[0] = PLL/256;
	senddata[1] = PLL%256;
	senddata[0]&= 0x3F;
	senddata[2] = 0x00;
	senddata[3] = 0x12;
	senddata[4] = 0x00;
	set5767(senddata);
}


