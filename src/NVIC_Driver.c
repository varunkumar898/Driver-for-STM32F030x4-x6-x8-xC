#include "NVIC_Driver.h"

void NVIC_EnableIRQ(IRQn_t irqn)
{
    if ((uint32_t)irqn < 32U)
        NVIC->ISER[0] = (1UL << (uint32_t)irqn);
}

void NVIC_DisableIRQ(IRQn_t irqn)
{
    if ((uint32_t)irqn < 32U)
        NVIC->ICER[0] = (1UL << (uint32_t)irqn);
}

void NVIC_SetPriorityIRQ(IRQn_t irqn, uint8_t priority)
{
    if ((uint32_t)irqn < 32U)
        NVIC->IPR[(uint32_t)irqn] = (uint8_t)(priority << 6);
}
