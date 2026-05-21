#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "led.h"



void LED_voidInit(void)
{
    /* Set LED pins as output */
    GPIO_voidSetPinDirection(LED_RED_PORT,    LED_RED_PIN,    OUTPUT);
    GPIO_voidSetPinDirection(LED_YELLOW_PORT, LED_YELLOW_PIN, OUTPUT);
    /* Turn off all LEDs initially */
    GPIO_voidSetPinValue(LED_RED_PORT,    LED_RED_PIN,    LOW);
    GPIO_voidSetPinValue(LED_YELLOW_PORT, LED_YELLOW_PIN, LOW);
   
}

void LED_voidTurnOn(u8 port, u8 pin)
{
    GPIO_voidSetPinValue(port, pin, HIGH);
   
}

void LED_voidTurnOff(u8 port, u8 pin)
{
    GPIO_voidSetPinValue(port, pin, LOW);
    
}

void LED_voidToggle(u8 port, u8 pin)
{
    if(GPIO_u8GetPinValue(port, pin) == HIGH)
        GPIO_voidSetPinValue(port, pin, LOW);
    else
        GPIO_voidSetPinValue(port, pin, HIGH);
    
}