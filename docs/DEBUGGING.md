# Common Issues & Solutions

This document details practical debugging scenarios, root causes, and solutions encountered during the development and validation of the bare-metal STM32F030 HAL drivers.

---

## Issue 1: I2C Clock Stretching Timeout

**Symptom:** I2C master hangs or encounters early timeout when communicating with slower I2C slave devices.

**Root Cause:** The initial implementation did not properly handle the slave holding the SCL line low during internal processing (clock stretching). A hardcoded timeout counter expired before the slave released SCL.

**Solution:** Updated the I2C transfer routine to poll and wait for SCL release with a calibrated timeout parameter before asserting data or stop conditions.

**How to Debug:** Connect a logic analyzer to SCL and SDA. Check whether SCL remains held low by the slave after an ACK bit before suspecting an MCU bus error.

---

## Issue 2: ADC Data Corruption Under High Interrupt Load

**Symptom:** ADC readings sporadically show corrupted or out-of-order conversion values during continuous sampling.

**Root Cause:** When high-frequency external interrupts (EXTI) fired concurrently with the ADC End-of-Conversion (EOC) flag, the lower-priority interrupt handler suffered latency, causing the ADC data register (`DR`) to be overwritten by the next conversion before being read (overrun condition).

**Solution:** 
1. Increased ADC interrupt priority (`NVIC_SetPriority(ADC1_COMP_IRQn, 0)`) relative to non-critical EXTI lines.
2. Read the `ADC_DR` register immediately upon entry into the ISR and checked the `OVR` (overrun) flag in `ADC_ISR`.

**How to Debug:** Use GDB to set a breakpoint inside `ADC1_COMP_IRQHandler()` and monitor the value of `ADC1->ISR & ADC_ISR_OVR`.

---

## Issue 3: SPI Clock Polarity and Phase Mismatches (Mode 0 vs Mode 3)

**Symptom:** First bit of SPI received data is shifted or corrupted when interfacing with SPI EEPROM / sensor chips.

**Root Cause:** Incorrect configuration of CPOL and CPHA in `SPI_CR1`. Certain SPI peripherals sample data on the first clock transition, requiring SCLK idle low (Mode 0), whereas others expect Mode 3.

**Solution:** Explicitly exposed `clock_polarity` and `clock_phase` configuration fields in the `SPI_Config_t` initialization structure.

**How to Debug:** Trigger a digital logic analyzer on the Chip Select (CS) falling edge and compare the SCLK idle level and data transition timing against the slave device's datasheet timing diagram.

---

## Issue 4: System Hangs Immediately After Reset

**Symptom:** Firmware fails to reach `main()` or hangs in a hard fault loop upon startup.

**Root Cause:** Incorrect RCC clock tree configuration (e.g. attempting to switch system clock source to PLL or HSE before the oscillator is stable and the `HSERDY` / `PLLRDY` flag is set).

**Solution:** Added explicit readiness flag polling with timeout protection in clock configuration routines before switching the `SW` (System clock switch) bits in `RCC_CFGR`.

**How to Debug:** Attach GDB via OpenOCD, issue `mon reset halt`, and step through `rcc_init()` while inspecting register `RCC->CR` and `RCC->CFGR`.

---

## Issue 5: Peripheral Registers Inaccessible (Hard Fault / Bus Error)

**Symptom:** Writing to peripheral registers (e.g. `GPIOA->MODER`, `USART1->CR1`) triggers a HardFault or has no effect.

**Root Cause:** Clock gating for the specific peripheral was not enabled in `RCC_AHBENR` or `RCC_APB1ENR` / `RCC_APB2ENR` prior to register access.

**Solution:** Enforce enabling peripheral clock gating via `RCC_EnableGPIO()` / `RCC_EnablePeripheralClock()` before executing any peripheral initialization logic.
