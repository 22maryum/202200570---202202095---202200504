#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0/timer0.h"
#include "dht11.h"


/* Timeout for DHT11 response loops */
#define DHT11_TIMEOUT 1000

void DHT11_voidInit(void)
{
    /* Set DHT11 pin as output initially */
    GPIO_voidSetPinDirection(DHT11_PORT, DHT11_PIN, OUTPUT);
    /* Set pin high initially */
    GPIO_voidSetPinValue(DHT11_PORT, DHT11_PIN, HIGH);
}

static u8 DHT11_u8ReadByte(void)
{
    u8 i;
    u8 data = 0;
    u16 timeout;

    for(i = 0; i < 8; i++)
    {
        /* Wait for pin to go high with timeout */
        timeout = DHT11_TIMEOUT;
        while(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == LOW)
        {
            
            timeout--;
            if(timeout == 0) return 0;  /* Return 0 if stuck */
        }

        /* Wait 30us */
        TIMER0_voidDelayUs(30);

        /* If pin still high then bit is 1 */
        if(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == HIGH)
        {
            data |= (1 << (7 - i));

            /* Wait for pin to go low with timeout */
            timeout = DHT11_TIMEOUT;
            while(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == HIGH)
            {
                
                timeout--;
                if(timeout == 0) return 0;  /* Return 0 if stuck */
            }
        }
    }
    return data;
}

DHT11_Data_t DHT11_dataRead(void)
{
    DHT11_Data_t result;
    u8 hum_int, hum_dec, temp_int, temp_dec, checksum;
    u16 timeout;

    /* Default status is error */
    result.status = DHT11_ERROR;

    /* Send start signal */
    GPIO_voidSetPinDirection(DHT11_PORT, DHT11_PIN, OUTPUT);
    GPIO_voidSetPinValue(DHT11_PORT, DHT11_PIN, LOW);
    TIMER0_voidDelayMs(18);
    GPIO_voidSetPinValue(DHT11_PORT, DHT11_PIN, HIGH);
    TIMER0_voidDelayUs(30);

    /* Switch to input to read response */
    GPIO_voidSetPinDirection(DHT11_PORT, DHT11_PIN, INPUT);

    /* Wait for DHT11 response with timeout */
    timeout = DHT11_TIMEOUT;
    while(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == HIGH)
    {
       
        timeout--;
        if(timeout == 0) return result;  /* Return error if no response */
    }

    if(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == LOW)
    {
        /* Wait for response to finish with timeout */
        timeout = DHT11_TIMEOUT;
        while(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == LOW)
        {
            
            timeout--;
            if(timeout == 0) return result;  /* Return error if stuck */
        }

        timeout = DHT11_TIMEOUT;
        while(GPIO_u8GetPinValue(DHT11_PORT, DHT11_PIN) == HIGH)
        {
            
            timeout--;
            if(timeout == 0) return result;  /* Return error if stuck */
        }

        /* Read 5 bytes of data */
        hum_int  = DHT11_u8ReadByte();
        hum_dec  = DHT11_u8ReadByte();
        temp_int = DHT11_u8ReadByte();
        temp_dec = DHT11_u8ReadByte();
        checksum = DHT11_u8ReadByte();

        /* Verify checksum */
        if(checksum == (hum_int + hum_dec + temp_int + temp_dec))
        {
            result.humidity    = hum_int;
            result.temperature = temp_int;
            result.status      = DHT11_OK;
        }
    }
    return result;
}