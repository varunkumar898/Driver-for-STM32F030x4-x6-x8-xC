#include "RCC_Driver.h"

void RCC_EnableGPIO(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if (GPIOx == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if (GPIOx == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if (GPIOx == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
}

void RCC_EnableUSART(USART_TypeDef *USARTx)
{
    if (USARTx == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    else if (USARTx == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
}

void RCC_EnableSPI(SPI_TypeDef *SPIx)
{
    if (SPIx == SPI1) RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    else if (SPIx == SPI2) RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
}

void RCC_EnableI2C(I2C_TypeDef *I2Cx)
{
    if (I2Cx == I2C1) RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    else if (I2Cx == I2C2) RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
}

void RCC_EnableADC(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
}

void RCC_EnableSYSCFG(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
}

void RCC_ResetPeripheral(uint32_t *reg, uint32_t mask)
{
    *reg |= mask;
    *reg &= ~mask;
}

uint32_t RCC_GetSystemClockHz(void)
{
    /* This project intentionally starts from HSI48/HSI8 reset configuration.
       The example does not change SYSCLK, so reset SYSCLK is 8 MHz HSI. */
    return 8000000UL;
}
