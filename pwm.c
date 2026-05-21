#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "pwm.h"
#include <xc.h>

void PWM_voidInit(void)
{
    /* Set RC2 as output for PWM */
    CLR_BIT(TRISC, 2);
    /* PWM mode on CCP1 */
    SET_BIT(CCP1CON, 2);
    SET_BIT(CCP1CON, 3);
    /* Set period for 50Hz (20ms) for servo */
    PR2 = 249;
    /* Prescaler 1:16 */
    SET_BIT(T2CON, 1);
    SET_BIT(T2CON, 0);
    /* Start Timer2 */
    SET_BIT(T2CON, 2);
}

void PWM_voidSetDuty(u8 duty)
{
    /* Set duty cycle */
    CCPR1L = duty;
}

void PWM_voidSetServoAngle(u8 angle)
{
    u8 duty;
    /* Convert angle (0-180) to duty cycle
       SG90 needs 5% to 10% duty cycle
       at 50Hz: 0 degrees = 12, 180 degrees = 25 */
    duty = 12 + ((angle * 13) / 180);
    CCPR1L = duty;
    
}