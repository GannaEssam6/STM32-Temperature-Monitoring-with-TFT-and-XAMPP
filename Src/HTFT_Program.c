#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_Interface.h"
#include "MSYSTIC_Interface.h"
#include "MSPI_Interface.h"

#include "HTFT_Interface.h"
#include "HTFT_Private.h"
#include "HTFT_Config.h"


void HTFT_voidInit()
{
	//Configure Control pin &Reset pin
	MGPIO_void_SetPinMode(TFT_PORT,CONTROL_PIN,OUTPUT);
	MGPIO_void_OutputConfig(TFT_PORT,CONTROL_PIN,PUSH_PULL,LOW_SPEED);
	MGPIO_void_SetPinMode(TFT_PORT,RST_PIN,OUTPUT);
	MGPIO_void_OutputConfig(TFT_PORT,RST_PIN,PUSH_PULL,LOW_SPEED);

	//Reset Sequence
	MGPIO_void_SetAtomicPinValue(TFT_PORT,RST_PIN,HIGH);
	MSTK_voidDelayus(100);
	MGPIO_void_SetAtomicPinValue(TFT_PORT,RST_PIN,LOW);
	MSTK_voidDelayus(1);
	MGPIO_void_SetAtomicPinValue(TFT_PORT,RST_PIN,HIGH);
	MSTK_voidDelayus(100);
	MGPIO_void_SetAtomicPinValue(TFT_PORT,RST_PIN,LOW);
	MSTK_voidDelayus(100);
	MGPIO_void_SetAtomicPinValue(TFT_PORT,RST_PIN,HIGH);
	MSTK_voidDelayms(120);

	//Sleep out
	HTFT_voidWriteCommand(SLEEP_OUT);
	MSTK_voidDelayms(10);

	//Select Color mode
	HTFT_voidWriteCommand(COLOR_MODE);
	HTFT_voidWriteData(RGB565);

	//Display on
	HTFT_voidWriteCommand(DISPLAY_ON);
}
static void HTFT_voidWriteData(u8 Copy_u8Data)
{
	MGPIO_void_SetAtomicPinValue(TFT_PORT,CONTROL_PIN,HIGH);
	(void)MSPI_u16Tranceive(Copy_u8Data);
}
static void HTFT_voidWriteCommand(u8 Copy_u8CMD)
{
	MGPIO_void_SetAtomicPinValue(TFT_PORT,CONTROL_PIN,LOW);
	(void)MSPI_u16Tranceive(Copy_u8CMD);
}
void HTFT_voidDisplay(const u16*Copy_pu16PTR)
{
	u16 Local_u16Iteartor;
	u8 Local_u8HighPart,Local_u8LowPart;
	//Set x
	HTFT_voidWriteCommand(X_DIRECTION);
	HTFT_voidWriteData(START_X_B0);
	HTFT_voidWriteData(START_X_B1);
	HTFT_voidWriteData(END_X_B0);
	HTFT_voidWriteData(END_X_B1);

	//Set Y
	HTFT_voidWriteCommand(Y_DIRECTION);
	HTFT_voidWriteData(START_Y_B0);
	HTFT_voidWriteData(START_Y_B1);
	HTFT_voidWriteData(END_Y_B0);
	HTFT_voidWriteData(END_Y_B1);

	//Write on the screen
	HTFT_voidWriteCommand(SCREEN_WRITE);

	for(Local_u16Iteartor=0;Local_u16Iteartor<IMAGE_SIZE;Local_u16Iteartor++)
	{
		Local_u8LowPart=(u8)Copy_pu16PTR[Local_u16Iteartor]; //lsb
		Local_u8HighPart=(u8)(Copy_pu16PTR[Local_u16Iteartor]>>8);  //msb

		HTFT_voidWriteData(Local_u8HighPart);
		HTFT_voidWriteData(Local_u8LowPart);
	}

}
