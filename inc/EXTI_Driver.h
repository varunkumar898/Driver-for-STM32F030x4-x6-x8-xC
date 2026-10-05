#ifndef EXTI_DRIVER_H
#define EXTI_DRIVER_H
#include "STM32F030x8.h"

typedef enum {
    EXTI_TRIGGER_RISING,
    EXTI_TRIGGER_FALLING,
    EXTI_TRIGGER_BOTH
} EXTI_Trigger_t;

void EXTI_EnableInterrupt(uint8_t line, EXTI_Trigger_t trigger);
uint8_t EXTI_GetPending(uint8_t line);
void EXTI_ClearPending(uint8_t line);
#endif
