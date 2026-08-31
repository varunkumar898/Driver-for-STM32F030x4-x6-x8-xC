/*
 * Main application for blinking an LED on PA5.
 * Flow:
 * 1. Configure PA5 as a push-pull output.
 * 2. Enable the GPIOA clock.
 * 3. Toggle the LED forever with a short delay.
 */
#include <GPIO_Driver.h>
#include <RCC_Driver.h>
#include <EXTI_Driver.h>
#include <SYSCONFIG_Driver.h>
#include <NVIC_Driver.h>

void SystemInit(void)
{
}

void __libc_init_array(void)
{
}

static void delay(volatile uint32_t count)
{
    while (count--) {
    }
}

int main(void)
{
    GPIO_InitTypeDef ledConfig = {
        .Pin = 5,
        .Mode = GPIO_MODE_OUTPUT,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_NO_PULL
    };
    USART_InitTypeDef pushButtonConfig = {
        .BaudRate = 9600,
        .Parity = USART_PARITY_NONE,
        .WordLength = USART_WORD_LENGTH_8,
        .StopBits = USART_STOPBIT_1,
        .OverSampling = USART_OVERSAMPLING_16
        .USARTinstant = USART1
    };
    /* Enable GPIOA and GPIOC clocks */
    RCC_EnableGPIO(GPIOA);
    RCC_EnableGPIO(GPIOC);
   
    /*INSERT LED PIN*/
    GPIO_Init(GPIOA, &ledConfig);
    /*INSERT PUSH BUTTON PIN*/
    GPIO_Init(GPIOC, &pushButtonConfig);

    /* Configure EXTI for PC13 button */
    SYSCONFIG_SetEXTIConfig(13, 0x02);
    EXTI_EnableInterrupt(13, TRIGGER_FALLING_EDGE);
    NVIC_EnableIRQ(EXTI4_15IRQn);

    