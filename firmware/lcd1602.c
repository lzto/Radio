#include "lcd1602.h"

#include <util/delay.h>

#include <string.h>

void lcd_1602_write_line(unsigned char data)
{
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

}

void lcd_1602_write_command(unsigned char command)
{
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);
	CLRBIT(LCD_CONTROL_PORT,LCD_RS);
	lcd_1602_write_line(command);
	SETBIT(LCD_CONTROL_PORT,LCD_RS);
	_delay_us(40);
}

void lcd_1602_write_data(unsigned char data)
{
	CLRBIT(LCD_CONTROL_PORT,LCD_EP);
	SETBIT(LCD_CONTROL_PORT,LCD_RS);
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

	CLRBIT(LCD_CONTROL_PORT,LCD_RW);

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

void lcd_1602_write_string(unsigned char line,char *s) //列x=0~15,行y=0,1
{
	if(line!=0)
	{
		lcd_1602_write_command(0xC0);
	}else
	{
		lcd_1602_write_command(0x80);
	}
	do{
		lcd_1602_write_data( *s );
	}while(*(s++));
}

