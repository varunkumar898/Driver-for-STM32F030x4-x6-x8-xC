#ifndef RCC_DRIVER_H
#define RCC_DRIVER_H
#include "STM32F030x8.h"

void RCC_EnableGPIO(GPIO_TypeDef *GPIOx);
void RCC_EnableUSART(USART_TypeDef *USARTx);
void RCC_EnableSPI(SPI_TypeDef *SPIx);
void RCC_EnableI2C(I2C_TypeDef *I2Cx);
void RCC_EnableADC(void);
void RCC_EnableSYSCFG(void);
void RCC_ResetPeripheral(uint32_t *reg, uint32_t mask);
uint32_t RCC_GetSystemClockHz(void);
#endif
