#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>
#include "STM32F030x4.h"

// Available I2C peripherals
typedef enum
{
    I2C1_ID = 1,
    I2C2_ID = 2
} I2C_EN_ID;

// Addressing Mode
typedef enum
{
    I2C_ADDRMODE_7BIT = 0,
    I2C_ADDRMODE_10BIT = 1
} I2C_EN_ADDRMODE;

// Acknowledge Enable
typedef enum
{
    I2C_ACK_DISABLE = 0,
    I2C_ACK_ENABLE = 1
} I2C_EN_ACK;

// Standard I2C Speed Modes
typedef enum
{
    I2C_SPEED_STANDARD = 0x00201D2B, // 100kHz @ 8MHz HSI (TIMINGR value)
    I2C_SPEED_FAST     = 0x0010020A  // 400kHz @ 8MHz HSI (TIMINGR value)
} I2C_EN_TIMING;

// Configuration Struct
typedef struct
{
    I2C_EN_ID I2C_ID;
    uint8_t OwnAddress;
    I2C_EN_ACK AckEnable;
    I2C_EN_ADDRMODE AddressingMode;
    I2C_EN_TIMING Timing;       // Pre-calculated TIMINGR value for STM32F0
    I2C_TypeDef * I2Cinstant;   // Peripheral pointer (e.g., I2C1)
} I2C_ConfigTypeDef;


// Function Prototypes
void I2C_Init(I2C_ConfigTypeDef *config);
void I2C_DeInit(I2C_EN_ID I2C_ID);
void I2C_MasterTransmit(I2C_TypeDef *i2c, uint8_t slaveAddr, const uint8_t *data, uint32_t length);
void I2C_MasterReceive(I2C_TypeDef *i2c, uint8_t slaveAddr, uint8_t *data, uint32_t length);
void I2C_enable(I2C_EN_ID I2C_ID);
void I2C_disable(I2C_EN_ID I2C_ID);
void I2C_GPIOConfig(I2C_EN_ID I2C_ID);

#endif /* I2C_DRIVER_H */
