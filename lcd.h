#ifndef LCD_H
#define LCD_H

#include "../../SERVICES/std_types.h"

void LCD_voidInit(void);
void LCD_voidClear(void);
void LCD_voidSetCursor(u8 row, u8 col);
void LCD_voidSendChar(u8 data);
void LCD_voidSendString(const char *str);
void LCD_voidSendNumber(u16 num);

#endif