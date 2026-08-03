#include "RCC_Driver.h"


/*enable the clock for the specified GPIO port */

void RCC_EnableGPIO(GPIO_TypeDef *port)
{
    if (port == GPIOA)
    {
        RCC->AHBENR |= (1 << 17);
    }
    else if( port == GPIOB)
    {
        RCC->AHBENR |= (1 << 18);
    }
    else if (port == GPIOC)
    {
        RCC->AHBENR |= (1 << 19);
    }
    else if (port == GPIOD)
    {
        RCC->AHBENR |= (1 << 20);
    }
    else if (port == GPIOF)
    {
        RCC->AHBENR |= (1 << 22);
    }
}
//Disable the clock for the specified GPIO port */
void RCC_DisableGPIO(GPIO_TypeDef *port)

{
    if (port == GPIOA)
    {
        RCC->AHBENR &= ~(1 << 17);
    }
    else if( port == GPIOB)
    {
        RCC->AHBENR &= ~(1 << 18);
    }
    else if (port == GPIOC)
    {
        RCC->AHBENR &= ~(1 << 19);
    }
    else if (port == GPIOD)
    {
        RCC->AHBENR &= ~(1 << 20);
    }
    else if (port == GPIOF)
    {
        RCC->AHBENR &= ~(1 << 22);
    }
}
