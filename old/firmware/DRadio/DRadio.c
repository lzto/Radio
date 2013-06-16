#include "DRadio.h"
#include "TEA5767.h"
#include <util/delay.h>

void R_Init()
{
	Radio_DDR |= (1<<R_CS);
	DDRC &= ~((1<<2)|(1<<3)|(1<<4)|(1<<5));
	PORTC |= (1<<2)|(1<<3)|(1<<4)|(1<<5);
	R_Disable();
}
