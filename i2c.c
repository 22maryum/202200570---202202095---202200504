#include <xc.h>
#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "i2c.h"

#define WDT_CLEAR()   asm("CLRWDT")
#define I2C_TIMEOUT   10000

/* Wait for MSSP to be completely idle */
static void I2C_voidWaitIdle(void)
{
    u16 timeout = I2C_TIMEOUT;
    /* Wait while any I2C operation is in progress */
    /* SSPCON2 bits 0-4: SEN, RSEN, PEN, RCEN, ACKEN */
    /* SSPSTAT bit 2: R/W (transmission in progress) */
    while((SSPCON2 & 0x1F) || GET_BIT(SSPSTAT, 2))
    {
        WDT_CLEAR();
        timeout--;
        if(timeout == 0) break;
    }
}

void I2C_voidInit(void)
{
    /* Set SCL (RC3) and SDA (RC4) as inputs */
    SET_BIT(TRISC, 3);
    SET_BIT(TRISC, 4);

    /* Clear SSPCON2 first */
    SSPCON2 = 0x00;

    /* Set I2C clock 100kHz at 16MHz */
    /* SSPADD = (Fosc / (4 * Fbaud)) - 1 */
    /* SSPADD = (16000000 / (4 * 100000)) - 1 = 39 */
    SSPADD = 39;

    /* Enable I2C Master mode (SSPM = 1000) */
    SSPCON = 0x28;

    /* Clear SSPIF flag */
    CLR_BIT(PIR1, 3);

    WDT_CLEAR();
}

void I2C_voidStart(void)
{
    I2C_voidWaitIdle();
    CLR_BIT(PIR1, 3);        /* Clear SSPIF before start */
    SET_BIT(SSPCON2, 0);     /* SEN = 1, initiate start condition */
    /* Wait for start to complete */
    u16 timeout = I2C_TIMEOUT;
    while(!GET_BIT(PIR1, 3))
    {
        WDT_CLEAR();
        timeout--;
        if(timeout == 0) break;
    }
    CLR_BIT(PIR1, 3);        /* Clear SSPIF */
}

void I2C_voidStop(void)
{
    I2C_voidWaitIdle();
    CLR_BIT(PIR1, 3);        /* Clear SSPIF before stop */
    SET_BIT(SSPCON2, 2);     /* PEN = 1, initiate stop condition */
    /* Wait for stop to complete */
    u16 timeout = I2C_TIMEOUT;
    while(!GET_BIT(PIR1, 3))
    {
        WDT_CLEAR();
        timeout--;
        if(timeout == 0) break;
    }
    CLR_BIT(PIR1, 3);        /* Clear SSPIF */
}

void I2C_voidWrite(u8 data)
{
    u16 timeout = I2C_TIMEOUT;
    I2C_voidWaitIdle();
    CLR_BIT(PIR1, 3);        /* Clear SSPIF */
    SSPBUF = data;           /* Load data into buffer */
    /* Wait for transmission to complete */
    while(!GET_BIT(PIR1, 3))
    {
        WDT_CLEAR();
        timeout--;
        if(timeout == 0) break;
    }
    CLR_BIT(PIR1, 3);        /* Clear SSPIF */
    WDT_CLEAR();
}

u8 I2C_u8Read(u8 ack)
{
    u8 data;
    u16 timeout = I2C_TIMEOUT;

    I2C_voidWaitIdle();
    CLR_BIT(PIR1, 3);
    SET_BIT(SSPCON2, 3);     /* RCEN = 1, enable receive */

    /* Wait for byte to be received */
    while(!GET_BIT(PIR1, 3))
    {
        WDT_CLEAR();
        timeout--;
        if(timeout == 0) break;
    }
    CLR_BIT(PIR1, 3);

    data = SSPBUF;           /* Read received data */

    I2C_voidWaitIdle();

    /* Send ACK or NACK */
    if(ack == 1)
        CLR_BIT(SSPCON2, 5); /* ACKDT = 0 ? ACK */
    else
        SET_BIT(SSPCON2, 5); /* ACKDT = 1 ? NACK */

    SET_BIT(SSPCON2, 4);     /* ACKEN = 1, send ACK/NACK */
    I2C_voidWaitIdle();

    WDT_CLEAR();
    return data;
}