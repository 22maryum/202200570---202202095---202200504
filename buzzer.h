#ifndef BUZZER_INTERFACE_H
#define BUZZER_INTERFACE_H
#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"

#define BUZZER_PORT   PORTD_ID
#define BUZZER_PIN    3          /* RD3 = pin 22 */

#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0

void BUZZER_voidInit(void);
void BUZZER_voidTurnOn(void);
void BUZZER_voidTurnOff(void);
void BUZZER_voidBeep(u16 duration);
#endif