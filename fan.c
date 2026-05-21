#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "fan.h"



void FAN_voidInit(void)
{
    /* Set fan pin as output */
    GPIO_voidSetPinDirection(FAN_PORT, FAN_PIN, OUTPUT);
    /* Turn off fan initially */
    GPIO_voidSetPinValue(FAN_PORT, FAN_PIN, LOW);

}

void FAN_voidTurnOn(void)
{
    /* Turn on fan */
    GPIO_voidSetPinValue(FAN_PORT, FAN_PIN, HIGH);
    
}

void FAN_voidTurnOff(void)
{
    /* Turn off fan */
    GPIO_voidSetPinValue(FAN_PORT, FAN_PIN, LOW);
    
}