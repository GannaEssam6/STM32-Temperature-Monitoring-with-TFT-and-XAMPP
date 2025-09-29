/*
 * main.c
 *
 *  Created on: Sep 12, 2025
 *      Author: Ganaa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"
#include "MSPI_Interface.h"
#include "MSYSTIC_Interface.h"
#include "MADC_Interface.h"
#include "MUSART_Interface.h"

#include "HTFT_Interface.h"
#include "TFT_Image.h"

// ---------------- Constants ----------------
#define VREF            3.3
#define ADC_RESOLUTION  4095.0
#define LM35_SCALE      100

// Convert ADC raw value to temperature in Celsius
u32 Convert_ADCValue_To_Temperature(u16 adc_val)
{
    u32 temperature = (((u32)adc_val * VREF * LM35_SCALE) / ADC_RESOLUTION);
    return temperature;
}

int main(void)
{
    // ---------------- RCC (Clock System) ----------------
    MRCC_Init();
    MRCC_EnablePeripheral(AHB1_BUS, GPIOA);   // Enable GPIOA
    MRCC_EnablePeripheral(APB2_BUS, SPI1);    // Enable SPI1
    MRCC_EnablePeripheral(APB2_BUS, USART1);  // Enable USART1
    MRCC_EnablePeripheral(APB2_BUS, ADC1);    // Enable ADC1

    // ---------------- SPI Pins (for TFT) ----------------
    MGPIO_void_SetPinMode(PORTA, PIN5, ALTERNATIVE_FUNC);   // PA5 -> SCK
    MGPIO_void_AltFunConfig(PORTA, PIN5, AF5);
    MGPIO_void_SetPinMode(PORTA, PIN7, ALTERNATIVE_FUNC);   // PA7 -> MOSI
    MGPIO_void_AltFunConfig(PORTA, PIN7, AF5);

    // ---------------- USART1 Pins ----------------
    MGPIO_void_SetPinMode(PORTA, PIN9, ALTERNATIVE_FUNC);   // PA9  -> TX
    MGPIO_void_AltFunConfig(PORTA, PIN9, AF7);
    MGPIO_void_SetPinMode(PORTA, PIN10, ALTERNATIVE_FUNC);  // PA10 -> RX
    MGPIO_void_AltFunConfig(PORTA, PIN10, AF7);

    // ---------------- ADC Input Pin ----------------
    MGPIO_void_SetPinMode(PORTA, PIN2, ANALOG); // PA2 (ADC1_IN2) for LM35

    // ---------------- LEDs Output ----------------
    // Cold LED on PA3
    MGPIO_void_SetPinMode(PORTA, PIN3, OUTPUT);
    MGPIO_void_OutputConfig(PORTA, PIN3, PUSH_PULL, LOW_SPEED);
    // Warm LED on PA4
    MGPIO_void_SetPinMode(PORTA, PIN4, OUTPUT);
    MGPIO_void_OutputConfig(PORTA, PIN4, PUSH_PULL, LOW_SPEED);
    // Hot LED on PA6
    MGPIO_void_SetPinMode(PORTA, PIN6, OUTPUT);
    MGPIO_void_OutputConfig(PORTA, PIN6, PUSH_PULL, LOW_SPEED);

    // ---------------- Peripherals Init ----------------
    MSTK_voidInit();           // Systick (for delay)
    MSPI_voidMasterInit();     // SPI Master (for TFT)
    HTFT_voidInit();           // TFT Init
    MADC1_voidInit();          // ADC Init
    MUSART1_voidInit();        // USART1 Init @ 9600 baud

    // ---------------- Display Project Logo ----------------
    HTFT_voidDisplay(Image_Project);
    MSTK_voidDelayms(1000);

    // ---------------- Main Loop ----------------
    while (1)
    {
        // 1. Read raw ADC value from channel 2 (LM35)
        u16 adc_raw = MADC1_u16ReadChannel(2);

        // 2. Convert to Celsius
        u32 temperature = Convert_ADCValue_To_Temperature(adc_raw);


        // 3. Decide based on temperature range
        if (temperature <= 30)
        {
            // Display "Cold" image
            HTFT_voidDisplay(Image_Cold);

            // Turn ON LED1, OFF others
            MGPIO_void_WritePinValue(PORTA, PIN3, HIGH);
            MGPIO_void_WritePinValue(PORTA, PIN4, LOW);
            MGPIO_void_WritePinValue(PORTA, PIN6, LOW);

            // Send text over USART
            MUSART1_voidSendString((u8*)"Cold\r\n");
        }
        else if (temperature > 30 && temperature <= 50)
        {
            // Display "Warm" image
            HTFT_voidDisplay(Image_Warm);

            // Turn ON LED2, OFF others
            MGPIO_void_WritePinValue(PORTA, PIN3, LOW);
            MGPIO_void_WritePinValue(PORTA, PIN4, HIGH);
            MGPIO_void_WritePinValue(PORTA, PIN6, LOW);

            // Send text over USART
            MUSART1_voidSendString((u8*)"Warm\r\n");
        }
        else
        {
            // Display "Hot" image
            HTFT_voidDisplay(Image_Hot);

            // Turn ON LED3, OFF others
            MGPIO_void_WritePinValue(PORTA, PIN3, LOW);
            MGPIO_void_WritePinValue(PORTA, PIN4, LOW);
            MGPIO_void_WritePinValue(PORTA, PIN6, HIGH);

            // Send text over USART
            MUSART1_voidSendString((u8*)"Hot\r\n");
        }

        // 4. Send numeric value too
        u8 buffer[20];
        sprintf(buffer, "Temp=%d\r\n", temperature);
        MUSART1_voidSendString((u8*)buffer);

        // 5. Delay before next reading
        MSTK_voidDelayms(1000);
    }

    return 0;
}
