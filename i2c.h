#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"

/* I2C LCD Address */
#define LCD_I2C_ADDRESS   0x27

void I2C_voidInit(void);
void I2C_voidStart(void);
void I2C_voidStop(void);
void I2C_voidWrite(u8 data);
u8   I2C_u8Read(u8 ack);

#endif