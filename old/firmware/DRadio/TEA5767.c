#include "TEA5767.h"

#include "../debug.h"

//TWINT 标志的清零必须通过软件写 "1" 来完成
unsigned char set5767(unsigned char *dat) 
{ 
        uchar i = 0; 
         
        TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // SEND START SIGNAL 
        while (!(TWCR & (1<<TWINT)));           // WAIT FOR START SIG 等待START信号发送完成

        if ((TWSR & 0xF8) != START)
		{
			return 0;
		}
        TWDR = SLA_W;                            // send address 写TEA5767的地址
        TWCR = (1<<TWINT)|(1<<TWEN);             //清TWI中断标志，使能发送。。。
        while (!(TWCR & (1<<TWINT)));            //等待发送完成。。。

        if ((TWSR & 0xF8) !=MT_SLA_ACK)
		{
			TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL
			return 0;  //ACK
		}
        for ( i = 0; i < 5; i++ ) 
        { 
               
            TWDR = dat[i];                  //写数据
            TWCR = (1<<TWINT)|(1<<TWEN);         // send data 
            while (!(TWCR & (1<<TWINT)));        //等待发送完成
			if ((TWSR & 0xF8) != MT_DATA_ACK)
			{
				TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL
				return 0;//ACK
			}
        }
       
        TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL 
        return 1;
} 

void read5767(void)
{
	uchar i = 0;
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // SEND START SIGNAL
	while (!(TWCR & (1<<TWINT)));           // WAIT FOR START SIG
	//if ((TWSR & 0xF8) != START)  ERROR();
	
	TWDR = SLA_R;                            // send address
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	//if ((TWSR & 0xF8) !=MT_SLA_ACK) ERROR();
	//TWCR = (1<<TWINT) | (1<<TWEN);
	
	for ( i = 0; i < 5; i++ )
	{
		TWCR = (1<<TWINT) | (1<<TWEN);      // read data
		while (!(TWCR & (1<<TWINT)));
		//readdata[i] = TWDR ;//save版本没有[i]
		
		debug("rd:");
		dip_c(TWDR);
		debug("\r\n");
	//	if ((TWSR & 0xF8) != MT_DATA_ACK) ERROR();
	}
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //SEND STOP SIGNAL

	//LCD_write_english_string(10,3,"rOK");
}




///////////////////////////////////////////////////////////////////////////////////////
unsigned char TEA5767_INTI(void)
{
	unsigned char senddata[5];

	TWBR = 12*12;         //分频系数 SCL frequency = CPU Clock frequency/(16+2*(TWBR)*4)
	                   //约 70KHz 的时钟频率
	TWCR = (1<<TWEN);  //SEND STOP SIGNAL

	senddata[0] = 0x29;  //load 88.3MHz BIT6用于选择是否搜台模式1是/0否 0x29
	                     //BIT7 MUTE1/NO MUTE0    PLL13...8
	senddata[1] = 0xF5;  // PLL7...0   F1
	senddata[2] = 0x60;  //bit7 用于选择向上1/向下搜台0  ADC选择 0x20 ADC 5
	                                                           //0x40 ADC 7
															   //0x60 ADC 10
	senddata[3] = 0x12;  //bit5 用于选择日本1/欧洲模式0
	senddata[4] = 0x00;  //不用改
	return (set5767(senddata));
}

/////////////////////////////////////////////////////////////////////////////////////////////
//手动设置频率
void set_frequency(unsigned long frequency) //设定频率KHz
{
	unsigned char senddata[5];
    unsigned int PLL;
	unsigned char falg;
    if(senddata[2]&0x10)
		PLL=(unsigned int)((float)((frequency+225)*4)/(float)32.768);
    else
		PLL=(unsigned int)((float)((frequency-225)*4)/(float)32.768);

    senddata[0] = PLL/256;
	senddata[1] = PLL%256;
	senddata[0]&= 0x3F;
	senddata[2] = 0x00;
	senddata[3] = 0x12;
	senddata[4] = 0x00;
    falg=set5767(senddata);
}


