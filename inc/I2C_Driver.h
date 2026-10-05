#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H
#include "STM32F030x8.h"

typedef enum { I2C1_ID, I2C2_ID } I2C_ID_t;
typedef struct {
    I2C_ID_t I2C_ID;
    I2C_TypeDef *I2Cinstant;
    uint32_t Timing;
} I2C_InitTypeDef;

void I2C_Init(const I2C_InitTypeDef *config);
int I2C_Write(I2C_TypeDef *I2Cx, uint8_t address7, const uint8_t *data, uint8_t length);
int I2C_Read(I2C_TypeDef *I2Cx, uint8_t address7, uint8_t *data, uint8_t length);
int I2C_WriteRead(I2C_TypeDef *I2Cx, uint8_t address7,
                 const uint8_t *tx, uint8_t tx_len,
                 uint8_t *rx, uint8_t rx_len);
#endif
