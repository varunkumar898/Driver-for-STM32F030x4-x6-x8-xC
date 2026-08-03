#ifndef GPIO_Driver_h
#define GPIO_Driver_h
#include "STM32F030x4.h"

typedef enum
{
    GPIO_MODE_INPUT      = 0x00,
    GPIO_MODE_OUTPUT     = 0x01,
    GPIO_MODE_ALTERNATE  = 0x02,
    GPIO_MODE_ANALOG     = 0x03
} GPIO_Mode_t;
typedef enum
{
    GPIO_OUTPUT_TYPE_PUSH_PULL  = 0x00,
    GPIO_OUTPUT_TYPE_OPEN_DRAIN = 0x01
} GPIO_Output_Type_t;
typedef enum
{

    GPIO_SPEED_LOW      = 0x00,
    GPIO_SPEED_MEDIUM   = 0x01,
    GPIO_SPEED_HIGH     = 0x02,
} GPIO_Speed_t;
typedef enum
{
    GPIO_NO_PULL        = 0x00,
    GPIO_PULL_UP        = 0x01,
    GPIO_PULL_DOWN      = 0x02,
    GPIO_RESERVED       = 0x03
} GPIO_PUPD_t;

typedef struct
{
    GPIO_TypeDef *GPIOx;            /*!< GPIO port base address */
    uint32_t Pin;                   /*!< GPIO pin number */
    GPIO_Mode_t Mode;               /*!< GPIO mode */
    GPIO_Output_Type_t OType;       /*!< GPIO output type */
    GPIO_Speed_t Speed;             /*!< GPIO speed */
    GPIO_PUPD_t Pupdr;               /*!< GPIO pull-up/pull-down configuration */

} GPIO_InitTypeDef;

/*function declarations*/

/* GPIO initialization and functions */

void GPIO_Init(GPIO_TypeDef *Port ,GPIO_InitTypeDef *PinConfig);

/* GPIO  de-initialization and functions */

void GPIO_DeInit(GPIO_TypeDef *Port ,GPIO_InitTypeDef *PinConfig);

/* GPIO read and write functions */

/*This function sets the specified GPIO pin to a high level (logic 1) */
void GPIO_SetPin(GPIO_TypeDef *GPIOx, uint32_t Pin);

/*This function clears the specified GPIO pin to a low level (logic 0) */
void GPIO_ResetPin(GPIO_TypeDef *GPIOx, uint32_t Pin);

/*This fuction sets thye troggle the specified GPIO pin, changing its state from high to low or low to high */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t Pin);

/*This function sets the specified Readpin */
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t Pin);

/*This function writes a value to the specified write */
void GPIO_WritePort(GPIO_TypeDef *GPIOx, uint32_t PortValue);

/*This function reads the current value of the specified GPIO port */
uint32_t GPIO_ReadPort(GPIO_TypeDef *GPIOx, uint32_t *PortValue);

/*This function locks the specified GPIO pin */
void GPIO_Lock(GPIO_TypeDef *GPIOx, uint32_t Pin);

/*This function resets the specified GPIO port to its default state */
void GPIO_reset(GPIO_TypeDef *GPIOx );





#endif /* GPIO_Driver_h */
