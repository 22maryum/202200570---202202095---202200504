
#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"

/* ADC Channel Definitions */
#define ADC_CHANNEL_SOIL    0    /* Soil Sensor on AN0 */
#define ADC_CHANNEL_LDR     1    /* LDR on AN1 */

void ADC_voidInit(void);
u16  ADC_u16Read(u8 channel);

#endif