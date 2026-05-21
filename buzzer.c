#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "buzzer.h"


void BUZZER_voidInit(void)
{
    /* Set buzzer pin as output */
    GPIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT);
    /* Turn off buzzer initially */
    GPIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, LOW);
}

void BUZZER_voidTurnOn(void)
{
    GPIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, HIGH);
}

void BUZZER_voidTurnOff(void)
{
    GPIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, LOW);
}

void BUZZER_voidBeep(u16 duration)
{
    /* Turn on buzzer */
    GPIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, HIGH);
    /* Wait for duration in milliseconds */
    TIMER0_voidDelayMs(duration);
    /* Turn off buzzer */
    GPIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, LOW);
    
}