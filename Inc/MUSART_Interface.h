#ifndef MUSART_INTERFACE_H_
#define MUSART_INTERFACE_H_

void MUSART1_voidInit();
void MUSART1_voidSendData(u8 Copy_u8Data);
u8 MUSART1_u8ReceiveData();
void MUSART1_voidSendString(u8 *Copy_pu8Str);
void MUSART1_voidReceiveString(u8 *Copy_pu8Str);


#endif
