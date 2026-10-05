#ifndef STM32F030X8_H
#define STM32F030X8_H

#include <stdint.h>

/*
 * STM32F030R8 / STM32F030x8 register-level device header.
 * Target: STM32F030R8T6, Cortex-M0, 64 KB Flash, 8 KB SRAM.
 *
 * Register layout is based on ST RM0360 and the STM32F030x8 device
 * definitions. No STM32 HAL/CMSIS header is required by this project.
 */

#define PERIPH_BASE              0x40000000UL
#define AHBPERIPH_BASE           0x40020000UL
#define APB2PERIPH_BASE          0x40010000UL
#define APB1PERIPH_BASE          0x40000000UL

#define FLASH_BASE_ADDR          0x08000000UL
#define SRAM_BASE_ADDR           0x20000000UL
#define SRAM_END_ADDR            0x20002000UL

#define GPIOA_BASE_ADDR          0x48000000UL
#define GPIOB_BASE_ADDR          0x48000400UL
#define GPIOC_BASE_ADDR          0x48000800UL
#define GPIOD_BASE_ADDR          0x48000C00UL
#define GPIOF_BASE_ADDR          0x48001400UL

#define RCC_BASE_ADDR            0x40021000UL
#define EXTI_BASE_ADDR           0x40010400UL
#define SYSCFG_BASE_ADDR         0x40010000UL

#define ADC1_BASE_ADDR           0x40012400UL
#define I2C1_BASE_ADDR           0x40005400UL
#define I2C2_BASE_ADDR           0x40005800UL
#define SPI1_BASE_ADDR           0x40013000UL
#define SPI2_BASE_ADDR           0x40003800UL
#define USART1_BASE_ADDR         0x40013800UL
#define USART2_BASE_ADDR         0x40004400UL

#define SCS_BASE_ADDR            0xE000E000UL
#define NVIC_BASE_ADDR           0xE000E100UL

typedef struct {
    volatile uint32_t MODER;       /* 0x00 */
    volatile uint32_t OTYPER;      /* 0x04 */
    volatile uint32_t OSPEEDR;     /* 0x08 */
    volatile uint32_t PUPDR;       /* 0x0C */
    volatile uint32_t IDR;         /* 0x10 */
    volatile uint32_t ODR;         /* 0x14 */
    volatile uint32_t BSRR;        /* 0x18 */
    volatile uint32_t LCKR;        /* 0x1C */
    volatile uint32_t AFRL;        /* 0x20 */
    volatile uint32_t AFRH;        /* 0x24 */
    volatile uint32_t BRR;         /* 0x28 */
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR;          /* 0x00 */
    volatile uint32_t CFGR;        /* 0x04 */
    volatile uint32_t CIR;         /* 0x08 */
    volatile uint32_t APB2RSTR;    /* 0x0C */
    volatile uint32_t APB1RSTR;    /* 0x10 */
    volatile uint32_t AHBENR;      /* 0x14 */
    volatile uint32_t APB2ENR;     /* 0x18 */
    volatile uint32_t APB1ENR;     /* 0x1C */
    volatile uint32_t BDCR;        /* 0x20 */
    volatile uint32_t CSR;         /* 0x24 */
    volatile uint32_t AHBRSTR;     /* 0x28 */
    volatile uint32_t CFGR2;       /* 0x2C */
    volatile uint32_t CFGR3;       /* 0x30 */
    volatile uint32_t CR2;         /* 0x34 */
} RCC_TypeDef;

typedef struct {
    volatile uint32_t IMR;         /* 0x00 */
    volatile uint32_t EMR;         /* 0x04 */
    volatile uint32_t RTSR;        /* 0x08 */
    volatile uint32_t FTSR;        /* 0x0C */
    volatile uint32_t SWIER;       /* 0x10 */
    volatile uint32_t PR;          /* 0x14 */
} EXTI_TypeDef;

typedef struct {
    volatile uint32_t CFGR1;       /* 0x00 */
    volatile uint32_t RCR;         /* 0x04 */
    volatile uint32_t EXTICR[4];   /* 0x08 */
    volatile uint32_t CFGR2;       /* 0x18 */
} SYSCFG_TypeDef;

typedef struct {
    volatile uint32_t ISR;         /* 0x00 */
    volatile uint32_t IER;         /* 0x04 */
    volatile uint32_t CR;          /* 0x08 */
    volatile uint32_t CFGR1;       /* 0x0C */
    volatile uint32_t CFGR2;       /* 0x10 */
    volatile uint32_t SMPR;        /* 0x14 */
    volatile uint32_t TR;          /* 0x18 */
    volatile uint32_t CHSELR;      /* 0x1C */
    uint32_t RESERVED0[8];         /* 0x20..0x3C */
    volatile uint32_t DR;          /* 0x40 */
} ADC_TypeDef;

typedef struct {
    volatile uint32_t CR1;         /* 0x00 */
    volatile uint32_t CR2;         /* 0x04 */
    volatile uint32_t OAR1;        /* 0x08 */
    volatile uint32_t OAR2;        /* 0x0C */
    volatile uint32_t TIMINGR;     /* 0x10 */
    volatile uint32_t TIMEOUTR;    /* 0x14 */
    volatile uint32_t ISR;         /* 0x18 */
    volatile uint32_t ICR;         /* 0x1C */
    volatile uint32_t PECR;        /* 0x20 */
    volatile uint32_t RXDR;        /* 0x24 */
    volatile uint32_t TXDR;        /* 0x28 */
} I2C_TypeDef;

typedef struct {
    volatile uint32_t CR1;         /* 0x00 */
    volatile uint32_t CR2;         /* 0x04 */
    volatile uint32_t SR;          /* 0x08 */
    volatile uint32_t DR;          /* 0x0C */
    volatile uint32_t CRCPR;       /* 0x10 */
    volatile uint32_t RXCRCR;      /* 0x14 */
    volatile uint32_t TXCRCR;      /* 0x18 */
    volatile uint32_t I2SCFGR;     /* 0x1C */
    volatile uint32_t I2SPR;       /* 0x20 */
} SPI_TypeDef;

typedef struct {
    volatile uint32_t CR1;         /* 0x00 */
    volatile uint32_t CR2;         /* 0x04 */
    volatile uint32_t CR3;         /* 0x08 */
    volatile uint32_t BRR;         /* 0x0C */
    volatile uint32_t GTPR;        /* 0x10 */
    volatile uint32_t RTOR;        /* 0x14 */
    volatile uint32_t RQR;         /* 0x18 */
    volatile uint32_t ISR;         /* 0x1C */
    volatile uint32_t ICR;         /* 0x20 */
    volatile uint32_t RDR;         /* 0x24 */
    volatile uint32_t TDR;         /* 0x28 */
} USART_TypeDef;

typedef struct {
    volatile uint32_t ISER[1];
    uint32_t RESERVED0[31];
    volatile uint32_t ICER[1];
    uint32_t RESERVED1[31];
    volatile uint32_t ISPR[1];
    uint32_t RESERVED2[31];
    volatile uint32_t ICPR[1];
    uint32_t RESERVED3[31];
    volatile uint32_t IABR[1];
    uint32_t RESERVED4[63];
    volatile uint8_t IPR[32];
} NVIC_TypeDef;

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE_ADDR)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE_ADDR)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE_ADDR)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE_ADDR)
#define GPIOF ((GPIO_TypeDef *)GPIOF_BASE_ADDR)
#define RCC   ((RCC_TypeDef *)RCC_BASE_ADDR)
#define EXTI  ((EXTI_TypeDef *)EXTI_BASE_ADDR)
#define SYSCFG ((SYSCFG_TypeDef *)SYSCFG_BASE_ADDR)
#define ADC1  ((ADC_TypeDef *)ADC1_BASE_ADDR)
#define I2C1  ((I2C_TypeDef *)I2C1_BASE_ADDR)
#define I2C2  ((I2C_TypeDef *)I2C2_BASE_ADDR)
#define SPI1  ((SPI_TypeDef *)SPI1_BASE_ADDR)
#define SPI2  ((SPI_TypeDef *)SPI2_BASE_ADDR)
#define USART1 ((USART_TypeDef *)USART1_BASE_ADDR)
#define USART2 ((USART_TypeDef *)USART2_BASE_ADDR)
#define NVIC ((NVIC_TypeDef *)NVIC_BASE_ADDR)

/* RCC AHBENR */
#define RCC_AHBENR_GPIOAEN     (1UL << 17)
#define RCC_AHBENR_GPIOBEN     (1UL << 18)
#define RCC_AHBENR_GPIOCEN     (1UL << 19)
#define RCC_AHBENR_GPIODEN     (1UL << 20)
#define RCC_AHBENR_DMA1EN      (1UL << 0)

/* RCC APB2ENR */
#define RCC_APB2ENR_SYSCFGEN   (1UL << 0)
#define RCC_APB2ENR_ADCEN      (1UL << 9)
#define RCC_APB2ENR_SPI1EN     (1UL << 12)
#define RCC_APB2ENR_USART1EN   (1UL << 14)

/* RCC APB1ENR */
#define RCC_APB1ENR_SPI2EN     (1UL << 14)
#define RCC_APB1ENR_USART2EN   (1UL << 17)
#define RCC_APB1ENR_I2C1EN     (1UL << 21)
#define RCC_APB1ENR_I2C2EN     (1UL << 22)

/* EXTI */
#define EXTI_LINE(n)           (1UL << (n))

/* USART */
#define USART_CR1_UE            (1UL << 0)
#define USART_CR1_RE            (1UL << 2)
#define USART_CR1_TE            (1UL << 3)
#define USART_CR1_RXNEIE        (1UL << 5)
#define USART_CR1_TXEIE         (1UL << 7)
#define USART_CR1_PCE           (1UL << 10)
#define USART_CR1_PS            (1UL << 9)
#define USART_CR1_M0            (1UL << 12)
#define USART_CR2_STOP_Pos      12U
#define USART_CR2_STOP_Msk      (3UL << USART_CR2_STOP_Pos)
#define USART_ISR_RXNE          (1UL << 5)
#define USART_ISR_TC            (1UL << 6)
#define USART_ISR_TXE           (1UL << 7)
#define USART_ISR_ORE           (1UL << 3)
#define USART_ICR_ORECF         (1UL << 3)

/* SPI */
#define SPI_CR1_CPHA            (1UL << 0)
#define SPI_CR1_CPOL            (1UL << 1)
#define SPI_CR1_MSTR            (1UL << 2)
#define SPI_CR1_BR_Pos          3U
#define SPI_CR1_SPE             (1UL << 6)
#define SPI_CR1_LSBFIRST        (1UL << 7)
#define SPI_CR1_SSI             (1UL << 8)
#define SPI_CR1_SSM             (1UL << 9)
#define SPI_CR2_RXDMAEN         (1UL << 0)
#define SPI_CR2_TXDMAEN         (1UL << 1)
#define SPI_CR2_SSOE            (1UL << 2)
#define SPI_CR2_FRF             (1UL << 4)
#define SPI_CR2_FRXTH           (1UL << 12)
#define SPI_CR2_DS_Pos          8U
#define SPI_CR2_DS_Msk          (7UL << SPI_CR2_DS_Pos)
#define SPI_SR_RXNE             (1UL << 0)
#define SPI_SR_TXE              (1UL << 1)
#define SPI_SR_BSY              (1UL << 7)

/* I2C */
#define I2C_CR1_PE              (1UL << 0)
#define I2C_CR1_TXIE            (1UL << 1)
#define I2C_CR1_RXIE            (1UL << 2)
#define I2C_CR1_ADDRIE          (1UL << 3)
#define I2C_CR1_STOPIE          (1UL << 5)
#define I2C_CR1_TCIE            (1UL << 6)
#define I2C_CR1_ERRIE           (1UL << 7)
#define I2C_CR2_SADD_Pos        0U
#define I2C_CR2_SADD_Msk        (0x3FFUL << I2C_CR2_SADD_Pos)
#define I2C_CR2_RD_WRN          (1UL << 10)
#define I2C_CR2_START           (1UL << 13)
#define I2C_CR2_STOP            (1UL << 14)
#define I2C_CR2_NBYTES_Pos      16U
#define I2C_CR2_NBYTES_Msk      (0xFFUL << I2C_CR2_NBYTES_Pos)
#define I2C_CR2_RELOAD          (1UL << 24)
#define I2C_CR2_AUTOEND         (1UL << 25)
#define I2C_ISR_TXIS            (1UL << 1)
#define I2C_ISR_RXNE            (1UL << 2)
#define I2C_ISR_NACKF           (1UL << 4)
#define I2C_ISR_STOPF           (1UL << 5)
#define I2C_ISR_TC              (1UL << 6)
#define I2C_ISR_TCR             (1UL << 7)
#define I2C_ISR_BUSY            (1UL << 15)
#define I2C_ICR_NACKCF          (1UL << 4)
#define I2C_ICR_STOPCF          (1UL << 5)

/* ADC */
#define ADC_ISR_ADRDY           (1UL << 0)
#define ADC_ISR_EOSMP           (1UL << 1)
#define ADC_ISR_EOC             (1UL << 2)
#define ADC_ISR_EOS             (1UL << 3)
#define ADC_ISR_OVR             (1UL << 4)
#define ADC_ISR_AWD             (1UL << 7)
#define ADC_CR_ADEN             (1UL << 0)
#define ADC_CR_ADDIS            (1UL << 1)
#define ADC_CR_ADSTART          (1UL << 2)
#define ADC_CR_ADCAL            (1UL << 31)
#define ADC_CFGR1_DMAEN         (1UL << 0)
#define ADC_CFGR1_DMACFG        (1UL << 1)
#define ADC_CFGR1_SCANDIR       (1UL << 2)
#define ADC_CFGR1_RES_Pos       3U
#define ADC_CFGR1_RES_Msk       (3UL << ADC_CFGR1_RES_Pos)
#define ADC_CFGR1_ALIGN         (1UL << 5)
#define ADC_CFGR1_CONT          (1UL << 13)
#define ADC_CFGR1_WAIT          (1UL << 14)
#define ADC_CFGR1_AUTOFF        (1UL << 15)
#define ADC_CFGR1_DISCEN        (1UL << 16)
#define ADC_SMPR_SMP_Pos        0U
#define ADC_SMPR_SMP_Msk        (7UL << ADC_SMPR_SMP_Pos)

/* Cortex-M0 core */
#define SCB_CPUID_ADDR          0xE000ED00UL
#define SCB_ICSR_ADDR           0xE000ED04UL
#define SCB_VTOR_ADDR           0xE000ED08UL

#endif
