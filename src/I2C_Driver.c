#include "I2C_Driver.h"
#include "RCC_Driver.h"

static int i2c_wait(I2C_TypeDef *i, uint32_t flag)
{
    uint32_t timeout = 1000000UL;
    while (!(i->ISR & flag)) {
        if (--timeout == 0) return -1;
        if (i->ISR & I2C_ISR_NACKF) {
            i->ICR = I2C_ICR_NACKCF;
            return -2;
        }
    }
    return 0;
}

void I2C_Init(const I2C_InitTypeDef *c)
{
    I2C_TypeDef *i = c->I2Cinstant;
    RCC_EnableI2C(i);
    i->CR1 &= ~I2C_CR1_PE;
    i->TIMINGR = c->Timing;
    i->CR1 |= I2C_CR1_PE;
}

int I2C_Write(I2C_TypeDef *i, uint8_t address7, const uint8_t *data, uint8_t length)
{
    if (length == 0 || length > 255) return -1;
    while (i->ISR & I2C_ISR_BUSY) {}

    i->CR2 = ((uint32_t)address7 << 1)
           | ((uint32_t)length << I2C_CR2_NBYTES_Pos)
           | I2C_CR2_AUTOEND | I2C_CR2_START;

    for (uint8_t n = 0; n < length; ++n) {
        if (i2c_wait(i, I2C_ISR_TXIS) != 0) return -2;
        i->TXDR = data[n];
    }

    if (i2c_wait(i, I2C_ISR_STOPF) != 0) return -3;
    i->ICR = I2C_ICR_STOPCF;
    return 0;
}

int I2C_Read(I2C_TypeDef *i, uint8_t address7, uint8_t *data, uint8_t length)
{
    if (length == 0 || length > 255) return -1;
    while (i->ISR & I2C_ISR_BUSY) {}

    i->CR2 = ((uint32_t)address7 << 1)
           | I2C_CR2_RD_WRN
           | ((uint32_t)length << I2C_CR2_NBYTES_Pos)
           | I2C_CR2_AUTOEND | I2C_CR2_START;

    for (uint8_t n = 0; n < length; ++n) {
        if (i2c_wait(i, I2C_ISR_RXNE) != 0) return -2;
        data[n] = (uint8_t)i->RXDR;
    }

    if (i2c_wait(i, I2C_ISR_STOPF) != 0) return -3;
    i->ICR = I2C_ICR_STOPCF;
    return 0;
}

int I2C_WriteRead(I2C_TypeDef *i, uint8_t address7,
                  const uint8_t *tx, uint8_t tx_len,
                  uint8_t *rx, uint8_t rx_len)
{
    if (tx_len == 0 || rx_len == 0) return -1;
    int r = I2C_Write(i, address7, tx, tx_len);
    if (r != 0) return r;
    return I2C_Read(i, address7, rx, rx_len);
}
