#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "uart.h"
#include <xc.h>

void UART_voidInit(void)
{
    /* Baud rate = 9600 for 16MHz, BRGH=1: 16000000/(16*9600)-1 = 103 */
    SPBRG = 103;
    
    /* BRGH = 1 (high speed mode - more accurate baud rate) */
    SET_BIT(TXSTA, 2);
    
    /* TX enable */
    SET_BIT(TXSTA, 5);
    
    /* Serial port enable */
    SET_BIT(RCSTA, 7);
    
    /* RX enable */
    SET_BIT(RCSTA, 4);
}

void UART_voidSendChar(u8 data)
{
    u16 timeout = 10000;
    /* Wait until transmit shift register is empty */
    while(!GET_BIT(TXSTA, 1))   // TRMT bit = transmit shift register empty
    {
        timeout--;
        if(timeout == 0) break;
    }
    TXREG = data;
}

void UART_voidSendString(const char *str)
{
    /* NULL check to prevent crash */
    if(str == 0) return;
    /* Send each character until null terminator */
    while(*str != '\0')
    {
        UART_voidSendChar(*str);
        str++;
    }
}

u8 UART_u8ReceiveChar(void)
{
    u16 timeout = 1000;
    /* Wait until data is received with timeout */
    while(!GET_BIT(PIR1, 5))
    {
        timeout--;
        if(timeout == 0) return 0;  /* Return 0 if no data */
    }
    return RCREG;
}