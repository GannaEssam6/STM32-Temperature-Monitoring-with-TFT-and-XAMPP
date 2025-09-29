#ifndef MADC_INTERFACE_H_
#define MADC_INTERFACE_H_

typedef enum {
    ADC_CHANNEL_0 = 0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,
    ADC_CHANNEL_8,
    ADC_CHANNEL_9,
    ADC_CHANNEL_10,
    ADC_CHANNEL_11,
    ADC_CHANNEL_12,
    ADC_CHANNEL_13,
    ADC_CHANNEL_14,
    ADC_CHANNEL_15,
    ADC_CHANNEL_16, // Internal temperature sensor
    ADC_CHANNEL_17  // Internal reference voltage
} ADC_Channel_t;

void MADC1_voidInit ();
u16 MADC1_u16ReadChannel(u8 channel);

#endif /* MADC_INTERFACE_H_ */
