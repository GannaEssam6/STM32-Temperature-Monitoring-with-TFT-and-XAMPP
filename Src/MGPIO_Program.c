#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_Interface.h"
#include "MGPIO_Private.h"

void MGPIO_void_SetPinMode(Port_t copy_uddtport,Pin_t copy_uddtpin,Mode_t copy_uddtmode)
{
    switch(copy_uddtport)
    {
        case PORTA: 
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else {
            GPIOA->MODER &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOA->MODER |=(copy_uddtmode<<(2*copy_uddtpin));
        }
        break;
        case PORTB: 
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else {
            GPIOB->MODER &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOB->MODER |=(copy_uddtmode<<(2*copy_uddtpin));
        }
        break;
       case PORTC: 
            GPIOB->MODER &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOB->MODER |=(copy_uddtmode<<(2*copy_uddtpin));
        break; 
    }
}

void MGPIO_void_OutputConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,Output_t copy_uddtoutput,Speed_t copy_uddtspeed)
{
    switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
            GPIOA->OTYPER &=~(1<<copy_uddtpin);
            GPIOA->OTYPER |=(copy_uddtoutput<<copy_uddtpin);
            GPIOA->OSPEEDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOA->OSPEEDR |=(copy_uddtspeed<<(2*copy_uddtpin));
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
            GPIOB->OTYPER &=~(1<<copy_uddtpin);
            GPIOB->OTYPER |=(copy_uddtoutput<<copy_uddtpin);
            GPIOB->OSPEEDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOB->OSPEEDR |=(copy_uddtspeed<<(2*copy_uddtpin));
        }
        break;
        case PORTC: 
            GPIOC->OTYPER &=~(1<<copy_uddtpin);
            GPIOC->OTYPER |=(copy_uddtoutput<<copy_uddtpin);
            GPIOC->OSPEEDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOC->OSPEEDR |=(copy_uddtspeed<<(2*copy_uddtpin));
        break; 
    }
}

void MGPIO_void_WritePinValue(Port_t copy_uddtport,Pin_t copy_uddtpin,Value_t copy_uddtvalue)
{
    switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
            GPIOA->ODR &=~(1<<copy_uddtpin);
            GPIOA->ODR |=(copy_uddtvalue<<copy_uddtpin);
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
        	GPIOA->ODR &=~(1<<copy_uddtpin);
        	GPIOA->ODR |=(copy_uddtvalue<<copy_uddtpin);
        }
        break;
        case PORTC: 
            GPIOC->ODR &=~(1<<copy_uddtpin);
            GPIOC->ODR |=(copy_uddtvalue<<copy_uddtpin);
            break;
    }
}

void MGPIO_void_SetAtomicPinValue(Port_t copy_uddtport,Pin_t copy_uddtpin,Value_t copy_uddtvalue)
{
   switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
            if(copy_uddtvalue==LOW)
            {
              copy_uddtpin+=16;  
            }
            GPIOA->BSRR =(1<<copy_uddtpin);
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
             if(copy_uddtvalue==LOW)
            {
              copy_uddtpin+=16;  
            }
            GPIOB->BSRR =(1<<copy_uddtpin);
        }
        break;
        case PORTC: 
            if(copy_uddtvalue==LOW)
            {
              copy_uddtpin+=16;  
            }
            GPIOC->BSRR =(1<<copy_uddtpin);
            break; 
    }
}

void MGPIO_void_InputConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,Input_t copy_uddtinput)
{
    switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
            GPIOA->PUPDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOA->PUPDR |=(copy_uddtinput<<(2*copy_uddtpin));
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
            GPIOB->PUPDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOB->PUPDR |=(copy_uddtinput<<(2*copy_uddtpin));
        }
        break;
        case PORTC: 
            GPIOC->PUPDR &=~(GPIO_MUSK<<(2*copy_uddtpin));
            GPIOC->PUPDR |=(copy_uddtinput<<(2*copy_uddtpin));
        break; 
    }
}

Value_t MGPIO_u8_ReadPinValue(Port_t copy_uddtport,Pin_t copy_uddtpin)
{
    Value_t Local_u8Value;
    switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
           Local_u8Value = GET_BIT(GPIOA->IDR,copy_uddtpin);
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
           Local_u8Value = GET_BIT(GPIOB->IDR,copy_uddtpin);
        }
        break;
        case PORTC: 
           Local_u8Value = GET_BIT(GPIOC->IDR,copy_uddtpin);
        break; 
    }
    return Local_u8Value;
}

void MGPIO_void_AltFunConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,AF_t copy_uddtaltfun)
{
     switch(copy_uddtport)
    {
        case PORTA:
        if (copy_uddtpin>=13){
           //do nothing 
        }
        else{
          if(copy_uddtpin<8){
            GPIOA->AFRL &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOA->AFRL |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
          else if (copy_uddtpin<16)
          {
            copy_uddtpin-=8;
            GPIOA->AFRH &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOA->AFRH |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
        }
        break;
        case PORTB:
        if ((copy_uddtpin>=3)&&(copy_uddtpin<=5)){
           //do nothing 
        }
        else{
            if(copy_uddtpin<8){
            GPIOB->AFRL &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOB->AFRL |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
          else if (copy_uddtpin<16)
          {
            copy_uddtpin-=8;
            GPIOB->AFRH &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOB->AFRH |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
        }
        break;
        case PORTC: 
           if(copy_uddtpin<8){
            GPIOC->AFRL &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOC->AFRL |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
          else if (copy_uddtpin<16)
          {
            copy_uddtpin-=8;
            GPIOC->AFRH &=~(ALT_MUSK<<(4*copy_uddtpin));
            GPIOC->AFRH |=(copy_uddtaltfun<<(4*copy_uddtpin));
          }
        break; 
    }
}
