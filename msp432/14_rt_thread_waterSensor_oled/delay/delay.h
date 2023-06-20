#ifndef __DELAY_H__
#define __DELAY_H__

#include "ti/devices/msp432e4/driverlib/driverlib.h"

void delay_init(void);
void delay_us(unsigned int us);
void delay_ms(uint32_t ms);
#endif
