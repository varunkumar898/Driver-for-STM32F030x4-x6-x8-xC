#include "EXTI_Driver.h"

void EXTI_EnableInterrupt(uint8_t line, EXTI_Trigger_t trigger)
{
    uint32_t bit = 1UL << line;
    EXTI->IMR |= bit;
    if (trigger == EXTI_TRIGGER_RISING || trigger == EXTI_TRIGGER_BOTH)
        EXTI->RTSR |= bit;
    else
        EXTI->RTSR &= ~bit;
    if (trigger == EXTI_TRIGGER_FALLING || trigger == EXTI_TRIGGER_BOTH)
        EXTI->FTSR |= bit;
    else
        EXTI->FTSR &= ~bit;
}

uint8_t EXTI_GetPending(uint8_t line)
{
    return (uint8_t)((EXTI->PR >> line) & 1U);
}

void EXTI_ClearPending(uint8_t line)
{
    EXTI->PR = (1UL << line);
}
