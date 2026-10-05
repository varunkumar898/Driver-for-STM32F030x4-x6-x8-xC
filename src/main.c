#include "STM32F030x8.h"
#include "RCC_Driver.h"
#include "GPIO_Driver.h"
#include "NVIC_Driver.h"
#include "EXTI_Driver.h"
#include "SYSCONFIG_Driver.h"
#include "USART_Driver.h"
#include "SPI_Driver.h"
#include "I2C_Driver.h"
#include "ADC_Driver.h"
#include "CAN_Driver.h"

#define LED_PIN             5U
#define BUTTON_PIN          13U
#define ADC_TEST_CHANNEL    0U

static void delay(volatile uint32_t count)
{
    while (count--) {
        __asm volatile ("nop");
    }
}

/* PC13 -> EXTI13 -> Port C */
void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetPending(BUTTON_PIN)) {
        GPIO_TogglePin(GPIOA, LED_PIN);
        EXTI_ClearPending(BUTTON_PIN);
    }
}

int main(void)
{
    /* ================================================================
     * 1. CLOCK / GPIO
     * ================================================================ */
    RCC_EnableGPIO(GPIOA);
    RCC_EnableGPIO(GPIOB);
    RCC_EnableGPIO(GPIOC);
    RCC_EnableSYSCFG();

    GPIO_InitTypeDef ledConfig = {
        .GPIOx = GPIOA,
        .Pin = LED_PIN,
        .Mode = GPIO_MODE_OUTPUT,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 0
    };

    GPIO_InitTypeDef buttonConfig = {
        .GPIOx = GPIOC,
        .Pin = BUTTON_PIN,
        .Mode = GPIO_MODE_INPUT,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_PULL_UP,
        .Alternate = 0
    };

    GPIO_Init(GPIOA, &ledConfig);
    GPIO_Init(GPIOC, &buttonConfig);

    /* PC13 -> EXTI13 */
    SYSCFG_SetEXTIConfig(BUTTON_PIN, 0x02U); /* Port C */
    EXTI_EnableInterrupt(BUTTON_PIN, EXTI_TRIGGER_FALLING);
    NVIC_SetPriorityIRQ(IRQ_EXTI4_15, 2);
    NVIC_EnableIRQ(IRQ_EXTI4_15);

    /* ================================================================
     * 2. USART2
     * PA2 = USART2_TX, PA3 = USART2_RX, AF1
     * ================================================================ */
    GPIO_InitTypeDef uartTx = {
        .GPIOx = GPIOA, .Pin = 2,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 1
    };
    GPIO_InitTypeDef uartRx = {
        .GPIOx = GPIOA, .Pin = 3,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_PULL_UP,
        .Alternate = 1
    };
    GPIO_Init(GPIOA, &uartTx);
    GPIO_Init(GPIOA, &uartRx);

    USART_InitTypeDef usart2Config = {
        .USART_ID = USART2_ID,
        .USARTinstant = USART2,
        .BaudRate = 9600,
        .Parity = USART_PARITY_NONE,
        .WordLength = USART_WORD_LENGTH_8,
        .StopBits = USART_STOPBIT_1,
        .OverSampling = 16,
        .EnableTx = 1,
        .EnableRx = 1
    };
    USART_Init(&usart2Config);
    USART_SendString(USART2, "\r\nSTM32F030R8 driver example\r\n");

    /* ================================================================
     * 3. SPI2
     * PB13 = SCK, PB14 = MISO, PB15 = MOSI, AF0
     * Keep SPI2 so PA5 remains the Nucleo LED.
     * ================================================================ */
    GPIO_InitTypeDef spiSck = {
        .GPIOx = GPIOB, .Pin = 13,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 0
    };
    GPIO_InitTypeDef spiMiso = {
        .GPIOx = GPIOB, .Pin = 14,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 0
    };
    GPIO_InitTypeDef spiMosi = {
        .GPIOx = GPIOB, .Pin = 15,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 0
    };
    GPIO_Init(GPIOB, &spiSck);
    GPIO_Init(GPIOB, &spiMiso);
    GPIO_Init(GPIOB, &spiMosi);

    SPI_InitTypeDef spi2Config = {
        .SPI_ID = SPI2_ID,
        .SPIinstant = SPI2,
        .Mode = SPI_MODE_MASTER,
        .CPOL = SPI_CPOL_LOW,
        .CPHA = SPI_CPHA_1EDGE,
        .DataSize = SPI_DATASIZE_8BIT,
        .BaudRatePrescaler = 2, /* BR=010 -> fPCLK/8 */
        .SoftwareNSS = 1
    };
    SPI_Init(&spi2Config);
    SPI_Enable(SPI2);

    /* ================================================================
     * 4. I2C1
     * PB6 = SCL, PB7 = SDA, AF1
     *
     * TIMINGR below is an example for the reset 8 MHz clock. Validate
     * timing against the required bus speed and board rise time before
     * production use.
     * ================================================================ */
    GPIO_InitTypeDef i2cScl = {
        .GPIOx = GPIOB, .Pin = 6,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_OPEN_DRAIN,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_PULL_UP,
        .Alternate = 1
    };
    GPIO_InitTypeDef i2cSda = {
        .GPIOx = GPIOB, .Pin = 7,
        .Mode = GPIO_MODE_ALTERNATE,
        .OType = GPIO_OUTPUT_TYPE_OPEN_DRAIN,
        .Speed = GPIO_SPEED_HIGH,
        .Pupdr = GPIO_PULL_UP,
        .Alternate = 1
    };
    GPIO_Init(GPIOB, &i2cScl);
    GPIO_Init(GPIOB, &i2cSda);

    I2C_InitTypeDef i2c1Config = {
        .I2C_ID = I2C1_ID,
        .I2Cinstant = I2C1,
        .Timing = 0x00303D5BUL
    };
    I2C_Init(&i2c1Config);

    /* ================================================================
     * 5. ADC1
     * PA0 = ADC_IN0
     * ================================================================ */
    GPIO_InitTypeDef adcPin = {
        .GPIOx = GPIOA, .Pin = ADC_TEST_CHANNEL,
        .Mode = GPIO_MODE_ANALOG,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_NO_PULL,
        .Alternate = 0
    };
    GPIO_Init(GPIOA, &adcPin);

    ADC_InitTypeDef adcConfig = {
        .Resolution = ADC_RESOLUTION_12BIT,
        .SamplingTime = ADC_SAMPLE_55_5,
        .Channel = ADC_TEST_CHANNEL,
        .Continuous = 0
    };
    ADC_Init(ADC1, &adcConfig);

    /* ================================================================
     * 6. CAN
     * ================================================================
     * CAN_Init() intentionally returns CAN_STATUS_UNSUPPORTED because
     * STM32F030R8 has no CAN controller.
     */
    CAN_InitTypeDef canConfig = {
        .bitrate = 500000,
        .mode = 0
    };
    CAN_Status_t canStatus = CAN_Init(&canConfig);
    (void)canStatus;

    /* ================================================================
     * Main demonstration loop
     * ================================================================ */
    while (1)
    {
        uint16_t adcValue = 0;

        /* ADC example */
        if (ADC_Read(ADC1, ADC_TEST_CHANNEL, &adcValue) == 0) {
            (void)adcValue;
        }

        /* SPI example: transmit one byte and read returned byte */
        {
            uint8_t spiRx = SPI_Transfer8(SPI2, 0x55);
            (void)spiRx;
        }

        /* UART example */
        USART_SendString(USART2, "UART/SPI/ADC example\r\n");

        /* I2C example:
         * To use this with a real device, replace 0x50 and the buffer
         * with the target device's 7-bit address/register protocol.
         *
         * Example:
         * uint8_t reg = 0x00;
         * uint8_t value;
         * I2C_WriteRead(I2C1, 0x50, &reg, 1, &value, 1);
         */

        delay(100000);
    }
}
