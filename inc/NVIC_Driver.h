#ifndef NVIC_DRIVER_H
#define NVIC_DRIVER_H
#include "STM32F030x8.h"

typedef enum {
    IRQ_EXTI4_15 = 7,
    IRQ_ADC1 = 12,
    IRQ_I2C1 = 23,
    IRQ_I2C2 = 24,
    IRQ_SPI1 = 25,
    IRQ_SPI2 = 26,
    IRQ_USART1 = 27,
    IRQ_USART2 = 28
} IRQn_t;

void NVIC_EnableIRQ(IRQn_t irqn);
void NVIC_DisableIRQ(IRQn_t irqn);
void NVIC_SetPriorityIRQ(IRQn_t irqn, uint8_t priority);
#endif
