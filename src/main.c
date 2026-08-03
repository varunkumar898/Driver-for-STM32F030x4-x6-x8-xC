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
    GPIO_InitTypeDef pushButtonConfig = {
        .Pin = 13,
        .Mode = GPIO_MODE_INPUT,
        .OType = GPIO_OUTPUT_TYPE_PUSH_PULL,
        .Speed = GPIO_SPEED_LOW,
        .Pupdr = GPIO_PULL_UP
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

    uint8_t ledOn = 0;

    while (1) {
        if (GPIO_ReadPin(GPIOC, 13) == 0U) {
            delay(100000);
            if (GPIO_ReadPin(GPIOC, 13) == 0U) {
                ledOn = !ledOn;
                if (ledOn) {
                    GPIO_SetPin(GPIOA, ledConfig.Pin);
                } else {
                    GPIO_ResetPin(GPIOA, ledConfig.Pin);
                }
            }
        }
    }
}
