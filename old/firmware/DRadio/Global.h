#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define uint8  unsigned char
#define uint16 unsigned int
#define uchar  unsigned char
#define uint   unsigned int
#define uint32 unsigned long
#define ON  0
#define OFF 1

#define Set_Bit(port, bit) port |=  (1<<bit)
#define Clr_Bit(port, bit) port &= ~(1<<bit)
#define Get_Bit(pin,  bit) (pin & (1<<bit))

#endif
