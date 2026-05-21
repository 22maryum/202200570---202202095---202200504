#ifndef PUMP_INTERFACE_H
#define PUMP_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"

/* Pump Port & Pin Definitions */
#define PUMP_PORT   PORTD_ID
#define PUMP_PIN    2
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0
void PUMP_voidInit(void);
void PUMP_voidTurnOn(void);
void PUMP_voidTurnOff(void);
void PUMP_voidWater(u16 duration);

#endif