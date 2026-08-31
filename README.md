# STM32F030x4 Device Driver

## Overview

This repository contains device drivers for the STM32F030x4 microcontroller.

## Hardware

- **MCU**: STM32F030x4
- **Architecture**: ARM Cortex-M0
- **Flash**: 16 KB
- **SRAM**: 4 KB
- **GPIO**: Up to 16 pins
- **Peripherals**: GPIO, EXTI, NVIC, RCC ,I2C,SPI,ADC

## Features

- GPIO Driver
- EXTI Driver
- NVIC Driver
- RCC Driver
- SYSCFG Driver
- ADC Driver
- SPI Driver
- I2C Driver 

## Pinout

| Pin | Function |
|-----|---------|
| PA0 | GPIO_Input |
| PA1 | GPIO_Output |
| PA2 | GPIO_AF0 |
| PA3 | GPIO_AF1 |
| PA4 | GPIO_Analog |
| PA5 | GPIO_Event |

## Build Instructions

### Prerequisites

- ARM GCC Toolchain
- Make Utility
- OpenOCD (for debugging)

### Build Steps

```bash
make clean
make all
