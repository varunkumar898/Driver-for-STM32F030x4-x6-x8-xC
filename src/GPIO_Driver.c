#include "GPIO_Driver.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, const GPIO_InitTypeDef *c)
{
    uint32_t shift = c->Pin * 2U;
    GPIOx->MODER &= ~(3UL << shift);
    GPIOx->MODER |= ((uint32_t)c->Mode << shift);

    GPIOx->OTYPER &= ~(1UL << c->Pin);
    GPIOx->OTYPER |= ((uint32_t)c->OType << c->Pin);

    GPIOx->OSPEEDR &= ~(3UL << shift);
    GPIOx->OSPEEDR |= ((uint32_t)c->Speed << shift);

    GPIOx->PUPDR &= ~(3UL << shift);
    GPIOx->PUPDR |= ((uint32_t)c->Pupdr << shift);

    if (c->Mode == GPIO_MODE_ALTERNATE) {
        volatile uint32_t *afr = (c->Pin < 8U) ? &GPIOx->AFRL : &GPIOx->AFRH;
        uint32_t af_shift = (c->Pin & 7U) * 4U;
        *afr &= ~(0xFUL << af_shift);
        *afr |= ((uint32_t)c->Alternate << af_shift);
    }
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t pin, uint8_t state)
{
    GPIOx->BSRR = state ? (1UL << pin) : (1UL << (pin + 16U));
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
    return (uint8_t)((GPIOx->IDR >> pin) & 1U);
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pin)
{
    GPIOx->ODR ^= (1UL << pin);
}
