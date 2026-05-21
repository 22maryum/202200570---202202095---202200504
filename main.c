#include <xc.h>
#include "../SERVICES/std_types.h"
#include "../SERVICES/bit_math.h"
#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/TIMER0/timer0.h"
#include "../MCAL/UART/uart.h"
#include "../HAL/DHT11/dht11.h"
#include "../HAL/FAN/fan.h"
#include "../HAL/SOIL/soil.h"
#include "../HAL/PUMP/pump.h"
#include "../HAL/LDR/ldr.h"
#include "../HAL/BUZZER/buzzer.h"

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

static void sendNumber(u8 num)
{
    u8 digits[3];
    u8 i = 0;
    if(num == 0) { UART_voidSendChar('0'); return; }
    while(num > 0) { digits[i++] = (num % 10) + '0'; num /= 10; }
    while(i > 0)   { i--; UART_voidSendChar(digits[i]); }
}

static void sendNumber16(u16 num)
{
    u8 digits[5];
    u8 i = 0;
    if(num == 0) { UART_voidSendChar('0'); return; }
    while(num > 0) { digits[i++] = (num % 10) + '0'; num /= 10; }
    while(i > 0)   { i--; UART_voidSendChar(digits[i]); }
}

/* 3 short beeps = sensor error */
static void beepError(void)
{
    u8 i;
    for(i = 0; i < 3; i++)
    {
        BUZZER_voidBeep(100);
        TIMER0_voidDelayMs(100);
    }
}

/* 1 long beep = soil dry alert */
static void beepDry(void)
{
    BUZZER_voidBeep(500);
}

/* 2 medium beeps = temperature high */
static void beepHot(void)
{
    BUZZER_voidBeep(200);
    TIMER0_voidDelayMs(100);
    BUZZER_voidBeep(200);
}

static void shutdownAll(void)
{
    RD0 = 0;
    RD1 = 0;
    FAN_voidTurnOff();
    PUMP_voidTurnOff();
    BUZZER_voidTurnOff();
}

void main(void)
{
    DHT11_Data_t dhtData;
    u8  soilCondition;
    u8  ldrCondition;
    u16 soilRaw;

    ADCON1 = 0x00;
    TRISA  = 0xFF;
    TRISC  = 0x00;
    TRISD  = 0x00;
    TRISB  = 0xFF;

    GPIO_voidInit();
    TIMER0_voidInit();
    UART_voidInit();
    DHT11_voidInit();
    FAN_voidInit();
    SOIL_voidInit();
    PUMP_voidInit();
    LDR_voidInit();
    BUZZER_voidInit();

    RD0 = 0;
    RD1 = 0;

    TIMER0_voidDelayMs(2000);
    UART_voidSendString("System started\r\n");

    while(1)
    {
        /* ---- LDR master switch ---- */
        ldrCondition = LDR_u8GetCondition();

        if(ldrCondition == LDR_CONDITION_DARK)
        {
            shutdownAll();
            UART_voidSendString("DARK - all off\r\n");
            TIMER0_voidDelayMs(2000);
            continue;
        }

        UART_voidSendString("LIGHT - sensors on\r\n");

        /* ---- Soil sensor ---- */
        soilCondition = SOIL_u8GetCondition();
        soilRaw       = SOIL_u16ReadRaw();

        UART_voidSendString("Soil: ");
        sendNumber16(soilRaw);
        UART_voidSendString(" ");

        if(soilCondition == SOIL_CONDITION_DRY)
        {
            RD0 = 1;
            PUMP_voidTurnOn();
            beepDry();             /* 1 long beep ? very dry */
            UART_voidSendString("DRY Pump:ON Beep:LONG\r\n");
        }
        else if(soilCondition == SOIL_CONDITION_LOW)
        {
            RD0 = 1;
            PUMP_voidTurnOn();
            BUZZER_voidBeep(200);  /* 1 short beep ? low moisture */
            UART_voidSendString("LOW Pump:ON Beep:SHORT\r\n");
        }
        else
        {
            RD0 = 0;
            PUMP_voidTurnOff();
            UART_voidSendString("WET Pump:OFF\r\n");
        }

        /* ---- DHT11 ---- */
        dhtData = DHT11_dataRead();

        if(dhtData.status == DHT11_OK)
        {
            UART_voidSendString("Temp:");
            sendNumber(dhtData.temperature);
            UART_voidSendString("C Humi:");
            sendNumber(dhtData.humidity);
            UART_voidSendString("%\r\n");

            if(dhtData.temperature >= 30)
            {
                RD1 = 1;
                FAN_voidTurnOn();
                beepHot();         /* 2 medium beeps ? too hot */
                UART_voidSendString("Fan:ON Beep:HOT\r\n");
            }
            else
            {
                RD1 = 0;
                FAN_voidTurnOff();
                UART_voidSendString("Fan:OFF\r\n");
            }
        }
        else
        {
            RD1 = 0;
            FAN_voidTurnOff();
            beepError();           /* 3 short beeps ? sensor fault */
            UART_voidSendString("DHT11 ERROR Beep:ERROR\r\n");
        }

        TIMER0_voidDelayMs(2000);
    }
}