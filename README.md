# STM32F030x4/x6/x8/xC Register-Level Driver Library

Targeted reference implementation: **STM32F030R8T6 / NUCLEO-F030R8**.

This project uses direct peripheral registers and does not depend on STM32 HAL.

## Supported in this F030R8 example

- GPIO
- RCC
- EXTI
- SYSCFG
- NVIC
- USART1/USART2 register definitions; example uses USART2
- SPI1/SPI2; example uses SPI2
- I2C1/I2C2; example uses I2C1
- ADC1
- Cortex-M0 startup/vector table

## CAN

STM32F030R8 has **no integrated CAN controller**. Therefore `CAN_Driver.h/.c`
contains a compile-safe interface that returns `CAN_STATUS_UNSUPPORTED`.

Do not add invented CAN registers to `STM32F030x8.h`.

To implement real CAN, move the CAN driver to an MCU that contains CAN
and create a device-specific register layer for that MCU.

## NUCLEO-F030R8 example pin plan

| Function | Pin |
|---|---|
| LED | PA5 |
| User button | PC13 |
| USART2 TX | PA2 |
| USART2 RX | PA3 |
| SPI2 SCK | PB13 |
| SPI2 MISO | PB14 |
| SPI2 MOSI | PB15 |
| I2C1 SCL | PB6 |
| I2C1 SDA | PB7 |
| ADC1 channel 0 | PA0 |

SPI2 is used so PA5 remains available for the Nucleo LED.

## Build

```bash
make clean
make
```

Expected output is an ELF and BIN under `build/`.

Flash:

```bash
make flash
```

## Serial example

USART2 is configured for:

- 9600 baud
- 8 data bits
- no parity
- 1 stop bit

The Nucleo ST-LINK virtual COM connection can be used with the USART2 pins
through the board's standard routing/configuration.

## Important

The I2C TIMINGR value in `main.c` is an example and must be validated for
the actual I2C clock, requested bus speed, and pull-up/rise-time conditions
before production use.
