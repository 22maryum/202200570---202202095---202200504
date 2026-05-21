#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "ldr.h"

void LDR_voidInit(void)
{
    /* Set RA1 as input */
    GPIO_voidSetPinDirection(LDR_PORT, LDR_PIN, INPUT);
}

u8 LDR_u8GetCondition(void)
{
    u8 pinVal = GPIO_u8GetPinValue(LDR_PORT, LDR_PIN);

    /* Most LDR modules: DO = LOW when light, HIGH when dark */
    if(pinVal == LOW)
        return LDR_CONDITION_BRIGHT;
    else
        return LDR_CONDITION_DARK;
}