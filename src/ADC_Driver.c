#include "ADC_Driver.h"
#include "GPIO_Driver.h"
#include "RCC_Driver.h"

#define ADC_CFGR1_RES_MASK (3U << 3U)
#define ADC_SMPR_SMP_MASK  (7U << 0U)
#define ADC_CFGR1_EXTEN_MASK (3U << 10U)
#define ADC_CFGR1_EXTSEL_MASK (7U << 6U)
#define ADC_CFGR1_SCANDIR_MASK (1U << 2U)

void ADC_Init(ADC_TypeDef *ADCx, const ADC_ConfigTypeDef *config)
{
    GPIO_InitTypeDef gpioConfig = {
        .GPIOx = GPIOA,
        .Pin = (uint32_t)config->Selection,
        .Mode = GPIO_MODE_ANALOG,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_NO_PULL
    };

    /* RCC APB2 ADCEN: enable the ADC peripheral clock. */
    RCC->APB2ENR |= (1U << 9U);
    RCC_EnableGPIO(GPIOA);

    /* GPIOA MODER/PUPDR: configure PA0 as an analog input. */
    GPIO_Init(GPIOA, &gpioConfig);

    /* ADC CFGR1 RES: select the configured ADC resolution. */
    ADCx->CFGR1 = (ADCx->CFGR1 & ~ADC_CFGR1_RES_MASK) |
                  (((uint32_t)config->Resolution << 3U) & ADC_CFGR1_RES_MASK);

    /* ADC CFGR1 ALIGN: select right or left data alignment. */
    if (config->DataAlignment == ADC_DATAALIGN_LEFT) {
        ADCx->CFGR1 |= ADC_CFGR1_ALIGN;
    } else {
        ADCx->CFGR1 &= ~ADC_CFGR1_ALIGN;
    }

    /* ADC CFGR1 CONT: select single or continuous conversion mode. */
    if (config->ContinuousMode == ADC_CONTINUOUS_ENABLE) {
        ADCx->CFGR1 |= ADC_CFGR1_CONT;
    } else {
        ADCx->CFGR1 &= ~ADC_CFGR1_CONT;
    }

    /* ADC CFGR1 EXTEN: select the configured external trigger edge. */
    ADCx->CFGR1 = (ADCx->CFGR1 & ~ADC_CFGR1_EXTEN_MASK) |
                  ((uint32_t)config->ExternalTrigger << 10U);

    /* ADC CFGR1 SCANDIR: scan channels in ascending channel order. */
    ADCx->CFGR1 &= ~ADC_CFGR1_SCANDIR_MASK;

    /* ADC CFGR1 DMAEN: enable DMA requests when a DMA handle is supplied. */
    if (config->DMARequest != 0) {
        ADCx->CFGR1 |= ADC_CFGR1_DMAEN;
    } else {
        ADCx->CFGR1 &= ~ADC_CFGR1_DMAEN;
    }

    /* ADC SMPR SMP: select the configured sampling time. */
    ADCx->SMPR = (ADCx->SMPR & ~ADC_SMPR_SMP_MASK) |
                 ((uint32_t)config->SamplingTime & ADC_SMPR_SMP_MASK);

    /* ADC CHSELR: select exactly one configured regular channel. */
    ADCx->CHSELR = (1U << (uint32_t)config->Selection);
}

void ADC_StartConversion(ADC_TypeDef *ADCx)
{
    /* ADC CR ADEN/ADSTART/ADSTP: start only when ADC is ready. */
    if ((ADCx->CR & ADC_CR_ADEN) &&
        !(ADCx->CR & (ADC_CR_ADSTART | ADC_CR_ADSTP))) {
        ADCx->CR |= ADC_CR_ADSTART;
    }
}

uint16_t ADC_ReadValue(ADC_TypeDef *ADCx)
{
    if (!(ADCx->CR & ADC_CR_ADEN)) {
        return 0U;
    }

    ADC_StartConversion(ADCx);

    /* ADC ISR EOC: wait for end of conversion before reading the result. */
    while (!(ADCx->ISR & ADC_ISR_EOC)) {
    }

    /* ADC DR: reading the conversion result clears EOC. */
    return (uint16_t)ADCx->DR;
}

void ADC_Enable(ADC_TypeDef *ADCx)
{
    /* ADC CR: do not enable while a control or conversion command is active. */
    if (ADCx->CR & (ADC_CR_ADSTART | ADC_CR_ADSTP | ADC_CR_ADDIS | ADC_CR_ADCAL)) {
        return;
    }

    /* ADC CR ADCAL: calibrate before enabling the ADC. */
    ADCx->CR |= ADC_CR_ADCAL;
    while (ADCx->CR & ADC_CR_ADCAL) {
    }

    /* ADC ISR ADRDY: clear the ready flag using its write-one-to-clear rule. */
    ADCx->ISR = ADC_ISR_ADRDY;

    /* ADC CR ADEN: enable the ADC and wait for the ready flag. */
    ADCx->CR |= ADC_CR_ADEN;
    while (!(ADCx->ISR & ADC_ISR_ADRDY)) {
    }
}

void ADC_Disable(ADC_TypeDef *ADCx)
{
    if (ADCx->CR & ADC_CR_ADSTART) {
        /* ADC CR ADSTP: stop an active conversion. */
        ADCx->CR |= ADC_CR_ADSTP;
        while (ADCx->CR & ADC_CR_ADSTP) {
        }
    }

    if (ADCx->CR & ADC_CR_ADEN) {
        /* ADC CR ADDIS: disable the ADC after conversion has stopped. */
        ADCx->CR |= ADC_CR_ADDIS;
        while (ADCx->CR & ADC_CR_ADDIS) {
        }
    }
}
