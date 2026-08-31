#include "I2C_driver.h"
#include "GPIO_Driver.h"
#include "RCC_Driver.h"

/* This function initializes the I2C peripheral based on the passed configuration */
void I2C_Init(I2C_ConfigTypeDef *I2C_Config)
{
    I2C_TypeDef *pI2c = I2C_Config->I2Cinstant;

    /* Insert the GPIO configuration for the I2C ID */    
    I2C_GPIOConfig(I2C_Config->I2C_ID);

    /* Enable RCC clock for the corresponding I2C peripheral */
    switch(I2C_Config->I2C_ID)
    {
        case I2C1_ID:
            RCC->APB1ENR |= (1 << 21); /* Enable I2C1 clock (Bit 21 in APB1ENR) */
            break;
        case I2C2_ID:
            RCC->APB1ENR |= (1 << 22); /* Enable I2C2 clock (Bit 22 in APB1ENR) */
            break;
        default:
            // Handle invalid I2C ID
            break;
    }

    /* Disable peripheral before configuration (PE = 0) */
    pI2c->CR1 &= ~I2C_CR1_PE;

    /* Configure TIMINGR register (Clock speed timing for STM32F030) */
    pI2c->TIMINGR = I2C_Config->Timing;

    /* Configure Own Address 1 (OAR1) */
    pI2c->OAR1 &= ~I2C_OAR1_OA1EN; // Disable before editing
    if(I2C_Config->AddressingMode == I2C_ADDRMODE_7BIT)
    {
        pI2c->OAR1 &= ~(1 << 10); // 7-bit mode
        pI2c->OAR1 |= (I2C_Config->OwnAddress << 1); // Bits [7:1] contain 7-bit address
    }
    else
    {
        pI2c->OAR1 |= (1 << 10);  // 10-bit mode
        pI2c->OAR1 |= I2C_Config->OwnAddress;
    }
    pI2c->OAR1 |= I2C_OAR1_OA1EN; // Enable Own Address

    /* Enable I2C peripheral (PE = 1) */
    pI2c->CR1 |= I2C_CR1_PE;
}

/*-----------------------------------------------------------------------------------*/

/* This function transmits data as Master to a specific slave address */
void I2C_MasterTransmit(I2C_TypeDef *pI2c, uint8_t slaveAddr, const uint8_t *data, uint32_t length)
{
    // Clear CR2 register parameters
    pI2c->CR2 &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN);

    // Set Slave Address, byte length, AUTOEND bit (Generates STOP automatically), Write direction (RD_WRN = 0)
    pI2c->CR2 |= ((uint32_t)slaveAddr << 1);
    pI2c->CR2 |= ((uint32_t)length << 16);
    pI2c->CR2 |= I2C_CR2_AUTOEND;

    // Generate START condition
    pI2c->CR2 |= I2C_CR2_START;

    for(uint32_t i = 0; i < length; i++)
    {
        // Wait until TXIS (Transmit Interrupt Status / Buffer Empty) is set
        while (!(pI2c->ISR & I2C_ISR_TXIS));

        // Write data byte to Transmit Data Register
        pI2c->TXDR = data[i];
    }

    // Wait until STOP condition is detected (AUTOEND generates STOP)
    while (!(pI2c->ISR & I2C_ISR_STOPF));

    // Clear STOP flag in ICR register
    pI2c->ICR |= I2C_ICR_STOPCF;
}

/*-----------------------------------------------------------------------------------*/

/* This function receives data as Master from a specific slave address */
void I2C_MasterReceive(I2C_TypeDef *pI2c, uint8_t slaveAddr, uint8_t *data, uint32_t length)
{
    // Clear CR2 register parameters
    pI2c->CR2 &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN);

    // Set Slave Address, byte length, AUTOEND bit, Read direction (RD_WRN = 1)
    pI2c->CR2 |= ((uint32_t)slaveAddr << 1);
    pI2c->CR2 |= ((uint32_t)length << 16);
    pI2c->CR2 |= I2C_CR2_AUTOEND;
    pI2c->CR2 |= I2C_CR2_RD_WRN;

    // Generate START condition
    pI2c->CR2 |= I2C_CR2_START;

    for(uint32_t i = 0; i < length; i++)
    {
        // Wait until RXNE (Receive Buffer Not Empty) is set
        while (!(pI2c->ISR & I2C_ISR_RXNE));

        // Read data byte from Receive Data Register
        data[i] = pI2c->RXDR;
    }

    // Wait until STOP condition is detected
    while (!(pI2c->ISR & I2C_ISR_STOPF));

    // Clear STOP flag in ICR register
    pI2c->ICR |= I2C_ICR_STOPCF;
}

/*-----------------------------------------------------------------------------------*/

/* This function enables the I2C peripheral */
void I2C_enable(I2C_EN_ID I2C_ID)
{   
    I2C_TypeDef *I2Cx;

    if(I2C_ID == I2C1_ID)
    {
        I2Cx = I2C1;
    }
    else if(I2C_ID == I2C2_ID)
    {
        I2Cx = I2C2;
    }
    
    I2Cx->CR1 |= I2C_CR1_PE; /* Enable I2C peripheral */
}

/* This function disables the I2C peripheral */
void I2C_disable(I2C_EN_ID I2C_ID)   
{   
    I2C_TypeDef *I2Cx;

    if(I2C_ID == I2C1_ID)
    {
        I2Cx = I2C1;
    }
    else if(I2C_ID == I2C2_ID)
    {
        I2Cx = I2C2;
    }
    
    I2Cx->CR1 &= ~I2C_CR1_PE; /* Disable I2C peripheral */
}

/*-----------------------------------------------------------------------------------*/

/* This function configures GPIO Pins for the I2C peripheral */
void I2C_GPIOConfig(I2C_EN_ID I2C_ID)
{
    GPIO_InitTypeDef I2C_GPIOConfig = {
        .Pin = 0,
        .Mode = GPIO_MODE_AF,
        .OType = GPIO_OUTPUT_TYPE_OPEN_DRAIN, /* I2C requires Open-Drain output */
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_PULL_UP,                 /* Internal pull-ups enabled */
        .alternate = 1                        /* AF1 is standard for I2C on STM32F0 */
    };

    /* GPIO I2C1 pin configuration */
    if(I2C_ID == I2C1_ID)
    {
        /* PB6 (SCL) and PB7 (SDA) for I2C1 */
        RCC_EnableGPIO(GPIOB);

        I2C_GPIOConfig.alternate = 1;

        I2C_GPIOConfig.pin = 6; // SCL
        GPIO_Init(GPIOB, &I2C_GPIOConfig);

        I2C_GPIOConfig.pin = 7; // SDA
        GPIO_Init(GPIOB, &I2C_GPIOConfig);
    }
    /* GPIO I2C2 pin configuration */
    else if(I2C_ID == I2C2_ID)
    { 
        /* PB10 (SCL) and PB11 (SDA) for I2C2 */
        RCC_EnableGPIO(GPIOB);    

        I2C_GPIOConfig.alternate = 1;

        I2C_GPIOConfig.pin = 10; // SCL
        GPIO_Init(GPIOB, &I2C_GPIOConfig);

        I2C_GPIOConfig.pin = 11; // SDA
        GPIO_Init(GPIOB, &I2C_GPIOConfig);
    }
}