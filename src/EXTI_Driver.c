#include "EXTI_Driver.h"

/*Enable interrupt for the specific line and unmasking number and trigger type*/
void EXTI_EnableInterrupt(uint32_t EXTINumberline, EXTI_TriggerType TriggerType)
{
    EXTI->EXTI_IMR |= (1U << EXTINumberline);
    switch (TriggerType)
    {
    case TRIGGER_RISING_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_FALLING_EDGE:
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        EXTI->EXTI_RTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_BOTH_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        break;

    default:
        break;
    }
}

/*This function enable the unmasking for the specific line number */
void EXTI_EnableMask(uint32_t EXTINumberline, EXTI_TriggerType TriggerType)
{
    EXTI->EXTI_EMR |= (1U << EXTINumberline);
    switch (TriggerType)
    {
    case TRIGGER_RISING_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_FALLING_EDGE:
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        EXTI->EXTI_RTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_BOTH_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        break;

    default:
        break;
    }
}

/*This function enable the software interrupt for the specific line number */
void EXTI_EnableSWIER(uint32_t EXTINumberline, EXTI_TriggerType TriggerType)
{
    EXTI->EXTI_SWIER |= (1U << EXTINumberline);
    switch (TriggerType)
    {
    case TRIGGER_RISING_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_FALLING_EDGE:
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        EXTI->EXTI_RTSR &= ~(1U << EXTINumberline);
        break;

    case TRIGGER_BOTH_EDGE:
        EXTI->EXTI_RTSR |= (1U << EXTINumberline);
        EXTI->EXTI_FTSR |= (1U << EXTINumberline);
        break;

    default:
        break;
    }
}

/*This function clear the pending bit for the specific line number */
void EXTI_CLEAR_Pending(uint32_t EXTINumberline)
{
    EXTI->EXTI_PR |= (1U << EXTINumberline);
}

/*This function get the pending bit for the specific line number */
boolean EXTI_GetPending(uint32_t EXTINumberline)
{
    return (EXTI->EXTI_PR & (1U << EXTINumberline)) ? 1U : 0U;
}