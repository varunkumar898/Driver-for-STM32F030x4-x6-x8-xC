#include "ADC_Driver.h"
#include "RCC_Driver.h"

void ADC_Init(ADC_TypeDef *a, const ADC_InitTypeDef *c)
{
    RCC_EnableADC();

    a->CR &= ~ADC_CR_ADEN;

    a->CFGR1 = ((uint32_t)c->Resolution << ADC_CFGR1_RES_Pos);
    if (c->Continuous) a->CFGR1 |= ADC_CFGR1_CONT;

    a->SMPR = ((uint32_t)c->SamplingTime << ADC_SMPR_SMP_Pos);
    a->CHSELR = (1UL << c->Channel);

    a->CR |= ADC_CR_ADCAL;
    while (a->CR & ADC_CR_ADCAL) {}

    a->CR |= ADC_CR_ADEN;
    while (!(a->ISR & ADC_ISR_ADRDY)) {}
}

int ADC_Read(ADC_TypeDef *a, uint8_t channel, uint16_t *value)
{
    if (channel > 18 || value == 0) return -1;
    a->CHSELR = (1UL << channel);
    a->CR |= ADC_CR_ADSTART;
    while (!(a->ISR & ADC_ISR_EOC)) {}
    *value = (uint16_t)a->DR;
    return 0;
}
