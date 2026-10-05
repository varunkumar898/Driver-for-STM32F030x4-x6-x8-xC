#ifndef USART_DRIVER_H
#define USART_DRIVER_H
#include "STM32F030x8.h"

typedef enum { USART1_ID, USART2_ID } USART_ID_t;
typedef enum { USART_PARITY_NONE, USART_PARITY_EVEN, USART_PARITY_ODD } USART_Parity_t;
typedef enum { USART_WORD_LENGTH_8, USART_WORD_LENGTH_9 } USART_WordLength_t;
typedef enum { USART_STOPBIT_1 = 0, USART_STOPBIT_2 = 2 } USART_StopBits_t;

typedef struct {
    USART_ID_t USART_ID;
    USART_TypeDef *USARTinstant;
    uint32_t BaudRate;
    USART_Parity_t Parity;
    USART_WordLength_t WordLength;
    USART_StopBits_t StopBits;
    uint8_t OverSampling;
    uint8_t EnableTx;
    uint8_t EnableRx;
} USART_InitTypeDef;

void USART_Init(const USART_InitTypeDef *config);
void USART_SendByte(USART_TypeDef *USARTx, uint8_t data);
void USART_SendString(USART_TypeDef *USARTx, const char *s);
uint8_t USART_ReadByte(USART_TypeDef *USARTx);
uint8_t USART_DataAvailable(USART_TypeDef *USARTx);
#endif
