#ifndef _DRADIO_H_
#define _DRADIO_H_
#include <avr/io.h>
#include "Global.h"

#define R_CS  3

#define Radio_PORT PORTD
#define Radio_DDR  DDRD
#define Radio_PIN  PIND

#define R_Enable()  Set_Bit(Radio_PORT, R_CS)
#define R_Disable() Clr_Bit(Radio_PORT, R_CS)

void R_Init();

#endif

