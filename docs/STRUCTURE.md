# Project Structure

```text
Driver-for-STM32F030x4-x6-x8-xC/
├── inc/
│   ├── STM32F030x8.h
│   ├── GPIO_Driver.h
│   ├── RCC_Driver.h
│   ├── NVIC_Driver.h
│   ├── EXTI_Driver.h
│   ├── SYSCONFIG_Driver.h
│   ├── USART_Driver.h
│   ├── SPI_Driver.h
│   ├── I2C_Driver.h
│   ├── ADC_Driver.h
│   └── CAN_Driver.h
│
├── src/
│   ├── main.c
│   ├── GPIO_Driver.c
│   ├── RCC_Driver.c
│   ├── NVIC_Driver.c
│   ├── EXTI_Driver.c
│   ├── SYSCONFIG_Driver.c
│   ├── USART_Driver.c
│   ├── SPI_Driver.c
│   ├── I2C_Driver.c
│   ├── ADC_Driver.c
│   └── CAN_Driver.c
│
├── docs/
│   └── STRUCTURE.md
├── startup.s
├── linker.ld
├── Makefile
└── README.md
```

## Driver layering

```text
main.c
  |
  +-- GPIO_Driver
  +-- RCC_Driver
  +-- NVIC_Driver
  +-- EXTI_Driver
  +-- SYSCONFIG_Driver
  +-- USART_Driver
  +-- SPI_Driver
  +-- I2C_Driver
  +-- ADC_Driver
  +-- CAN_Driver (unsupported stub on F030R8)
          |
          v
    STM32F030x8.h
          |
          v
    STM32F030R8 hardware registers
```

`STM32F030x8.h` is the single hardware-register source of truth.

Driver headers contain configuration/API types. They should not duplicate
peripheral register layouts.

## Register map principles

- GPIO AFRL is at 0x20.
- GPIO AFRH is at 0x24.
- ADC DR is at 0x40.
- I2C uses the modern CR1/CR2/TIMINGR/ISR/ICR/RXDR/TXDR register layout.
- SPI1 = 0x40013000, SPI2 = 0x40003800.
- I2C1 = 0x40005400, I2C2 = 0x40005800.
- USART1 = 0x40013800, USART2 = 0x40004400.
- SRAM starts at 0x20000000 on Cortex-M STM32F030R8.

## Why CAN is not a register driver here

The F030R8 peripheral set includes I2C, SPI, USART and ADC but not CAN.
A fake CAN register block would make this educational driver library
incorrect. The interface is therefore separated so a future MCU-specific
CAN implementation can be added without contaminating the F030 register map.
