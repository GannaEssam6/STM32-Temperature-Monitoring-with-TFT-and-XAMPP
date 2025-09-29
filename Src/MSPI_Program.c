/*

 * MSPI_Program.c
 *
 *  Created on: Sep 3, 2025
 *      Author: Ganaa
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MSPI_Interface.h"
#include "MSPI_Private.h"


void MSPI_voidMasterInit()
{
	//Hardware or software SSM/SSI
	SPI1->CR1 |=(1<<SSM);
	SPI1->CR1 |=(1<<SSI);
	//Master mode
	SPI1->CR1 |=(1<<MSTR);
	//Direction (Full duplex)
	SPI1->CR1 &=~(1<<BIDIMODE);
	//MSB or LSB
	SPI1->CR1 &=~(1<<LSBFIRST);
	//CPOL
	SPI1->CR1 |=(1<<CPOL);
	//CPHA
	SPI1->CR1 &=~(1<<CPHA);
	//clock
	//SPI1->CR1 &=~(CLK_MUSK<<BR0);
	//SPE enable
	SPI1->CR1 |=(1<<SPE);

}
void MSPI_voidSlaveInit()
{
	//Hardware or software SSM/SSI
	//SPI1->CR1 &=~(1<<SSM);
	//Slave mode
	SPI1->CR1 &=~(1<<MSTR);
	//Direction (Full duplex)
	SPI1->CR1 &=~(1<<BIDIMODE);
	//MSB or LSB
	SPI1->CR1 &=~(1<<LSBFIRST);
	//CPOL
	SPI1->CR1 |=(1<<CPOL);
	//CPHA
	SPI1->CR1 &=~(1<<CPHA);
	//clock
	//SPI1->CR1 &=~(CLK_MUSK<<BR0);
	//SPE enable
	SPI1->CR1 |=(1<<SPE);
}
u16 MSPI_u16Tranceive(u16 Copy_u16Data)
{
	//Wait till Transmit
	while(!GET_BIT(SPI1->SR,TXE));
	SPI1->DR=Copy_u16Data;
	//Wait till Receive
	while(!GET_BIT(SPI1->SR,RXNE));
	return (u16)(SPI1->DR);

}




