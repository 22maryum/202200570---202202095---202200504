#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/PWM/pwm.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "servo.h"


void SERVO_voidInit(void)
{
    /* Initialize PWM for servo */
    PWM_voidInit();
    /* Set servo to 0 degrees initially */
    PWM_voidSetServoAngle(SERVO_0_DEG);
    
}

void SERVO_voidSetAngle(u8 angle)
{
    /* Make sure angle is within range */
    if(angle > 180)
        angle = 180;
    /* Set servo angle using PWM */
    PWM_voidSetServoAngle(angle);
    /* Small delay for servo to reach position */
    TIMER0_voidDelayMs(200);
   
}

void SERVO_voidSweep(void)
{
    u8 angle;
    /* Sweep from 0 to 180 degrees */
    for(angle = 0; angle <= 180; angle += 10)
    {
        PWM_voidSetServoAngle(angle);
        TIMER0_voidDelayMs(100);
        
    }
    /* Sweep back from 180 to 0 degrees */
    for(angle = 180; angle > 0; angle -= 10)
    {
        PWM_voidSetServoAngle(angle);
        TIMER0_voidDelayMs(100);
        
    }
}