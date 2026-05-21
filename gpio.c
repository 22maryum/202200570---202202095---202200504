#include <xc.h>
#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "gpio.h"


/* Shadow registers ? match to 0 so all pins start LOW */
static u8 shadow_a = 0x00;
static u8 shadow_b = 0x00;
static u8 shadow_c = 0x00;
static u8 shadow_d = 0x00;


void GPIO_voidInit(void)
{
    /* Force all ports LOW through shadow */
    shadow_a = 0x00;
    shadow_b = 0x00;
    shadow_c = 0x00;
    shadow_d = 0x00;
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
}


void GPIO_voidSetPinDirection(u8 port, u8 pin, u8 dir)
{
    if(port == PORTA_ID)
    {
        if(dir == OUTPUT) CLR_BIT(TRISA, pin);
        else              SET_BIT(TRISA, pin);
    }
    else if(port == PORTB_ID)
    {
        if(dir == OUTPUT) CLR_BIT(TRISB, pin);
        else              SET_BIT(TRISB, pin);
    }
    else if(port == PORTC_ID)
    {
        if(dir == OUTPUT) CLR_BIT(TRISC, pin);
        else              SET_BIT(TRISC, pin);
    }
    else if(port == PORTD_ID)
    {
        if(dir == OUTPUT) CLR_BIT(TRISD, pin);
        else              SET_BIT(TRISD, pin);
    }
}

void GPIO_voidSetPinValue(u8 port, u8 pin, u8 val)
{
    /* Write to shadow first, then write full byte to PORT
     * This avoids the PIC16 read-modify-write hardware bug */
    if(port == PORTA_ID)
    {
        if(val == HIGH) SET_BIT(shadow_a, pin);
        else            CLR_BIT(shadow_a, pin);
        PORTA = shadow_a;
    }
    else if(port == PORTB_ID)
    {
        if(val == HIGH) SET_BIT(shadow_b, pin);
        else            CLR_BIT(shadow_b, pin);
        PORTB = shadow_b;
    }
    else if(port == PORTC_ID)
    {
        if(val == HIGH) SET_BIT(shadow_c, pin);
        else            CLR_BIT(shadow_c, pin);
        PORTC = shadow_c;
    }
    else if(port == PORTD_ID)
    {
        if(val == HIGH) SET_BIT(shadow_d, pin);
        else            CLR_BIT(shadow_d, pin);
        PORTD = shadow_d;
    }
}

u8 GPIO_u8GetPinValue(u8 port, u8 pin)
{
    /* Always read from PORT ? correct for actual pin state */
    u8 result = 0;
    if(port == PORTA_ID)      result = GET_BIT(PORTA, pin);
    else if(port == PORTB_ID) result = GET_BIT(PORTB, pin);
    else if(port == PORTC_ID) result = GET_BIT(PORTC, pin);
    else if(port == PORTD_ID) result = GET_BIT(PORTD, pin);
    return result;
}