#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H
#include "STM32F030x4.h"

typedef enum
{
    ADC_RESOLUTION_12BIT = 0x00,
    ADC_RESOLUTION_10BIT = 0x01,
    ADC_RESOLUTION_8BIT  = 0x02,
    ADC_RESOLUTION_6BIT  = 0x03
} ADC_Resolution;

typedef enum
{
    ADC_SAMPLINGTIME_1_5CYCLES = 0x00,
    ADC_SAMPLINGTIME_7_5CYCLES = 0x01,
    ADC_SAMPLINGTIME_13_5CYCLES = 0x02,
    ADC_SAMPLINGTIME_28_5CYCLES = 0x03,
    ADC_SAMPLINGTIME_41_5CYCLES = 0x04,
    ADC_SAMPLINGTIME_55_5CYCLES = 0x05,
    ADC_SAMPLINGTIME_71_5CYCLES = 0x06,
    ADC_SAMPLINGTIME_239_5CYCLES = 0x07
} ADC_SamplingTime;

typedef enum
{
    ADC_CHANNEL_0 = 0U,
    ADC_CHANNEL_1 = 1U,
    ADC_CHANNEL_2 = 2U,
    ADC_CHANNEL_3 = 3U,
    ADC_CHANNEL_4 = 4U,
    ADC_CHANNEL_5 = 5U,
    ADC_CHANNEL_6 = 6U,
    ADC_CHANNEL_7 = 7U,
    ADC_CHANNEL_8 = 8U,
    ADC_CHANNEL_9 = 9U,
    ADC_CHANNEL_10 = 10U,
    ADC_CHANNEL_11 = 11U,
    ADC_CHANNEL_12 = 12U,
    ADC_CHANNEL_13 = 13U,
    ADC_CHANNEL_14 = 14U,
    ADC_CHANNEL_15 = 15U
} ADC_ChannelSelection;

typedef enum
{
    ADC_EXTERNALTRIGGER_NONE = 0U,
    ADC_EXTERNALTRIGGER_RISING = 1U,
    ADC_EXTERNALTRIGGER_FALLING = 2U,
    ADC_EXTERNALTRIGGER_BOTH = 3U
} ADC_ExternalTrigger;

typedef struct DMA_HandleTypeDef DMA_HandleTypeDef;

#define ADC_DATAALIGN_RIGHT 0U
#define ADC_DATAALIGN_LEFT  1U
#define ADC_CONTINUOUS_DISABLE 0U
#define ADC_CONTINUOUS_ENABLE  1U



typedef struct
{
    ADC_Resolution          Resolution;
    ADC_SamplingTime        SamplingTime;
    ADC_ChannelSelection    Selection;
    ADC_ExternalTrigger     ExternalTrigger;
    uint32_t                DataAlignment;
    uint32_t                ContinuousMode;
    DMA_HandleTypeDef      *DMARequest;
} ADC_ConfigTypeDef;

/*ADC functions declarations*/ 
void ADC_Init(ADC_TypeDef *ADCx, const ADC_ConfigTypeDef *config);

/*ADC functions startconversion*/
void ADC_StartConversion(ADC_TypeDef *ADCx);

/*ADC functions read value*/
uint16_t ADC_ReadValue(ADC_TypeDef *ADCx);

/*ADC functions enable/disable*/
void ADC_Enable(ADC_TypeDef *ADCx);
void ADC_Disable(ADC_TypeDef *ADCx);

#endif /* ADC_DRIVER_H */
