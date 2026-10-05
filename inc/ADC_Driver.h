#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include "STM32F030x8.h"

typedef enum {
    ADC_RESOLUTION_12BIT = 0,
    ADC_RESOLUTION_10BIT = 1,
    ADC_RESOLUTION_8BIT  = 2,
    ADC_RESOLUTION_6BIT  = 3
} ADC_Resolution_t;

typedef enum {
    ADC_SAMPLE_1_5 = 0,
    ADC_SAMPLE_7_5 = 1,
    ADC_SAMPLE_13_5 = 2,
    ADC_SAMPLE_28_5 = 3,
    ADC_SAMPLE_41_5 = 4,
    ADC_SAMPLE_55_5 = 5,
    ADC_SAMPLE_71_5 = 6,
    ADC_SAMPLE_239_5 = 7
} ADC_SampleTime_t;

typedef struct {
    ADC_Resolution_t Resolution;
    ADC_SampleTime_t SamplingTime;
    uint8_t Channel;
    uint8_t Continuous;
} ADC_InitTypeDef;

void ADC_Init(ADC_TypeDef *ADCx, const ADC_InitTypeDef *config);
int ADC_Read(ADC_TypeDef *ADCx, uint8_t channel, uint16_t *value);
#endif
