#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"

void UART_voidInit(void);
void UART_voidSendChar(u8 data);
void UART_voidSendString(const char *str);
u8   UART_u8ReceiveChar(void);

#endif