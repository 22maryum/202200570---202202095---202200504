#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/I2C/i2c.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "lcd.h"
#include <xc.h>

/* 
 * PCF8574 Pin Mapping (Your Schematic):
 * P7, P6, P5, P4 = Data
 * P3 = Backlight (BL)
 * P2 = E (EN)
 * P1 = RW
 * P0 = RS
 */

/* I2C Address - 0x4E = 0x27 shifted left by 1 with R/W=0 */
#define LCD_ADDR    0x27

#define LCD_BL      0x08
#define LCD_EN      0x04
#define LCD_RS      0x01

/* Write to PCF8574: Start -> Addr -> Data -> Stop */
static void LCD_voidWritePCF(u8 value)
{
    I2C_voidStart();
    I2C_voidWrite(LCD_ADDR);
    I2C_voidWrite(value);
    I2C_voidStop();
}

/* Pulse E: EN=1 wait, EN=0 wait */
static void LCD_voidPulseEN(u8 value)
{
    LCD_voidWritePCF(value | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(value & ~LCD_EN);
    TIMER0_voidDelayMs(1);
}

/* Send command byte (RS=0) */
static void LCD_voidSendCmdByte(u8 cmd)
{
    u8 lcddata;

    /* High nibble, RS=0, BL=1 */
    lcddata = (cmd & 0xF0) | LCD_BL;
    LCD_voidPulseEN(lcddata);

    /* Low nibble, RS=0, BL=1 */
    lcddata = ((cmd << 4) & 0xF0) | LCD_BL;
    LCD_voidPulseEN(lcddata);
}

/* Send data byte (RS=1) */
static void LCD_voidSendDataByte(u8 data)
{
    u8 lcddata;

    /* High nibble, RS=1, BL=1 */
    lcddata = (data & 0xF0) | LCD_RS | LCD_BL;
    LCD_voidPulseEN(lcddata);

    /* Low nibble, RS=1, BL=1 */
    lcddata = ((data << 4) & 0xF0) | LCD_RS | LCD_BL;
    LCD_voidPulseEN(lcddata);

    /* Clear RS after send (optional, like working code) */
    LCD_voidWritePCF(lcddata & ~LCD_RS);
    TIMER0_voidDelayMs(1);
}

void LCD_voidInit(void)
{
    u8 lcddata;

    /* Wait for LCD power-on */
    TIMER0_voidDelayMs(20);

    /* Init sequence: send 0x30 three times */
    lcddata = 0x30;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(5);

    lcddata = 0x30;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(5);

    lcddata = 0x30;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(5);

    /* Switch to 4-bit mode */
    lcddata = 0x20;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);

    /* Function set: 4-bit, 2 lines */
    lcddata = 0x20;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
    lcddata = 0x80;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(5);

    /* Display OFF */
    lcddata = 0x00;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
    lcddata = 0x80;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);

    /* Display ON, cursor OFF */
    lcddata = 0x00;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
    lcddata = 0xC0;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);

    /* Entry mode set */
    lcddata = 0x00;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
    lcddata = 0x20 | LCD_BL;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);

    /* Clear display */
    lcddata = 0x00;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
    lcddata = 0x10;
    LCD_voidWritePCF(lcddata | LCD_EN);
    TIMER0_voidDelayMs(1);
    LCD_voidWritePCF(lcddata & ~LCD_EN);
    TIMER0_voidDelayMs(1);
}

void LCD_voidClear(void)
{
    LCD_voidSendCmdByte(0x01);
    TIMER0_voidDelayMs(3);
}

void LCD_voidSetCursor(u8 row, u8 col)
{
    u8 addr;
    switch(row)
    {
        case 0: addr = 0x80 + col; break;
        case 1: addr = 0xC0 + col; break;
        default: addr = 0x80 + col; break;
    }
    LCD_voidSendCmdByte(addr);
}

void LCD_voidSendChar(u8 data)
{
    LCD_voidSendDataByte(data);
}

void LCD_voidSendString(const char *str)
{
    if(str == 0) return;
    while(*str != '\0')
    {
        LCD_voidSendDataByte(*str);
        str++;
    }
}

void LCD_voidSendNumber(u16 num)
{
    u8 digits[5];
    u8 i = 0;

    if(num == 0)
    {
        LCD_voidSendDataByte('0');
        return;
    }

    while(num > 0)
    {
        digits[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    while(i > 0)
    {
        i--;
        LCD_voidSendDataByte(digits[i]);
    }
}