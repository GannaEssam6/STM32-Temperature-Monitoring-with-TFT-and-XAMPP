#ifndef MGPIO_INTERFACE_H_
#define MGPIO_INTERFACE_H_

typedef enum {
    PORTA,
    PORTB,
    PORTC
}Port_t;

typedef enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
	PIN5,
    PIN6,
    PIN7,
    PIN8,
    PIN9,
    PIN10,
    PIN11,
    PIN12,
    PIN13,
    PIN14,
    PIN15
}Pin_t;

typedef enum {
    AF0,
    AF1,
    AF2,
    AF3,
    AF4,
	AF5,
    AF6,
    AF7,
    AF8,
    AF9,
    AF10,
    AF11,
    AF12,
    AF13,
    AF14,
    AF15
}AF_t;

typedef enum {
    INPUT,
    OUTPUT,
    ALTERNATIVE_FUNC,
    ANALOG
}Mode_t;

typedef enum {
    PUSH_PULL,
    OPEN_DRAIN
}Output_t;

typedef enum {
    LOW_SPEED,
    MEDIUM_SPEED,
    HIGH_SPEED,
    VHIGH_SPEED
}Speed_t;

typedef enum {
    LOW,
    HIGH
}Value_t;

typedef enum {
    FLOATING,    //no pullup no pulldown
    PULL_UP,
    PULL_DOWN
}Input_t;

typedef enum {
    OK,
    NOK
}Error_t;

void MGPIO_void_SetPinMode(Port_t copy_uddtport,Pin_t copy_uddtpin,Mode_t copy_uddtmode);

/******************************************OUTPUT_MODE******************************************/
void MGPIO_void_OutputConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,Output_t copy_uddtoutput,Speed_t copy_uddtspeed);
void MGPIO_void_WritePinValue(Port_t copy_uddtport,Pin_t copy_uddtpin,Value_t copy_uddtvalue);
void MGPIO_void_SetAtomicPinValue(Port_t copy_uddtport,Pin_t copy_uddtpin,Value_t copy_uddtvalue);

/******************************************INPUT_MODE******************************************/
void MGPIO_void_InputConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,Input_t copy_uddtinput);
Value_t MGPIO_u8_ReadPinValue(Port_t copy_uddtport,Pin_t copy_uddtpin);

/******************************************ALT_FUNC_MODE******************************************/
void MGPIO_void_AltFunConfig(Port_t copy_uddtport,Pin_t copy_uddtpin,AF_t copy_uddtaltfun);




#endif
