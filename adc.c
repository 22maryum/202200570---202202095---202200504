#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/TIMER0/timer0.h"  /* ADDED - was missing! */
#include "adc.h"
#include <xc.h>


void ADC_voidInit(void)
{
    /* Turn ON ADC */
    SET_BIT(ADCON0, 0);
    /* Select Fosc/8 */
    SET_BIT(ADCON0, 6);
    /* Configure all analog pins */
    ADCON1 = 0x80;
}

u16 ADC_u16Read(u8 channel)
{
    u16 result;
    u16 timeout = 1000;

    /* Clear channel bits */
    ADCON0 &= 0b11000111;
    /* Select channel */
    ADCON0 |= (channel << 3);
    /* Small delay before conversion */
    TIMER0_voidDelayUs(10);
    /* Start conversion */
    SET_BIT(ADCON0, 2);
    /* Wait until done with timeout */
    while(GET_BIT(ADCON0, 2))
    {
       
        timeout--;
        if(timeout == 0) break;  /* Escape if stuck */
    }
    /* Read 10-bit result */
    result = (ADRESH << 8) | ADRESL;
    return result;
}