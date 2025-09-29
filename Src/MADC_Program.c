#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MADC_Private.h"
#include "MADC_Interface.h"
#include "MGPIO_Interface.h"

// Initialize ADC1
void MADC1_voidInit(void)
{
    // Reset control registers CR1 & CR2
    ADC->CR1 = 0;
    ADC->CR2 = 0;

    // Enable ADC1 (ADON bit = 1)
    SET_BIT(ADC->CR2, ADON);

    // Single conversion mode (disable continuous mode)
    CLR_BIT(ADC->CR2, CONT);

    // Right alignment for data (default)
    CLR_BIT(ADC->CR2, ALIGN);

    // Set sampling time = 3 cycles for all channels
    ADC->SMPR1 = 0x00000000; // Channels 10-18
    ADC->SMPR2 = 0x00000000; // Channels 0-9
}

// Read from a given ADC channel
u16 MADC1_u16ReadChannel(u8 channel)
{
	// Select ADC channel in sequence register (SQR3)
    ADC->SQR3 &= ~(0x1F);        // Clear previous channel
    ADC->SQR3 |= (channel & 0x1F); // Set new channel (0–18)

    // Start conversion (SWSTART bit = 1)
    SET_BIT(ADC->CR2, SWSTART);

    // Wait until conversion is complete (EOC = 1)
    while (GET_BIT(ADC->SR, EOC) == 0);

    // Read result from Data Register
    u16 result = (u16)(ADC->DR & 0xFFFF);

    // Clear EOC flag by reading ADC->DR (already done)

    // Return conversion result
    return result;
}
