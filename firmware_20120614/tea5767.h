#ifndef _TEA5767_H_
#define _TEA5767_H_


#include <avr/io.h>

#define START       0x08                    //TWI 状态指示
#define MT_SLA_ACK  0x18
#define MT_SLA_NOACK  0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NOACK 0x30

#define LowestFM_US 	    87500		      //87.5MHz	
#define HighestFM_US    	108000	          //108Mhz
#define LowestFM_JA 	    76000		      //76MHz	
#define HighestFM_JA    	91000	          //91Mhz

#define MODE_JAP 0X32   //日本模式
#define MODE_USA 0X12   //美国模式

#define LOW_US_H            0x69
#define LOW_US_L            0xD8            //87.5 &108 MHz
#define HIG_US_H            0x73            
#define HIG_US_L            0x9E            //PLL FOR US band

#define LOW_JA_H            0x64
#define LOW_JA_L            0x5C            //76 & 91 MHz
#define HIG_JA_H            0x6B
#define HIG_JA_L            0x83            //PLL FOR JA band

#define SLA_W 0xC0	//write   TEA5767 地址
#define SLA_R 0xC1	//read

unsigned char senddata[5];

unsigned char TEA5767_INIT(unsigned char radio_mode);    //初始化TWI
unsigned char set5767(unsigned char *dat);         //写TEA5767寄存器
unsigned char read5767(unsigned char *readdata);
void set_frequency(unsigned long frequency);

#endif

