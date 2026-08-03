/*
 * GPIO driver implementation.
 * These functions configure GPIO registers and control pin states.
 * They are used by the main program to set up and blink the LED.
 */
#include "GPIO_Driver.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *PinConfig)
{
    uint32_t pin = PinConfig->Pin;
    uint32_t position = pin * 2U;

    GPIOx->MODER &= ~(0x3U << position);
    GPIOx->MODER |= ((uint32_t)PinConfig->Mode & 0x3U) << position;

    GPIOx->OTYPER &= ~(1U << pin);
    GPIOx->OTYPER |= ((uint32_t)PinConfig->OType & 0x1U) << pin;

    GPIOx->OSPEEDR &= ~(0x3U << position);
    GPIOx->OSPEEDR |= ((uint32_t)PinConfig->Speed & 0x3U) << position;

    GPIOx->PUPDR &= ~(0x3U << position);
    GPIOx->PUPDR |= ((uint32_t)PinConfig->Pupdr & 0x3U) << position;
}

void GPIO_DeInit(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *PinConfig)
{
    uint32_t pin = PinConfig->Pin;
    uint32_t position = pin * 2U;

    GPIOx->MODER &= ~(0x3U << position);
    GPIOx->OTYPER &= ~(1U << pin);
    GPIOx->OSPEEDR &= ~(0x3U << position);
    GPIOx->PUPDR &= ~(0x3U << position);
}

void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    GPIOx->ODR |= (1U << Pin);
}

void GPIO_ResetPin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    GPIOx->ODR &= ~(1U << Pin);
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    GPIOx->ODR ^= (1U << Pin);
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    return (uint8_t)((GPIOx->IDR >> Pin) & 0x1U);
}

void GPIO_WritePort(GPIO_TypeDef *GPIOx, uint32_t PortValue)
{
    GPIOx->ODR = PortValue;
}

uint32_t GPIO_ReadPort(GPIO_TypeDef *GPIOx, uint32_t *PortValue)
{
    if (PortValue != 0U) {
        *PortValue = GPIOx->IDR;
    }
    return GPIOx->IDR;
}

void GPIO_Lock(GPIO_TypeDef *GPIOx, uint32_t Pin)
{
    (void)GPIOx;
    (void)Pin;
}

void GPIO_reset(GPIO_TypeDef *GPIOx)
{
    GPIOx->MODER = 0x00000000U;
    GPIOx->OTYPER = 0x00000000U;
    GPIOx->OSPEEDR = 0x00000000U;
    GPIOx->PUPDR = 0x00000000U;
    GPIOx->ODR = 0x00000000U;
    GPIOx->BSRR = 0x00000000U;
    GPIOx->LCKR = 0x00000000U;
    GPIOx->AFRH = 0x00000000U;
    GPIOx->AFRL = 0x00000000U;
}
