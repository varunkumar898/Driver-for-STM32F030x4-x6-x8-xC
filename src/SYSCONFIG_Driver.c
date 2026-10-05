#include "SYSCONFIG_Driver.h"

void SYSCFG_SetEXTIConfig(uint8_t line, uint8_t port_code)
{
    uint8_t index = line / 4U;
    uint8_t shift = (line % 4U) * 4U;
    SYSCFG->EXTICR[index] &= ~(0xFUL << shift);
    SYSCFG->EXTICR[index] |= ((uint32_t)port_code << shift);
}
