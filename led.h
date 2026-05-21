#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"

/* LED Port & Pin Definitions */
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0
#define LED_YELLOW_PORT   PORTD_ID
#define LED_YELLOW_PIN    1

void LED_voidInit(void);
void LED_voidTurnOn(u8 port, u8 pin);
void LED_voidTurnOff(u8 port, u8 pin);
void LED_voidToggle(u8 port, u8 pin);

#endif