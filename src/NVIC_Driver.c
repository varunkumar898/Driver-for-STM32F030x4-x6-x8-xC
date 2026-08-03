#include "NVIC_Driver.h"

#define NVIC_ISER_BASE ((volatile uint32_t *)(NVIC_BASE_ADDR))
#define NVIC_ICER_BASE ((volatile uint32_t *)(NVIC_BASE_ADDR + 0x80U))
#define NVIC_ISPR_BASE ((volatile uint32_t *)(NVIC_BASE_ADDR + 0x100U))
#define NVIC_ICPR_BASE ((volatile uint32_t *)(NVIC_BASE_ADDR + 0x180U))
#define NVIC_IABR_BASE ((volatile uint32_t *)(NVIC_BASE_ADDR + 0x300U))

/*this function enable the specific interrupt number */
void NVIC_EnableIRQ(uint8_t IRQn)
{
    NVIC_ISER_BASE[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/*this function disable the specific interrupt number */
void NVIC_DisableIRQ(uint8_t IRQn)
{
    NVIC_ICER_BASE[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/*this function get the pending interrupt number */
uint32_t NVIC_GetPendingIRQ(uint8_t IRQn)
{
    return (NVIC_ISPR_BASE[IRQn / 32U] & (1U << (IRQn % 32U))) ? 1U : 0U;
}

/*this function set the pending interrupt number */
void NVIC_SetPendingIRQ(uint8_t IRQn)
{
    NVIC_ISPR_BASE[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/*this function clear the pending interrupt number */
void NVIC_ClearPendingIRQ(uint8_t IRQn)
{
    NVIC_ICPR_BASE[IRQn / 32U] |= (1U << (IRQn % 32U));
}

/*this function set the priority of the specific interrupt number */
void NVIC_SetPriorityIRQ(uint8_t IRQn, uint32_t priority)
{
    NVIC_IABR_BASE[IRQn / 32U] = (priority << (IRQn % 32U));
}

/*this function get the priority of the specific interrupt number */
uint32_t NVIC_GetPriorityIRQ(uint8_t IRQn, uint32_t priority)
{
    (void)priority;
    return (NVIC_IABR_BASE[IRQn / 32U] >> (IRQn % 32U)) & 0xFFU;
}
