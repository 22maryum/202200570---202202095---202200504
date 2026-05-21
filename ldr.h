#ifndef LDR_INTERFACE_H
#define LDR_INTERFACE_H
#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"

#define LDR_PORT        PORTA_ID
#define LDR_PIN         1          /* RA1 = pin 3 */

/* DO pin: LOW = light detected, HIGH = dark (most modules) */
#define LDR_CONDITION_DARK    0
#define LDR_CONDITION_BRIGHT  1

void LDR_voidInit(void);
u8   LDR_u8GetCondition(void);
#endif