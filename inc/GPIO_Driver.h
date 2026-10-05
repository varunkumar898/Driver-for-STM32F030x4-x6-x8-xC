#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H
#include "STM32F030x8.h"

typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT = 1,
    GPIO_MODE_ALTERNATE = 2,
    GPIO_MODE_ANALOG = 3
} GPIO_Mode_t;

typedef enum {
    GPIO_OUTPUT_TYPE_PUSH_PULL = 0,
    GPIO_OUTPUT_TYPE_OPEN_DRAIN = 1
} GPIO_Output_Type_t;

typedef enum {
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_HIGH = 3
} GPIO_Speed_t;

typedef enum {
    GPIO_NO_PULL = 0,
    GPIO_PULL_UP = 1,
    GPIO_PULL_DOWN = 2
} GPIO_PUPD_t;

typedef struct {
    GPIO_TypeDef *GPIOx;
    uint32_t Pin;
    GPIO_Mode_t Mode;
    GPIO_Output_Type_t OType;
    GPIO_Speed_t Speed;
    GPIO_PUPD_t Pupdr;
    uint8_t Alternate;
} GPIO_InitTypeDef;

void GPIO_Init(GPIO_TypeDef *GPIOx, const GPIO_InitTypeDef *config);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t pin, uint8_t state);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pin);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pin);
#endif
