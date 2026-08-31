#ifndef SPI_Driver.h
#define SPI_Driver.h

#include <stdint.h>
#include "STM32F030x4.h"

// Define available SPI peripherals for the F030 line
typedef enum
{
    SPI1_ID = 1,
    SPI2_ID = 2
} SPI_EN_ID;

// Master or Slave mode
typedef enum
{
    SPI_MODE_SLAVE = 0,
    SPI_MODE_MASTER = 1
} SPI_EN_MODE;

// Clock Polarity (CPOL)
typedef enum
{
    SPI_CPOL_LOW = 0,
    SPI_CPOL_HIGH = 1
} SPI_EN_CPOL;

// Clock Phase (CPHA)
typedef enum
{
    SPI_CPHA_1EDGE = 0,
    SPI_CPHA_2EDGE = 1
} SPI_EN_CPHA;

// Data Size (maps to DS[3:0] in CR2)
typedef enum
{
    SPI_DATASIZE_8BIT = 0x07,  // 0111 in binary
    SPI_DATASIZE_16BIT = 0x0F  // 1111 in binary
} SPI_EN_DATASIZE;

// Baud Rate Prescaler (maps to BR[2:0] in CR1)
typedef enum
{
    SPI_BAUDRATE_DIV2 = 0,
    SPI_BAUDRATE_DIV4 = 1,
    SPI_BAUDRATE_DIV8 = 2,
    SPI_BAUDRATE_DIV16 = 3,
    SPI_BAUDRATE_DIV32 = 4,
    SPI_BAUDRATE_DIV64 = 5,
    SPI_BAUDRATE_DIV128 = 6,
    SPI_BAUDRATE_DIV256 = 7
} SPI_EN_BAUDRATE_PRESCALER;

// Software Slave Management (SSM)
typedef enum
{
    SPI_SSM_DISABLE = 0, // Hardware handles CS
    SPI_SSM_ENABLE = 1   // Software handles CS
} SPI_EN_SSM;

// Configuration Struct
typedef struct
{
    SPI_EN_ID SPI_ID;
    SPI_EN_MODE Mode;
    SPI_EN_CPOL CPOL;
    SPI_EN_CPHA CPHA;
    SPI_EN_DATASIZE DataSize;
    SPI_EN_BAUDRATE_PRESCALER BaudRatePrescaler;
    SPI_EN_SSM SSM;
    SPI_TypeDef * SPIinstant; // CMSIS peripheral pointer (e.g., SPI1)
} SPI_ConfigTypeDef;


// Function Prototypes
void SPI_Init(SPI_ConfigTypeDef *config);
void SPI_DeInit(SPI_EN_ID SPI_ID);
void SPI_Transmit(SPI_TypeDef *spi, const uint8_t *data, uint32_t length);
void SPI_Receive(SPI_TypeDef *spi, uint8_t *data, uint32_t length);
void SPI_enable(SPI_EN_ID SPI_ID);
void SPI_disable(SPI_EN_ID SPI_ID);
void SPI_GPIOConfig(SPI_EN_ID SPI_ID);

#endif /* SPI_DRIVER_H */