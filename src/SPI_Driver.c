#include "SPI_Driver.h"
#include "RCC_Driver.h"
#include "GPIO_Driver.h"


/* This function initializes the SPI peripheral based on the passed configuration */
void SPI_Init(SPI_ConfigTypeDef *SPI_Config)
{
    SPI_TypeDef *pSpi = SPI_Config->SPIinstant;

    /* Insert the GPIO configuration for the SPI ID */    
    SPI_GPIOConfig(SPI_Config->SPI_ID);

    /* SPI Enable RCC Clock */
    switch(SPI_Config->SPI_ID)
    {
        case SPI1_ID:
            RCC->APB2ENR |= (1 << 12); /* Enable SPI1 clock (Bit 12 in APB2ENR) */
            break;
        case SPI2_ID:
            RCC->APB1ENR |= (1 << 14); /* Enable SPI2 clock (Bit 14 in APB1ENR) */
            break;
        default:
            // Handle invalid SPI ID
            break;
    }

    /* Ensure SPI is disabled before configuration */
    pSpi->CR1 &= ~(SPI_CR1_SPE);

    /* SPI Set Clock Polarity (CPOL) */
    if(SPI_Config->CPOL == SPI_CPOL_LOW)
    {
        pSpi->CR1 &= ~(SPI_CR1_CPOL);
    }
    else
    {
        pSpi->CR1 |= (SPI_CR1_CPOL);
    }

    /* SPI Set Clock Phase (CPHA) */
    if(SPI_Config->CPHA == SPI_CPHA_1EDGE)
    {
        pSpi->CR1 &= ~(SPI_CR1_CPHA);
    }
    else
    {
        pSpi->CR1 |= (SPI_CR1_CPHA);
    }

    /* SPI Set Master/Slave Mode */
    if(SPI_Config->Mode == SPI_MODE_SLAVE)
    {
        pSpi->CR1 &= ~(SPI_CR1_MSTR);
    }
    else
    {
        pSpi->CR1 |= (SPI_CR1_MSTR);
    }

    /* SPI Set BaudRate Prescaler (BR[2:0]) */
    pSpi->CR1 &= ~(SPI_CR1_BR); // Clear existing baud rate
    pSpi->CR1 |= (SPI_Config->BaudRatePrescaler << SPI_CR1_BR_Pos);

    /* SPI Set Software Slave Management (SSM & SSI) */
    if(SPI_Config->SSM == SPI_SSM_DISABLE)
    {
        pSpi->CR1 &= ~(SPI_CR1_SSM);
    }
    else
    {
        pSpi->CR1 |= (SPI_CR1_SSM);
        /* If Master mode and SSM enabled, force SSI high to prevent mode fault */
        if(SPI_Config->Mode == SPI_MODE_MASTER)
        {
            pSpi->CR1 |= (SPI_CR1_SSI);
        }
    }

    /* SPI Set Data Size (DS[3:0] in CR2 for STM32F030) */
    pSpi->CR2 &= ~(SPI_CR2_DS); // Clear existing data size
    pSpi->CR2 |= (SPI_Config->DataSize << SPI_CR2_DS_Pos);

    /* Set FIFO Reception Threshold (FRXTH) for 8-bit mode */
    if(SPI_Config->DataSize == SPI_DATASIZE_8BIT)
    {
        pSpi->CR2 |= (SPI_CR2_FRXTH); /* Trigger RXNE on 8 bits */
    }
    else
    {
        pSpi->CR2 &= ~(SPI_CR2_FRXTH); /* Trigger RXNE on 16 bits */
    }
}

/*-----------------------------------------------------------------------------------*/

/* This function transmits data to the SPI peripheral */
void SPI_Transmit(SPI_TypeDef *pSpi, const uint8_t *data, uint32_t length)
{ 
    for(uint32_t i = 0; i < length; i++)
    {
        /* Wait until TXE (Transmit buffer empty) is set */
        while (!(pSpi->SR & SPI_SR_TXE)); 

        /* Transmit data */
        /* Note: Casting to uint8_t pointer forces 8-bit access on STM32F0 hardware */
        *(volatile uint8_t *)&pSpi->DR = data[i];
    }

    /* Wait until TXE is set (last byte moved to shift register) */
    while (!(pSpi->SR & SPI_SR_TXE));
    
    /* Wait until BSY (Busy) flag is cleared before assuming transmission is done */
    while (pSpi->SR & SPI_SR_BSY);
}

/*-----------------------------------------------------------------------------------*/

/* This function receives data from the SPI peripheral */
void SPI_Receive(SPI_TypeDef *pSpi, uint8_t *data, uint32_t length)
{  
    for(uint32_t i = 0; i < length; i++)
    {
        /* In SPI Master mode, you MUST transmit dummy data to generate the clock */
        while (!(pSpi->SR & SPI_SR_TXE)); 
        *(volatile uint8_t *)&pSpi->DR = 0xFF; // Send dummy byte
        
        /* Wait until RXNE (Receive buffer not empty) is set */
        while (!(pSpi->SR & SPI_SR_RXNE));      
        
        /* Read the data from the DR register */
        data[i] = *(volatile uint8_t *)&pSpi->DR;   
    }
    
    /* Wait until BSY flag is cleared */
    while (pSpi->SR & SPI_SR_BSY);
}

/*-----------------------------------------------------------------------------------*/

/* This function enables the SPI peripheral */
void SPI_enable(SPI_EN_ID SPI_ID)
{   
    SPI_TypeDef *SPIx;

    if(SPI_ID == SPI1_ID)
    {
        SPIx = SPI1;
    }
    else if(SPI_ID == SPI2_ID)
    {
        SPIx = SPI2;
    }
    
    SPIx->CR1 |= SPI_CR1_SPE; /* Enable SPI peripheral */
}

/* This function disables the SPI peripheral */
void SPI_disable(SPI_EN_ID SPI_ID)   
{   
    SPI_TypeDef *SPIx;

    if(SPI_ID == SPI1_ID)
    {
        SPIx = SPI1;
    }
    else if(SPI_ID == SPI2_ID)
    {
        SPIx = SPI2;
    }
    
    SPIx->CR1 &= ~SPI_CR1_SPE; /* Disable SPI peripheral */
}

/*-----------------------------------------------------------------------------------*/

/* This function configures GPIO Pins for the SPI peripheral */
void SPI_GPIOConfig(SPI_EN_ID SPI_ID)
{
    /* Using your hypothetical GPIO Init struct format */
    GPIO_InitTypeDef SPI_GPIOConfig = {
        .Pin = 0,
        .Mode = GPIO_MODE_AF,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH, /* High speed is recommended for SPI SCK */
        .Pupdr = GPIO_NO_PULL,
        .alternate = 0
    };

    /* GPIO SPI1 pin configuration */
    if(SPI_ID == SPI1_ID)
    {
        /* PA5 (SCK), PA6 (MISO), PA7 (MOSI) for SPI1 on AF0 */
        RCC_EnableGPIO(GPIOA);

        SPI_GPIOConfig.alternate = 0; // AF0 for SPI1 on STM32F030

        SPI_GPIOConfig.pin = 5; // SCK
        GPIO_Init(GPIOA, &SPI_GPIOConfig);

        SPI_GPIOConfig.pin = 6; // MISO
        GPIO_Init(GPIOA, &SPI_GPIOConfig);

        SPI_GPIOConfig.pin = 7; // MOSI
        GPIO_Init(GPIOA, &SPI_GPIOConfig);
    }
    /* GPIO SPI2 pin configuration */
    else if(SPI_ID == SPI2_ID)
    { 
        /* PB13 (SCK), PB14 (MISO), PB15 (MOSI) for SPI2 on AF0 */
        RCC_EnableGPIO(GPIOB);    

        SPI_GPIOConfig.alternate = 0; // AF0 for SPI2 on STM32F030

        SPI_GPIOConfig.pin = 13; // SCK
        GPIO_Init(GPIOB, &SPI_GPIOConfig);

        SPI_GPIOConfig.pin = 14; // MISO
        GPIO_Init(GPIOB, &SPI_GPIOConfig);

        SPI_GPIOConfig.pin = 15; // MOSI
        GPIO_Init(GPIOB, &SPI_GPIOConfig);
    }
}