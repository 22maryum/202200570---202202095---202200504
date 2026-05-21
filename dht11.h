#ifndef DHT11_INTERFACE_H
#define DHT11_INTERFACE_H

#include "../../SERVICES/std_types.h"
#include "../../SERVICES/bit_math.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/TIMER0/timer0.h"

/* DHT11 Port & Pin Definitions */
#define DHT11_PORT   PORTB_ID
#define DHT11_PIN    0

/* DHT11 Status Definitions */
#define DHT11_OK      0
#define DHT11_ERROR   1
#define LED_RED_PORT    PORTA_ID
#define LED_RED_PIN     0

/* DHT11 Data Structure */
typedef struct
{
    u8 temperature;
    u8 humidity;
    u8 status;
} DHT11_Data_t;

void      DHT11_voidInit(void);
DHT11_Data_t DHT11_dataRead(void);

#endif