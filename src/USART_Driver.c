#include "USART_Driver.h"
#include "RCC_Driver.h"

static uint32_t usart_brr(uint32_t pclk, uint32_t baud)
{
    return (pclk + (baud / 2U)) / baud;
}

void USART_Init(const USART_InitTypeDef *c)
{
    USART_TypeDef *u = c->USARTinstant;
    RCC_EnableUSART(u);

    u->CR1 = 0;
    u->CR2 = ((uint32_t)c->StopBits << USART_CR2_STOP_Pos);

    if (c->Parity != USART_PARITY_NONE) {
        u->CR1 |= USART_CR1_PCE;
        if (c->Parity == USART_PARITY_ODD)
            u->CR1 |= USART_CR1_PS;
    }

    if (c->WordLength == USART_WORD_LENGTH_9)
        u->CR1 |= USART_CR1_M0;

    u->BRR = usart_brr(RCC_GetSystemClockHz(), c->BaudRate);

    if (c->EnableTx) u->CR1 |= USART_CR1_TE;
    if (c->EnableRx) u->CR1 |= USART_CR1_RE;
    u->CR1 |= USART_CR1_UE;
}

void USART_SendByte(USART_TypeDef *u, uint8_t data)
{
    while (!(u->ISR & USART_ISR_TXE)) {}
    u->TDR = data;
    while (!(u->ISR & USART_ISR_TC)) {}
}

void USART_SendString(USART_TypeDef *u, const char *s)
{
    while (*s) USART_SendByte(u, (uint8_t)*s++);
}

uint8_t USART_DataAvailable(USART_TypeDef *u)
{
    return (u->ISR & USART_ISR_RXNE) ? 1U : 0U;
}

uint8_t USART_ReadByte(USART_TypeDef *u)
{
    while (!(u->ISR & USART_ISR_RXNE)) {}
    return (uint8_t)(u->RDR & 0xFFU);
}
