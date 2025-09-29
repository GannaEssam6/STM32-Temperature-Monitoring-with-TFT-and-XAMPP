/*
 * MRCC_Interface.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Ganaa
 */

#ifndef MRCC_INTERFACE_H_
#define MRCC_INTERFACE_H_

typedef enum {
	AHB1_BUS,
	AHB2_BUS,
	APB1_BUS,
	APB2_BUS
}System_Bus_t;


void MRCC_Init();
void MRCC_EnablePeripheral(System_Bus_t Copy_uddtBus, u8 Copy_uddtperipheral);
void MRCC_DisablePeripheral(System_Bus_t Copy_uddtBus, u8 Copy_uddtperipheral);

/*******AHB1*******/
#define GPIOA   0
#define GPIOB   1
#define GPIOC   2
#define GPIOD   3
#define GPIOE   4
#define GPIOH   7
#define CRC     12
#define DMA1    21
#define DMA2    22
/*******AHB2*******/
#define OTGFS   7
/*******APB1*******/
#define TIM2    0
#define TIM3    1
#define TIM4    2
#define TIM5    3
#define WWDG    11
#define SPI2    14
#define SPI3    15
#define USART2  17
#define I2C1    21
#define I2C2    22
#define I2C3    23
#define PWR     28
/*******APB2*******/
#define TIM1    0
#define USART1  4
#define USART6  5
#define ADC1    8
#define SDIO    11
#define SPI1    12
#define SPI4    13
#define SYSCF    14
#define TIM9    16
#define TIM10   17
#define TIM11   18

#endif /* MRCC_INTERFACE_H_ */
