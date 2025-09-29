/*
 * MRCC_Program.c\
 *
 *  Created on: Aug 17, 2025
 *      Author: Ganaa
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MRCC_Interface.h"
#include "MRCC_Private.h"
#include "MRCC_Config.h"

void MRCC_Init()
{
	/******************HSI_Config******************/
	#if (SYSTEM_CLOCK==HSI_CLOCK)
	//HSI ON
	 RCC->CR |= (1<<HSION);  //SET_BIT(RCC->CR,HSION)
	//Wait till ready
     while (!GET_BIT(RCC->CR,HSIRDY));
    //Switch HSI
     RCC->CFGR &=~(SW_MUSK<<SW0);
     RCC->CFGR |=(HSI_OSC<<SW0);

    /******************HSE_Config******************/
	#elif (SYSTEM_CLOCK==HSE_CLOCK)
		#if (HSE_OSC==MECHANICAL_CLK)
          RCC->CR &=~(1<<HSEBYP)
		#elif(HSE_OSC==RC_CLK)
          RCC->CR |=(1<<HSEBYP)
		#endif
    //HSE ON
     RCC->CR |= (1<<HSEON);
    //Wait till ready
     while (!GET_BIT(RCC->CR,HSERDY));
    //Switch HSE
     RCC->CFGR &=~(SW_MUSK<<SW0);
     RCC->CFGR |=(HSE_OSC<<SW0);
    //Disable HSI
     RCC->CR &=~(1<<HSION);

    /******************PLL_Config******************/
	#elif (SYSTEM_CLOCK==PLL)
    //Enable HSI as a source for PLL
     RCC->CR |= (1<<HSION);
     while (!GET_BIT(RCC->CR,HSIRDY));
    //Clear PLLM, PLLN, PLLP bits
     RCC->PLLCFGR &= ~((0x3F << 0) | (0x1FF << 6) | (0x3 << 16));
    //ConfigurePLL(M=16, N=336, P=4)
     RCC->PLLCFGR |=(PLLM<<0);
     RCC->PLLCFGR |=(PLLN<<6);
     RCC->PLLCFGR |=(PLLP<<16);
     RCC->PLLCFGR &=~(1<<PLLSRC);  //Choose HSI clock as PLL source
    //PLL ON
     RCC->CR |= (1<<PLLON);
    //Wait till ready
     while (!GET_BIT(RCC->CR,PLLRDY));
    //Switch PLL
     RCC->CFGR &=~(SW_MUSK<<SW0);
     RCC->CFGR |=(PLL_OSC<<SW0);
    //Disable HSI
     RCC->CR &=~(1<<HSION);
     RCC->CR &=~(1<<HSEON);
	#endif
}

void MRCC_EnablePeripheral(System_Bus_t Copy_uddtBus, u8 Copy_uddtperipheral)
{
	switch(Copy_uddtBus)
	{
	case AHB1_BUS:
		RCC->AHB1ENR |=(1<<Copy_uddtperipheral);
		break;
	case AHB2_BUS:
		RCC->AHB2ENR |=(1<<Copy_uddtperipheral);
		break;
	case APB1_BUS:
		RCC->APB1ENR |=(1<<Copy_uddtperipheral);
		break;
	case APB2_BUS:
		RCC->APB2ENR |=(1<<Copy_uddtperipheral);
		break;
	default:
	   break;
	}
}

void MRCC_DisablePeripheral(System_Bus_t Copy_uddtBus, u8 Copy_uddtperipheral)
{
	switch(Copy_uddtBus)
	{
	case AHB1_BUS:
		RCC->AHB1ENR &=~(1<<Copy_uddtperipheral);
		break;
	case AHB2_BUS:
		RCC->AHB2ENR &=~(1<<Copy_uddtperipheral);
		break;
	case APB1_BUS:
		RCC->APB1ENR &=~(1<<Copy_uddtperipheral);
		break;
	case APB2_BUS:
		RCC->APB2ENR &=~(1<<Copy_uddtperipheral);
		break;
	default:
		break;
	}
}



