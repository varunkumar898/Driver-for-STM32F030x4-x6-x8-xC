# Design Document: STM32F030 Hardware Abstraction Layer

## Overview

This document explains the architectural decisions behind the STM32F030 HAL driver suite and why each choice was made.

## Guiding Principles

1. **Transparency over abstraction** — Register-level code; understand what's actually happening
2. **Modularity** — Each driver is independent; link only what you need
3. **No dynamic memory** — All structures are static or stack-based
4. **Simplicity** — Minimize complexity to reduce debugging surface area
5. **Validation** — Every driver is tested on real hardware; no simulation-only code

## Driver Architecture

### Structure: Header + Implementation

Each driver follows this pattern:

```c
// gpio.h
typedef struct {
    uint32_t mode;          // GPIO_MODE_INPUT, GPIO_MODE_OUTPUT, GPIO_MODE_ALTERNATE
    uint32_t speed;         // GPIO_SPEED_LOW, GPIO_SPEED_HIGH
    uint32_t pull;          // GPIO_PULL_NONE, GPIO_PULL_UP, GPIO_PULL_DOWN
    uint32_t alternate;     // Alternate function (for AF pins)
} GPIO_Config_t;

void GPIO_Init(GPIO_TypeDef *gpio, uint32_t pin, GPIO_Config_t config);
void GPIO_WritePin(GPIO_TypeDef *gpio, uint32_t pin, uint32_t state);
uint32_t GPIO_ReadPin(GPIO_TypeDef *gpio, uint32_t pin);
void GPIO_TogglePin(GPIO_TypeDef *gpio, uint32_t pin);
```

**Why this design?**
- **Config struct** — Groups related settings; easy to pass around and modify
- **Named constants** — GPIO_MODE_INPUT is clearer than raw bit value (0x00)
- **Simple API** — Write, read, toggle are the only primitives needed
- **Pointer-based** — GPIOA, GPIOB passed as pointers; allows code reuse across port instances

### RCC (Clock Management)

```c
void RCC_EnablePeripheralClock(uint32_t peripheral);  // Enable clock gating
void RCC_SetSystemClock(uint32_t clock_freq);         // Configure PLL/prescalers
```

**Design decision: Centralized clock setup**

Early versions had each driver manage its own clock. Problem: If two drivers both tried to configure RCC, conflicts arose.

Solution: **Single RCC module** manages all clock initialization. Other drivers call RCC_EnablePeripheralClock() when they need a clock.

This prevents:
- Accidental clock conflicts (SPI overwrites ADC clock config)
- Cascading initialization failures (Driver A depends on Driver B's clock setup)

### NVIC (Interrupt Controller)

```c
void NVIC_EnableIRQ(IRQn_Type IRQn, uint32_t priority);
void NVIC_DisableIRQ(IRQn_Type IRQn);
void NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority);
```

**Design decision: Priority levels, not raw numbers**

Raw priorities (0–3 for STM32F030) are confusing. Instead:
- NVIC_PRIORITY_CRITICAL (0)
- NVIC_PRIORITY_HIGH (1)
- NVIC_PRIORITY_NORMAL (2)
- NVIC_PRIORITY_LOW (3)

**Why?** Makes code self-documenting. `NVIC_EnableIRQ(UART_IRQn, NVIC_PRIORITY_HIGH)` is clearer than `NVIC_EnableIRQ(UART_IRQn, 1)`.

### ADC (Analog Input)

```c
typedef struct {
    uint32_t resolution;        // ADC_RESOLUTION_12BIT, ADC_RESOLUTION_10BIT, etc.
    uint32_t scan_mode;         // ADC_SCAN_DISABLE, ADC_SCAN_ENABLE
    uint32_t continuous_mode;   // ADC_CONTINUOUS_DISABLE, ADC_CONTINUOUS_ENABLE
    uint32_t trigger_source;    // ADC_TRIGGER_SOFTWARE, ADC_TRIGGER_TIMER1, etc.
    uint32_t data_alignment;    // ADC_ALIGN_RIGHT, ADC_ALIGN_LEFT
} ADC_Config_t;

void ADC_Init(ADC_TypeDef *adc, ADC_Config_t config);
void ADC_StartConversion(ADC_TypeDef *adc);
uint32_t ADC_GetValue(ADC_TypeDef *adc);
void ADC_EnableInterrupt(ADC_TypeDef *adc);
```

**Design decision: Configuration struct + separate operations**

Early version combined init and start:

```c
// OLD: Combined init + start
ADC_Init(ADC1, 12_BIT, CONTINUOUS, SOFTWARE_TRIGGER);
// Now you MUST call ADC_StartConversion() separately
```

Problem: Unclear when ADC actually starts sampling. Some callers forgot to call Start().

**Better approach: Separate init and start.** Init configures. Start is explicit.

```c
// NEW: Init sets up, start is explicit
ADC_Config_t config = {
    .resolution = ADC_RESOLUTION_12BIT,
    .continuous_mode = ADC_CONTINUOUS_ENABLE,
    .trigger_source = ADC_TRIGGER_SOFTWARE
};
ADC_Init(ADC1, config);
ADC_StartConversion(ADC1);  // Clear when sampling begins
```

### SPI (Serial Communication)

```c
typedef struct {
    uint32_t mode;              // SPI_MODE_MASTER, SPI_MODE_SLAVE
    uint32_t clock_polarity;    // SPI_CPOL_LOW, SPI_CPOL_HIGH
    uint32_t clock_phase;       // SPI_CPHA_1EDGE, SPI_CPHA_2EDGE
    uint32_t data_size;         // SPI_DATA_8BIT, SPI_DATA_16BIT
    uint32_t baud_prescaler;    // SPI_PRESCALER_2, SPI_PRESCALER_4, etc.
    uint32_t nss_mode;          // SPI_NSS_HARDWARE, SPI_NSS_SOFTWARE
} SPI_Config_t;

void SPI_Init(SPI_TypeDef *spi, SPI_Config_t config);
void SPI_Send(SPI_TypeDef *spi, uint8_t data);
uint8_t SPI_Receive(SPI_TypeDef *spi);
```

**Design decision: Explicit baud prescaler, not frequency**

Naive approach: `SPI_Init(SPI1, 1000000);` — set baud to 1 MHz.

Problem: SPI clock divider on STM32F030 is fixed (2, 4, 8, 16, 32, 64, 128, 256). You can't get exactly 1 MHz from a 24 MHz clock.

**Better:** `SPI_Init(SPI1, SPI_PRESCALER_16);` — explicit divider. No hidden rounding errors.

Tradeoff: Slightly harder to use, but **no surprises during debugging**.

### I2C (Two-Wire Communication)

```c
typedef struct {
    uint32_t speed_mode;        // I2C_SPEED_STANDARD (100 kHz), I2C_SPEED_FAST (400 kHz)
    uint32_t addressing_mode;   // I2C_ADDR_7BIT, I2C_ADDR_10BIT
    uint32_t slave_address;     // Own address if in slave mode
} I2C_Config_t;

void I2C_Init(I2C_TypeDef *i2c, I2C_Config_t config);
void I2C_MasterStart(I2C_TypeDef *i2c);
void I2C_MasterSendAddress(I2C_TypeDef *i2c, uint8_t address, uint32_t direction);
void I2C_MasterSendByte(I2C_TypeDef *i2c, uint8_t data);
uint8_t I2C_MasterReceiveByte(I2C_TypeDef *i2c, uint8_t ack);
void I2C_MasterStop(I2C_TypeDef *i2c);
```

**Design decision: Sequence-oriented API (not high-level abstraction)**

Why not high-level?

```c
// HIGH-LEVEL: Easy but inflexible
I2C_ReadRegister(I2C1, 0x68, 0x3B, buffer, 6);  // Magic! But what if protocol changes?

// SEQUENCE-BASED: More control
I2C_MasterStart(I2C1);
I2C_MasterSendAddress(I2C1, 0x68, I2C_DIRECTION_TX);
I2C_MasterSendByte(I2C1, 0x3B);
I2C_MasterSendAddress(I2C1, 0x68, I2C_DIRECTION_RX);
for (int i = 0; i < 6; i++) {
    buffer[i] = I2C_MasterReceiveByte(I2C1, i < 5);  // ACK all but last
}
I2C_MasterStop(I2C1);
```

**Reasoning:**
- **Transparency** — Every I2C bus action is visible in code
- **Debugging** — If communication fails, you can breakpoint at each step
- **Flexibility** — Unusual I2C sequences (repeated START, address skipping) are supported

Cost: More code. Benefit: No "magic" that breaks when requirements change.

### EXTI (External Interrupts)

```c
typedef struct {
    uint32_t trigger_mode;      // EXTI_TRIGGER_RISING, EXTI_TRIGGER_FALLING, EXTI_TRIGGER_BOTH
    uint32_t port;              // EXTI_PORT_A, EXTI_PORT_B, etc.
} EXTI_Config_t;

void EXTI_Init(uint32_t line, EXTI_Config_t config);
void EXTI_EnableIRQ(uint32_t line);
void EXTI_DisableIRQ(uint32_t line);
uint32_t EXTI_GetFlag(uint32_t line);
void EXTI_ClearFlag(uint32_t line);
```

**Design decision: Explicit flag clearing**

Early version auto-cleared flags:

```c
// OLD: Auto-clear (but what if you're in nested interrupt?)
void EXTI_IRQHandler(void) {
    handle_event();
    // Flag auto-cleared here — but maybe you needed to check it elsewhere
}
```

**Better:** Manual clearing. Forces you to think about when flags are valid.

```c
// NEW: Explicit clearing
void EXTI_IRQHandler(void) {
    if (EXTI_GetFlag(EXTI_LINE_0)) {
        handle_event();
        EXTI_ClearFlag(EXTI_LINE_0);  // Clear only after handling
    }
}
```

Prevents accidental missed interrupts if handler is interrupted.

## No Initialization File or Config Wizard

Unlike ST's CubeMX, this HAL has **no XML or generated code**. Why?

1. **Version control** — All code is human-written, reviewable, and versionable
2. **Debugging** — No hidden generated code that's hard to step through
3. **Learning** — You see exactly what initialization does

Tradeoff: More upfront typing, but complete transparency.

## Clock Configuration

Every application needs:

```c
// main.c
#include "rcc.h"

int main() {
    // Configure system clock (typically 24 MHz or 48 MHz from HSI)
    RCC_SetSystemClock(RCC_SYSCLK_HSI_48MHZ);
    
    // Enable peripherals you need
    RCC_EnablePeripheralClock(RCC_GPIOA);
    RCC_EnablePeripheralClock(RCC_UART1);
    
    // Then initialize your drivers
    GPIO_Init(GPIOA, PIN_0, GPIO_MODE_OUTPUT);
    USART_Init(USART1, USART_BAUD_115200);
    
    while (1) { ... }
}
```

**Why this pattern?**
- Centralized clock setup (prevents conflicts)
- Explicit dependency: "I'm using GPIOA, so I enable its clock"
- Easy to debug: Look at RCC_SetSystemClock() to understand clock tree

## Memory Model

All drivers use:
- **Stack-based configs** — GPIO_Config_t, SPI_Config_t are small structs on stack
- **No malloc/free** — No dynamic memory; deterministic behavior
- **Stateless drivers** — Drivers are just wrappers around hardware registers

This ensures:
- Predictable memory usage (no fragmentation)
- Easy debugging (no pointer chasing)
- Real-time safe (no allocator latency)

## Error Handling

Drivers return status codes:

```c
typedef enum {
    HAL_OK = 0,
    HAL_ERROR = 1,
    HAL_TIMEOUT = 2,
    HAL_INVALID_PARAM = 3
} HAL_Status_t;

HAL_Status_t I2C_MasterWrite(I2C_TypeDef *i2c, uint8_t addr, uint8_t *data, uint32_t len, uint32_t timeout_ms);
```

**No exceptions or callbacks**. Return codes force you to check results.

Example:
```c
if (I2C_MasterWrite(I2C1, 0x68, config, 2, 100) != HAL_OK) {
    // Handle error: timeout, NAK, etc.
}
```

## Testing & Validation Approach

Each driver was validated:

1. **Logic analyzer** — Capture actual waveforms (SPI, I2C, GPIO timing)
2. **Oscilloscope** — Measure voltage levels, verify timing
3. **Multimeter** — Verify GPIO output voltage, ADC accuracy
4. **GDB breakpoints** — Step through interrupt handlers, inspect register state

See `docs/TESTING.md` for specific test procedures and results.

## Performance Characteristics

- **Interrupt latency:** < 1 µs (M0 core, proper priority setup)
- **Code size:** ~1 KB per driver (when linked)
- **Runtime overhead:** Negligible; drivers compile to tight code with no function pointers

## Lessons Learned

### Mistake 1: Over-Abstraction
Early version had callback pointers for everything:

```c
typedef struct {
    void (*on_tx_complete)(void);
    void (*on_rx_complete)(uint8_t data);
} UART_Callbacks_t;
```

**Problem:** Function pointers add overhead and complexity. Most apps don't need them.

**Solution:** Simple interrupt handler + manual polling. User writes their own handler.

### Mistake 2: Hiding Clock Dependencies
Initially, GPIO_Init() auto-enabled its port clock.

**Problem:** Hidden magic. If two drivers clash on clock setup, hard to debug.

**Solution:** Explicit RCC_EnablePeripheralClock() calls. User controls clock state.

### Mistake 3: Prescaler Tables
Buried prescaler-to-frequency math inside drivers.

**Problem:** Unclear how baud rates are chosen. Debugging is harder.

**Solution:** Explicit SPI_PRESCALER_16, I2C_SPEED_FAST constants. No magic tables.

## Future Improvements

- [ ] DMA integration (currently basic)
- [ ] Watchdog (IWDG) driver
- [ ] Real-time clock (RTC) driver
- [ ] Low-power mode support (SLEEP, STANDBY)

---

**This design prioritizes transparency, modularity, and real-world validation over convenience. The result is code you can trust.**
