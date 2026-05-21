#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"

void TIMER0_voidInit(void);
void TIMER0_voidDelayUs(u8 time);
void TIMER0_voidDelayMs(u16 time);

#endif