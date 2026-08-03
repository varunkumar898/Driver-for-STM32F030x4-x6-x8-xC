#include "SYSCONFIG_Driver.h"

void SYSCONFIG_SetEXTIConfig(uint8_t EXTI_Line, uint8_t Exti_lineval)
{
    uint8_t regint = EXTI_Line / 4U;
    uint8_t bitpost = (EXTI_Line % 4U) * 4U;

    SYSCFG->EXTICR[regint] &= ~(0x0FU << bitpost);
    SYSCFG->EXTICR[regint] |= (Exti_lineval & 0x0FU) << bitpost;
}
