#ifndef USART_DRIVER_H
#define USART_DRIVER_H

#include <stdint.h>
#include "STM32F030x4.h"

#define USART_PeripheralClockFreq 8000000UL

typedef enum
{
    USART1_ID = 1
    USART2_ID = 2,
    USART3_ID = 3,
    USART4_ID = 4,  
    USART5_ID = 5,
    USART6_ID = 6,
} USART_EN_ID;

typedef enum
{
    USART_EVEN_PARITY,
    USART_ODD_PARITY,
    USART_NO_PARITY
} USART_EN_PARITY;

typedef enum
{
    USART_WORLDLENGTH_8BIT,
    USART_WORLDLENGTH_9BIT
} USART_EN_WORDLENGTH;

typedef enum
{
    USART_STOPBIT_1,
    USART_STOPBIT_2
} USART_EN_STOPBITS;

typedef struct
{
    USART_EN_ID USART_ID;
    uint32_t BaudRate;
    USART_EN_PARITY Parity;
    USART_EN_WORDLENGTH WordLength;
    USART_EN_STOPBITS StopBits;
    uint8_t OverSample;
    USART_TypeDef * USARTinstant
} USART_ConfigTypeDef;


void USART_Init(USART_ConfigTypeDef *config);
void USART_DeInit(USART_EN_ID USART_ID);
void USART_Transmit(USART_TypeDef *usart, const uint8_t *data, uint32_t length);
void USART_Receive(USART_TypeDef *usart, uint8_t *data, uint32_t length);
void USART_enable(USART_EN_ID USART_ID);
void USART_disable(USART_EN_ID USART_ID);
void USART_GPIOConfig(USART_EN_ID USART_ID);

#endif