#include "SPI_Driver.h"
#include "RCC_Driver.h"

void SPI_Init(const SPI_InitTypeDef *c)
{
    SPI_TypeDef *s = c->SPIinstant;
    RCC_EnableSPI(s);
    s->CR1 = 0;
    s->CR2 = 0;

    if (c->Mode == SPI_MODE_MASTER) s->CR1 |= SPI_CR1_MSTR;
    if (c->CPOL == SPI_CPOL_HIGH) s->CR1 |= SPI_CR1_CPOL;
    if (c->CPHA == SPI_CPHA_2EDGE) s->CR1 |= SPI_CR1_CPHA;

    s->CR1 |= ((uint32_t)(c->BaudRatePrescaler & 7U) << SPI_CR1_BR_Pos);

    if (c->SoftwareNSS) {
        s->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;
    }

    s->CR2 |= ((uint32_t)c->DataSize << SPI_CR2_DS_Pos);
    s->CR2 |= SPI_CR2_FRXTH;
}

void SPI_Enable(SPI_TypeDef *s) { s->CR1 |= SPI_CR1_SPE; }
void SPI_Disable(SPI_TypeDef *s) { s->CR1 &= ~SPI_CR1_SPE; }

uint8_t SPI_Transfer8(SPI_TypeDef *s, uint8_t data)
{
    while (!(s->SR & SPI_SR_TXE)) {}
    *(__IO uint8_t *)&s->DR = data;
    while (!(s->SR & SPI_SR_RXNE)) {}
    return *(__IO uint8_t *)&s->DR;
}
