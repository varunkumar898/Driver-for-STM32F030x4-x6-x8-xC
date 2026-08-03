#ifndef STM32F030X4_H
#define STM32F030X4_H
#include <stdint.h>
/*=========================================================
    * STM32F030x4
*=========================================================*/
/* All marco related to STM32F030x4 device should be defined in this peripheral address ,sram,flash,address.
 *Data structure related to peripheral
 *peripheral bit definition*/

#define SRAM_BASE_ADDR          0x00000000UL
#define SRAM_END_ADDR           0x00040000UL
#define FLASH_MEMORY_BASE_ADDR  0x08000000UL
#define FLASH_MEMORY_END_ADDR   0x08040000UL
#define SYSTEM_MEMORY_BASE_ADDR 0x1FFFF0000UL
#define SYSTEM_MEMORY_END_ADDR  0x1FFFF800UL
#define OPTION_BYTES_BASE_ADDR  0x1FFFF800UL
#define OPTION_BYTES_END_ADDR   0x1FFFFC00UL

/*PB & AHB peripheral base address */
#define APB1peripheral_BASE_ADDRESS     0x40000000UL
#define APB1peripheral_END_ADDRESS      0x40008000UL
#define APB2peripheral_BASE_ADDRESS     0x40010000UL
#define APB2peripheral_END_ADDRESS      0x40018000UL

#define AHB1peripheral_BASE_ADDRESS     0x40020000UL
#define AHB1peripheral_END_ADDRESS      0x400243FFUL
#define AHB2peripheral_BASE_ADDRESS     0x48000000UL
#define AHB2peripheral_END_ADDRESS      0x480017FFUL

/* RCC peripheral base address */
#define RCC_BASE_ADDR                   0x40021000UL

/* GPIO peripheral base address */
#define GPIOA_BASE_ADDR    (AHB2peripheral_BASE_ADDRESS + 0x0000UL)
#define GPIOB_BASE_ADDR    (AHB2peripheral_BASE_ADDRESS + 0x0400UL)
#define GPIOC_BASE_ADDR    (AHB2peripheral_BASE_ADDRESS + 0x0800UL)
#define GPIOD_BASE_ADDR    (AHB2peripheral_BASE_ADDRESS + 0x0C00UL)
#define GPIOF_BASE_ADDR    (AHB2peripheral_BASE_ADDRESS + 0x1400UL)

/*EXTI interrupt numbers */
#define EXTI0_1IRQn     5
#define EXTI2_3IRQn     6
#define EXTI4_15IRQn    7

#define EXTI0_1IRQu     EXTI0_1IRQn
#define EXTI2_3IRQu     EXTI2_3IRQn
#define EXTI4_15IRQu    EXTI4_15IRQn

/*NVIC peripheral register base address */
#define NVIC_BASE_ADDR                    0xE000E100UL

#define NVIC_ISERx_ADDR         (volatile uint32_t*)NVIC_BASE_ADDR
#define NVIC_ICERX_ADDR         (volatile uint32_t*)(NVIC_BASE_ADDR + 0x80UL)
#define NVIC_ISPRX_ADDR         (volatile uint32_t*)(NVIC_BASE_ADDR + 0x100UL)
#define NVIC_ICPRX_ADDR         (volatile uint32_t*)(NVIC_BASE_ADDR + 0x180UL)
#define NVIC_IABRX_ADDR         (volatile uint32_t*)(NVIC_BASE_ADDR + 0X300UL)



/*EXTI structer define */
typedef struct 
{
    volatile uint32_t EXTI_IMR;     /*exti register for EXTI_IMR, Address offset, 0x00*/
    volatile uint32_t EXTI_EMR;     /*exti register for EXTI_EMR, Address offset, 0x04*/
    volatile uint32_t EXTI_RTSR;    /*exti register for EXTI_RTSR ,Address offset, 0x08*/
    volatile uint32_t EXTI_FTSR;    /*exti register for EXTI_FTSR ,Address offset, 0x08*/
    volatile uint32_t EXTI_SWIER;   /*exti register for EXTI_SWIER ,Address offset, 0x10*/
    volatile uint32_t EXTI_PR;      /*exti register for EXTI_PR ,Address offset, 0x14*/
}EXTI_TypeDef;

/*EXTI peripheral base address*/

#define EXTI_BASE_ADDRESS               0x40010400UL
#define EXTI ((EXTI_TypeDef*)EXTI_BASE_ADDRESS)

/*set macreo for GPIO structure*/
typedef struct
{
    volatile uint32_t MODER;   /*!< GPIO port mode register,               Address offset: 0x00      */
    volatile uint32_t OTYPER;  /*!< GPIO port output type register,          Address offset: 0x04      */
    volatile uint32_t OSPEEDR; /*!< GPIO port output speed register,         Address offset: 0x08      */
    volatile uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register, Address offset: 0x0C      */
    volatile uint32_t IDR;     /*!< GPIO port input data register,           Address offset: 0x10      */
    volatile uint32_t ODR;     /*!< GPIO port output data register,          Address offset: 0x14      */
    volatile uint32_t BSRR;    /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
    volatile uint32_t LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C      */
    volatile uint32_t AFRH;    /*!< GPIO alternate function registers,      Address offset: 0x20 */
    volatile uint32_t AFRL;    /*!< GPIO alternate function registers,      Address offset: 0x24 */
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE_ADDR)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE_ADDR)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE_ADDR)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE_ADDR)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASE_ADDR)


/* RRC structure definition */
typedef struct
{

    volatile uint32_t CR;            /*!< RCC clock control register,                                  Address offset:  0x00 */
    volatile uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset:  0x04 */
    volatile uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset:  0x08 */
    volatile uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset                                    Address offset:  0x0C */
    volatile uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset                                    Address offset:  0x010 */
    volatile uint32_t AHBENR;        /*!< RCC AHB peripheral clock enable register,                    Address offset:  0x014 */
    volatile uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset:  0x018 */
    volatile uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset:  0x01C */
    volatile uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset:  0x020 */
    volatile uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset:  0x024 */    
    volatile uint32_t AHBRSTR;        /*!< RCC AHB peripheral reset register,                          Address offset:  0x028 */   
    volatile uint32_t CFGR2;         /*!< RCC clock configuration register 2,                          Address offset:  0x02C */   
    volatile uint32_t CFGR3;         /*!< RCC clock configuration register 3,                          Address offset:  0x030 */
    volatile uint32_t CR2;           /*!< RCC clock control register 2,                                Address offset:  0x034 */    

} RCC_TypeDef;

/*create the pointer to the GPIO structure*/

#define GPIO     ((GPIO_TypeDef *)GPIOA_BASE_ADDR)

/* sys config related macro definition */

typedef struct
{
    volatile uint32_t CFGR1;   /*!< SYSCFG configuration register 1,          Address offset: 0x00      */
    volatile uint32_t Reserved; /*!< Reserved,                                 Address offset: 0x04      */
    volatile uint32_t EXTICR[4]; /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
    volatile uint32_t CFGR2;   /*!< SYSCFG configuration register 2,          Address offset: 0x18      */
} SYSCFG_Reg;


/*sys config related macro definition*/
#define SYSCFG_BASE_ADDR 0x40010000UL

/*create the pointer to the SYSCFG structure*/
#define SYSCFG ((SYSCFG_Reg *)SYSCFG_BASE_ADDR)

/*create the pointer to the RCC structure*/

#define RCC    ((RCC_TypeDef *)RCC_BASE_ADDR)

#endif /* STM32F030X4_H */