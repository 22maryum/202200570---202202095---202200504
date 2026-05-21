#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/PWM/pwm.h"

/* Servo Angle Definitions */
#define SERVO_0_DEG    0
#define SERVO_45_DEG   45
#define SERVO_90_DEG   90
#define SERVO_135_DEG  135
#define SERVO_180_DEG  180
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0
void SERVO_voidInit(void);
void SERVO_voidSetAngle(u8 angle);
void SERVO_voidSweep(void);

#endif