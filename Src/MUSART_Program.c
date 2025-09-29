#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUSART_Interface.h"
#include "MUSART_Private.h"


void MUSART1_voidInit()
{
    // Oversampling = 16
	USART1->CR1.OVER8=0;
	// Baud rate = 115200 @ 16 MHz
	USART1->BRR = (104 << 4) | 3;   // 0x0683
    // Word length = 8 bit
    USART1->CR1.M=0;
    // Disable parity
    USART1->CR1.PCE=0;
    // Enable USART
    USART1->CR1.UE=1;
    // Enable TX
    USART1->CR1.TE=1;
    // Enable RX
    USART1->CR1.RE=1;
}

void MUSART1_voidSendData(u8 Copy_u8Data)
{
    //Wait until TXE
    while (!GET_BIT(USART1->SR,TXE));
    USART1->DR = Copy_u8Data ;
}

u8 MUSART1_u8ReceiveData()
{
    //Wait until RXNE
    while (!GET_BIT(USART1->SR,RXNE));
    return (u8)(USART1->DR);
}

void MUSART1_voidSendString(u8 *Copy_pu8Str)
{
    u8 i = 0;
    // Loop until the null terminator '\0'
    while (Copy_pu8Str[i] != '\0')
    {
        // Send each character
        MUSART1_voidSendData(Copy_pu8Str[i]);
        i++;
    }
}


void MUSART1_voidReceiveString(u8 *Copy_pu8Str)
{
    u8 i = 0;
    u8 data;

    while (1)
    {
        // Wait for a new character from USART
        data = MUSART1_u8ReceiveData();

        if (data == '\r')  // Stop when Enter key is received
        {
            Copy_pu8Str[i] = '\0';  // Terminate the string
            break;
        }
        else
        {
            // Store received character into the buffer
            Copy_pu8Str[i] = data;
            i++;
        }
    }
}


