#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/ADC/adc.h"
#include "soil.h"


void SOIL_voidInit(void)
{
    /* Initialize ADC for soil sensor */
    ADC_voidInit();
 
}

u16 SOIL_u16ReadRaw(void)
{
    /* Read raw ADC value from soil sensor channel */
   
    return ADC_u16Read(ADC_CHANNEL_SOIL);
}

u8 SOIL_u8GetCondition(void)
{
    u16 soilValue;
    /* Read soil moisture value */
    soilValue = SOIL_u16ReadRaw();
   
    /* Determine moisture condition */
    if(soilValue < SOIL_DRY_THRESHOLD)
        return SOIL_CONDITION_DRY;
    else if(soilValue < SOIL_WET_THRESHOLD)
        return SOIL_CONDITION_LOW;
    else
        return SOIL_CONDITION_WET;
}