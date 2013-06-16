#include "lcd1602.h"

#include <util/delay.h>

#include <string.h>

void lcd_1602_write_line(unsigned char data)
{
	CLRBIT(LCD_CONTROL_PORT,LCD_RW);

	(data&0x10)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT0):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT0);
	(data&0x20)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT1):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT1);
	(data&0x40)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT2):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT2);
	(data&0x80)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT3):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT3);

	SETBIT(LCD_CONTROL_PORT,LCD_EP);
	//_delay_us(1);
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);

	(data&0x01)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT0):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT0);
	(data&0x02)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT1):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT1);
	(data&0x04)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT2):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT2);
	(data&0x08)? SETBIT(LCD_DATA_PORT,LCD_DATA_BIT3):CLRBIT(LCD_DATA_PORT,LCD_DATA_BIT3);

	SETBIT(LCD_CONTROL_PORT,LCD_EP);
	//_delay_us(1);
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);

	SETBIT(LCD_CONTROL_PORT,LCD_RW);
}

void lcd_1602_write_command(unsigned char command)
{
	//lcd_1602_wait_ready();
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);
	CLRBIT(LCD_CONTROL_PORT,LCD_RS);
	CLRBIT(LCD_CONTROL_PORT,LCD_RW);
	lcd_1602_write_line(command);
	SETBIT(LCD_CONTROL_PORT,LCD_RS);
	_delay_us(40);
}

void lcd_1602_write_data(unsigned char data)
{
	//lcd_1602_wait_ready();
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);
	SETBIT(LCD_CONTROL_PORT,LCD_RS);
	CLRBIT(LCD_CONTROL_PORT,LCD_RW);
	lcd_1602_write_line(data);
	_delay_us(40);
}

void lcd_1602_init(void) 
{
	//LCD_DATA_PORT |= ((1<<LCD_DATA_BIT0)|(1<<LCD_DATA_BIT1)|(1<<LCD_DATA_BIT2)|(1<<LCD_DATA_BIT3));
	LCD_DATA_DDR |= ((1<<LCD_DATA_BIT0)|(1<<LCD_DATA_BIT1)|(1<<LCD_DATA_BIT2)|(1<<LCD_DATA_BIT3));

	//LCD_BL_PORT |= (1<<LCD_BL);
	LCD_BL_DDR |= (1<<LCD_BL);

	//LCD_CONTROL_PORT |= ((1<<LCD_EP)|(1<<LCD_RW)|(1<<LCD_RS));
	LCD_CONTROL_DDR |= ((1<<LCD_EP)|(1<<LCD_RW)|(1<<LCD_RS));

	_delay_ms(10);

	lcd_1602_write_command(0x33);
	_delay_ms(41);
	lcd_1602_write_command(0x32);
	_delay_ms(100);
	lcd_1602_write_command(0x28);
	_delay_ms(50);
	lcd_1602_write_command(0x06);
	_delay_ms(50);
	lcd_1602_write_command(0x0C);
	_delay_ms(1);
	lcd_1602_write_command(0x01);
	_delay_ms(1);
	lcd_1602_write_command(0x80);
	_delay_ms(1);
}

void lcd_1602_set_addr(unsigned char x,unsigned char y)    //x:0~15,y:0~1 
{
	if(y!=0)
		lcd_1602_write_command(0xC0+(x&0x0F));//第二行显示
	else
		lcd_1602_write_command(0x80+(x&0x0F));//第一行显示
}

/*
void lcd_1602_write_char(unsigned char X,unsigned char Y,char data) //列x=0~15,行y=0,1 
{
	lcd_1602_set_addr(X,Y);
	lcd_1602_write_data(data);
}*/


void lcd_1602_write_string(unsigned char X,unsigned char Y,char *s) //列x=0~15,行y=0,1
{
	lcd_1602_set_addr( X, Y );
	do{
		lcd_1602_write_data( *s );
	}while(*(s++));
}
/*
void lcd_1602_roll_frame(unsigned char line,char* lcd_buff0,char* lcd_buff1)
{
	unsigned char uiTemp;
	unsigned char len;
	unsigned int i;


	if(line &0x01)
	{
		len = strlen((const char*)lcd_buff0);
		if(len>16)
		{
			uiTemp = lcd_buff0[0];
			for(i=0;i<len-1;i++)
			{
				lcd_buff0[i] = lcd_buff0[i+1];
			}
			lcd_buff0[len-1] = uiTemp;
		}
		if(len!=0)
			lcd_1602_write_string((unsigned char)0x00,(unsigned char)0x00,lcd_buff0);
	}
	if(line & 0x02)
	{
		len = strlen((const char *)lcd_buff1);
		if(len>16)
		{
			uiTemp = lcd_buff1[0];
			for(i=0;i<len-1;i++)
			{
				lcd_buff1[i] = lcd_buff1[i+1];
			}
			lcd_buff1[len-1] = uiTemp;
		}
		if(len!=0)
			lcd_1602_write_string((unsigned char)0x00,(unsigned char)0x01,lcd_buff1);
	}
}
*/

