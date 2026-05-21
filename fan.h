#ifndef FAN_INTERFACE_H
#define FAN_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"

/* Fan Port & Pin Definitions */
#define FAN_PORT   PORTD_ID
#define FAN_PIN    2
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0

void FAN_voidInit(void);
void FAN_voidTurnOn(void);
void FAN_voidTurnOff(void);

#endif