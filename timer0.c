#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "timer0.h"
#include <xc.h>

void TIMER0_voidInit(void)
{
    CLR_BIT(OPTION_REG, 5);  /* Timer mode selected */
    CLR_BIT(OPTION_REG, 3);  /* Prescaler assigned to Timer0 */
    CLR_BIT(OPTION_REG, 2);  /* PS2=0 \                      */
    CLR_BIT(OPTION_REG, 1);  /* PS1=0  } prescaler 1:8       */
    SET_BIT(OPTION_REG, 0);  /* PS0=1 /  tick = 4us @8MHz    */
}

void TIMER0_voidDelayUs(u8 time)
{
    /* Prescaler 1:8 @8MHz: 1 tick = 4us.
     * Divide requested us by 4 to get tick count (min 1). */
    u8 ticks = time >> 2;
    if(ticks == 0) ticks = 1;
    while(ticks--)
    {
        TMR0 = 0;
        while(TMR0 < 1);
    }
}

void TIMER0_voidDelayMs(u16 time)
{
    /* Prescaler 1:8 @8MHz: 125 ticks = 1ms */
    while(time--)
    {
        TMR0 = 0;
        while(TMR0 < 125);
    }
}