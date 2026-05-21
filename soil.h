#ifndef SOIL_INTERFACE_H
#define SOIL_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/ADC/adc.h"

/* Soil Moisture Threshold Definitions */
#define SOIL_DRY_THRESHOLD    300   /* Below this = very dry */
#define SOIL_LOW_THRESHOLD    600   /* Below this = low moisture */
#define SOIL_WET_THRESHOLD    800   /* Above this = wet enough */

/* Soil Moisture Conditions */
#define SOIL_CONDITION_DRY    0
#define SOIL_CONDITION_LOW    1
#define SOIL_CONDITION_WET    2
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0
void SOIL_voidInit(void);
u16  SOIL_u16ReadRaw(void);
u8   SOIL_u8GetCondition(void);

#endif