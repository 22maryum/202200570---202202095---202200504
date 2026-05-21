#ifndef PWM_INTERFACE_H
#define PWM_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"

/* Servo Angle Definitions */
#define SERVO_0_DEG    0
#define SERVO_90_DEG   90
#define SERVO_180_DEG  180

void PWM_voidInit(void);
void PWM_voidSetDuty(u8 duty);
void PWM_voidSetServoAngle(u8 angle);

#endif