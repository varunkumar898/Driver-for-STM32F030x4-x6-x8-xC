#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H
#include "STM32F030x4.h"
#include <stdint.h>

typedef uint8_t boolean;

typedef enum
{
    TRIGGER_RISING_EDGE = 0,
    TRIGGER_FALLING_EDGE,
    TRIGGER_BOTH_EDGE
} EXTI_TriggerType;

void EXTI_EnableInterrupt(uint32_t EXTINumberline, EXTI_TriggerType TriggerType);
void EXTI_EnableMask(uint32_t EXTINumberline, EXTI_TriggerType TriggerType);
void EXTI_EnableSWIER(uint32_t EXTINumberline, EXTI_TriggerType TriggerType);
void EXTI_CLEAR_Pending(uint32_t EXTINumberline);
boolean EXTI_GetPending(uint32_t EXTINumberline);

#endif // EXTI_DRIVER_H