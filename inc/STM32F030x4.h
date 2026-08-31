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

/* USART peripheral base address */
#define USART1_BASE_ADDRESS             0x40013800UL
#define USART2_BASE_ADDRESS             0x40004400UL
#define USART3_BASE_ADDRESS             0x40004800UL
#define USART4_BASE_ADDRESS             0x40004C00UL
#define USART5_BASE_ADDRESS             0x40005000UL
#define USART6_BASE_ADDRESS             0x40011400UL

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

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t BRR;
    volatile uint32_t GTPR;
    volatile uint32_t RTOR;
    volatile uint32_t RQR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t RDR;
    volatile uint32_t TDR;
} USART_TypeDef;

#define USART1 ((USART_TypeDef *)USART1_BASE_ADDRESS)

#define USART_CR1_UE                 (1U << 0U)
#define USART_CR1_RE                 (1U << 2U)
#define USART_CR1_TE                 (1U << 3U)
#define USART_ISR_RXNE               (1U << 5U)
#define USART_ISR_TXE                (1U << 7U)

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



/*ADC related macro definition and pointer and structer */


/*create the Address for ADC*/
#define ADC_BASE_ADDR   0x40012400UL

/*ADC pointer typecaste*/
#define ADC     ((ADC_TypeDef *)ADC_BASE_ADDR)  

/*create the structer for ADC*/
typedef struct
{  
    volatile uint32_t ISR;          /*!< ADC interrupt and status register,         Address offset: 0x00     */
    volatile uint32_t IER;          /*!< ADC interrupt enable register,             Address offset: 0x04     */
    volatile uint32_t CR;           /*!< ADC control register,                      Address offset:0x08      */
    volatile uint32_t CFGR1;        /*!< ADC configuration register 1,              Address offset:0x0C      */ 
    volatile uint32_t CFGR2;        /*!< ADC configuration register 2,              Address offset:0x10      */
    volatile uint32_t SMPR;         /*!< ADC sample time register,                  Address offset:0x14      */
    volatile uint32_t TR;           /*!< ADC watchdog threshold register,           Address offset:0x18      */
    volatile uint32_t CHSELR;       /*!< ADC channel selection register,            Address offset:0x1C      */
    volatile uint32_t RESERVED1;    /*!< Reserved,                                  Address offset:0x20      */
    volatile uint32_t RESERVED2;    /*!< Reserved,                                  Address offset:0x24      */
    volatile uint32_t RESERVED3;    /*!< Reserved,                                  Address offset:0x28      */
    volatile uint32_t RESERVED4;    /*!< Reserved,                                  Address offset:0x2C      */
    volatile uint32_t DR;           /*!< ADC data register,                         Address offset:0x30      */ 
    volatile uint32_t RESERVED5;    /*!< Reserved,                                  Address offset:0x34      */
    volatile uint32_t RESERVED6;    /*!< Reserved,                                  Address offset:0x38      */
    volatile uint32_t RESERVED7;    /*!< Reserved,                                  Address offset:0x3C      */
    volatile uint32_t ADC_CCR;      /*!<ADC common configuration register,         Address offset:0x308     */   

} ADC_TypeDef;

/*Create the ADC interrupt macros */

#define ADC_ISR_AWD     (1U << 7U)
#define ADC_ISR_OVR     (1U << 4U)
#define ADC_ISR_EOS     (1U << 3U)
#define ADC_ISR_EOC     (1U << 2U)  
#define ADC_ISR_EOSMP   (1U << 1U)
#define ADC_ISR_ADRDY   (1U << 0U)

/*create thew ADC interrupt enable register micro definition*/

#define ADC_IER_AWDIE   (1U << 7U)      /*Analog watchdog interrupt enable*/
#define ADC_IER_OVRIE   (1U << 4U)      /*Overrun interrupt enable*/
#define ADC_IER_EOSIE   (1U << 3U)      /*End of sequence interrupt enable*/
#define ADC_IER_EOCIE   (1U << 2U)      /*End of conversion interrupt enable*/
#define ADC_IER_EOSMPIE (1U << 1U)      /*End of sampling phase interrupt enable*/
#define ADC_IER_ADRDYIE (1U << 0U)      /*ADC ready interrupt enable*/

/*create  ADC control register */

#define ADC_CR_ADCAL    (1U << 31U)     /*ADC calibration*/  
#define ADC_CR_ADSTP    (1U << 4U)      /*ADC stop conversion*/
#define ADC_CR_ADSTART  (1U << 2U)      /*ADC start conversion*/
#define ADC_CR_ADDIS    (1U << 1U)      /*ADC disable*/
#define ADC_CR_ADEN     (1U << 0U)      /*ADC enable*/

/*create the ADC micro definitions for ADC configuration register 1*/
#define ADC_CFGR1_AWDCH  (1U << 26U)     /*Analog watchdog channel selection*/
#define ADC_CFGR1_AWDEN  (1U << 23U)     /*Analog watchdog enable on regular channels*/
#define ADC_CFGR1_AWDSGL (1U << 22U)     /*Analog watchdog enable on a single channel*/
#define ADC_CFGR1_DISCEN  (1U << 16U)     /*Discontinuous mode on regular channels*/
#define ADC_CFGR1_AUTOFF  (1U << 15U)     /*Auto power off*/
#define ADC_CFGR1_WAIT    (1U << 13U)     /*Wait conversion*/
#define ADC_CFGR1_CONT    (1U << 13U)     /*Continuous conversion*/
#define ADC_CFGR1_OVRMOD  (1U << 12U)     /*Overrun mode*/
#define ADC_CFGR1_EXTEN   (1U << 10U)    /*External trigger enable and polarity selection*/
#define ADC_CFGR1_EXTSEL  (1U << 6U)     /*External event select for regular group*/
#define ADC_CFGR1_ALIGN   (1U << 5U)     /*Data alignment*/
#define ADC_CFGR1_RES     (1U << 3U)     /*Data resolution*/    
#define ADC_CFGR1_SCANDIR (1U << 2U)     /*Sequencer scan direction*/   
#define ADC_CFGR1_DMAEN   (1U << 0U)     /*Direct memory access enable*/

/*create the ADC micro definitions for ADC configuration register 2 */

#define ADC_CFGR2_CKMODE  (1U << 30U)    /*ADC clock mode*/

/*create the ADC micro definitions for ADC sampling time register */

#define ADC_SMPR_SMP    (1U << 0U)      /*Sampling time selection*/
    
/*create the ADC micro definitions for ADC channel selection register*/

#define ADC_CHSELR_CHSEL (1U << 0U)      /*Channel selection for regular conversion*/

/*create the ADC micro definitions for ADC data register*/

#define ADC_DR_DATA (1U << 0U)          /*ADC conversion data*/

/*create the ADC micro definitions for ADC channel selection register */

#define ADC_CCR_TSEN (1U << 23U)      /*Temperature sensor enable*/
#define ADC_CCR_VREFEN (1U << 22U)    /*VREFINT enable*/


/* SPI protocal micro register and prepherical detial */

/*SPI peripheral register*/

#define SPI1_BASE_ADDR   0x40013000UL
#define SPI2_BASE_ADDR   0x40003800UL

/*create the Struct for SPI */

typedef struct 
{
    volatile uint32_t   SPIx_CR1;
    volatile uint32_t   SPIx_CR2;
    volatile uint32_t   SPIx_SR;
    volatile uint32_t   SPIx_DR;
    volatile uint32_t   SPIx_CRCPR;
    volatile uint32_t   SPIx_RXCRCR;
    volatile uint32_t   SPIx_TXCRCR;
}SPIreg;

/*SPI pointer */
#define SPI1    ((SPIreg*)SPI1_BASE_ADDR) 
#define SPI2    ((SPIreg*)SPI2_BASE_ADDR) 


/* SPI control register 1 */

#define SPIx_CR1_BIDIMODE   (1U<<15U)
#define SPIx_CR1_BIDIOE     (1U<<14U)
#define SPIx_CR1_CRCEN      (1U<<13U)
#define SPIx_CR1_CRCNEXT    (1U<<12U)
#define SPIx_CR1_CRCL       (1U<<11U)
#define SPIx_CR1_RXONLY     (1U<<10U)
#define SPIx_CR1_SSM        (1U<<9U)
#define SPIx_CR1_SSI        (1U<<8U)
#define SPIx_CR1_LSBFIRST   (1U<<7U)
#define SPIx_CR1_SPE        (1U<<6U)
#define SPIx_CR1_BR         (1U<<5U)
#define SPIx_CR1_MSTR       (1U<<2U)
#define SPIx_CR1_CPOL       (1U<<1U)
#define SPIx_CR1_CPHA       (1U<<0U)

/* SPI control register 2  */

#define SPIx_CR2_LDMA_TX    (1U << 14U)
#define SPIx_CR2_LDMA_RX    (1U << 13U)
#define SPIx_CR2_FRXTH      (1U << 12U)
#define SPIx_CR2_DS         (0xFU << 8U)
#define SPIx_CR2_TXEIE      (1U << 7U)
#define SPIx_CR2_RXNEIE     (1U << 6U)
#define SPIx_CR2_ERRIE      (1U << 5U)
#define SPIx_CR2_FRF        (1U << 4U)
#define SPIx_CR2_NSSP       (1U << 3U)
#define SPIx_CR2_SSOE       (1U << 2U)
#define SPIx_CR2_TXDMAEN    (1U << 1U)
#define SPIx_CR2_RXDMAEN    (1U << 0U)

/* SPI status register */

#define SPIx_SR_FTLVL       (0x3U << 11U)
#define SPIx_SR_FRLVL       (0x3U << 9U)
#define SPIx_SR_FRE         (1U << 8U)
#define SPIx_SR_BSY         (1U << 7U)
#define SPIx_SR_OVR         (1U << 6U)
#define SPIx_SR_MODF        (1U << 5U)
#define SPIx_SR_CRCE        (1U << 4U)
#define SPIx_SR_RESERVED3   (1U << 3U)
#define SPIx_SR_RESERVED2   (1U << 2U)
#define SPIx_SR_TXE         (1U << 1U)
#define SPIx_SR_RXNE        (1U << 0U)

/* SPI data register */

#define SPIx_DR_DR          (0xFFFFU << 0U)

/* SPI CRC polynomial register */

#define SPIx_CRCPR_CRCPOLY  (0xFFFFU << 0U)

/* SPI Rx CRC register */

#define SPIx_RXCRCR_RXCRC   (0xFFFFU << 0U)

/* SPI Tx CRC register */

#define SPIx_TXCRCR_TXCRC   (0xFFFFU << 0U)









#endif /* STM32F030X4_H */