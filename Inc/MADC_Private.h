/*
 * MADC_Private.h
 *
 *  Created on: Sep 8, 2025
 *      Author: Ganaa
 */

#ifndef MADC_PRIVATE_H_
#define MADC_PRIVATE_H_

#define MADC_BASE_ADDRESS (0x40012000)

typedef struct{
	u32 SR;
	u32 CR1;
	u32 CR2;
	u32 SMPR1;
	u32 SMPR2;
	u32 JOFR1;
	u32 JOFR2;
	u32 JOFR3;
	u32 JOFR4;
	u32 HTR;
	u32 LTR;
	u32 SQR1;
	u32 SQR2;
	u32 SQR3;
	u32 JSQR;
	u32 JDR1;
	u32 JDR2;
	u32 JDR3;
	u32 JDR4;
	u32 DR;
}MADC_t;

#define ADC ((volatile MADC_t*)MADC_BASE_ADDRESS)

// ---------------- CR2 Register Pins ----------------
#define ADON    0
#define CONT    1
#define ALIGN   11
#define SWSTART 30

// ---------------- SR Register Pins ----------------
#define EOC    1




#endif /* MADC_PRIVATE_H_ */
