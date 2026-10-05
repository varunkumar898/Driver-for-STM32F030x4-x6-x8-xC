#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H
#include "STM32F030x8.h"
#ifndef __IO
#define __IO volatile
#endif

typedef enum { SPI1_ID, SPI2_ID } SPI_ID_t;
typedef enum { SPI_MODE_SLAVE, SPI_MODE_MASTER } SPI_Mode_t;
typedef enum { SPI_CPOL_LOW, SPI_CPOL_HIGH } SPI_CPOL_t;
typedef enum { SPI_CPHA_1EDGE, SPI_CPHA_2EDGE } SPI_CPHA_t;
typedef enum { SPI_DATASIZE_8BIT = 7, SPI_DATASIZE_16BIT = 15 } SPI_DataSize_t;

typedef struct {
    SPI_ID_t SPI_ID;
    SPI_TypeDef *SPIinstant;
    SPI_Mode_t Mode;
    SPI_CPOL_t CPOL;
    SPI_CPHA_t CPHA;
    SPI_DataSize_t DataSize;
    uint8_t BaudRatePrescaler;
    uint8_t SoftwareNSS;
} SPI_InitTypeDef;

void SPI_Init(const SPI_InitTypeDef *config);
uint8_t SPI_Transfer8(SPI_TypeDef *SPIx, uint8_t data);
void SPI_Enable(SPI_TypeDef *SPIx);
void SPI_Disable(SPI_TypeDef *SPIx);
#endif
