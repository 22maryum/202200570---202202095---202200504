#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "pump.h"


void PUMP_voidInit(void)
{
    /* Set pump pin as output */
    GPIO_voidSetPinDirection(PUMP_PORT, PUMP_PIN, OUTPUT);
    /* Turn off pump initially */
    GPIO_voidSetPinValue(PUMP_PORT, PUMP_PIN, LOW);
}

void PUMP_voidTurnOn(void)
{
    /* Turn on water pump */
    GPIO_voidSetPinValue(PUMP_PORT, PUMP_PIN, HIGH);
}

void PUMP_voidTurnOff(void)
{
    /* Turn off water pump */
    GPIO_voidSetPinValue(PUMP_PORT, PUMP_PIN, LOW);
}

void PUMP_voidWater(u16 duration)
{
    /* Turn on pump */
    GPIO_voidSetPinValue(PUMP_PORT, PUMP_PIN, HIGH);
    /* Wait for duration in milliseconds */
    TIMER0_voidDelayMs(duration);
    /* Turn off pump */
    GPIO_voidSetPinValue(PUMP_PORT, PUMP_PIN, LOW);
    
}