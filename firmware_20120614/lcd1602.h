#ifndef _LCD_1602_
#define _LCD_1602_

#include <avr/io.h>

#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC
#define LCD_DATA_BIT0 (PC3)
#define LCD_DATA_BIT1 (PC2)
#define LCD_DATA_BIT2 (PC1)
#define LCD_DATA_BIT3 (PC0)

#define LCD_BL_PORT PORTB
#define LCD_BL_DDR DDRB
#define LCD_BL (PB0)

#define LCD_CONTROL_PORT PORTD
#define LCD_CONTROL_DDR DDRD
#define LCD_EP (PD7)
#define LCD_RW (PD6)
#define LCD_RS (PD5)

#define SETBIT(x,y)   (x|=(1<<y))
#define CLRBIT(x,y)   (x&=(~(1<<y)))

void lcd_1602_wait_ready();
void lcd_1602_write_line(unsigned char data);
void lcd_1602_write_command(unsigned char command);
void lcd_1602_write_data(unsigned char data);
void lcd_1602_init(void);
void lcd_1602_set_addr(unsigned char x,unsigned char y);
//void lcd_1602_write_char(unsigned char X,unsigned char Y,char data);
void lcd_1602_write_string(unsigned char X,unsigned char Y,char *s);
//void lcd_1602_roll_frame(unsigned char line,char* lcd_buff0,char* lcd_buff1);

#endif // _LCD_1602_

