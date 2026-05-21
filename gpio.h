#ifndef GPIO_H
#define GPIO_H

#include "../../SERVICES/std_types.h"

/* Use numeric IDs to avoid conflict with XC8 PORTA/PORTB macros */
#define PORTA_ID  0
#define PORTB_ID  1
#define PORTC_ID  2
#define PORTD_ID  3

#define INPUT   1
#define OUTPUT  0
#define HIGH    1
#define LOW     0

void GPIO_voidSetPinDirection(u8 port, u8 pin, u8 dir);
void GPIO_voidSetPinValue(u8 port, u8 pin, u8 val);
u8   GPIO_u8GetPinValue(u8 port, u8 pin);
void GPIO_voidInit(void);

#endif