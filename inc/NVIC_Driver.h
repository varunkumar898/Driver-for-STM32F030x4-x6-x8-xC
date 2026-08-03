#ifndef NVIC_DRIVER_H
#define NVIC_DRIVER_H
#include "STM32F030x4.h"
#include "stdint.h"

void NVIC_EnableIRQ              (uint8_t IRQn);
void NVIC_DisableIRQ             (uint8_t IRQn);
uint32_t NVIC_GetPendingIRQ      (uint8_t IRQn);
void NVIC_SetPendingIRQ          (uint8_t IRQn);
void NVIC_ClearPendingIRQ        (uint8_t IRQn);
void NVIC_SetPriorityIRQ         (uint8_t IRQn, uint32_t priority);
uint32_t NVIC_GetPriorityIRQ     (uint8_t IRQn, uint32_t priority);



#endif // NVIC_DRIVER_H