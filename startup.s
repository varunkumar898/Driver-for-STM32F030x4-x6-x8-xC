/*
 * startup.s - STM32F030R8 / STM32F030x8 GCC startup
 *
 * Vector layout follows ST's STM32F030x8 startup template.
 */

.syntax unified
.cpu cortex-m0
.thumb

.global g_pfnVectors
.global Default_Handler
.global Reset_Handler

.extern main

.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word 0
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler

    .word WWDG_IRQHandler
    .word 0
    .word RTC_IRQHandler
    .word FLASH_IRQHandler
    .word RCC_IRQHandler
    .word EXTI0_1_IRQHandler
    .word EXTI2_3_IRQHandler
    .word EXTI4_15_IRQHandler
    .word 0
    .word DMA1_Channel1_IRQHandler
    .word DMA1_Channel2_3_IRQHandler
    .word DMA1_Channel4_5_IRQHandler
    .word ADC1_IRQHandler
    .word TIM1_BRK_UP_TRG_COM_IRQHandler
    .word TIM1_CC_IRQHandler
    .word 0
    .word TIM3_IRQHandler
    .word TIM6_IRQHandler
    .word 0
    .word TIM14_IRQHandler
    .word TIM15_IRQHandler
    .word TIM16_IRQHandler
    .word TIM17_IRQHandler
    .word I2C1_IRQHandler
    .word I2C2_IRQHandler
    .word SPI1_IRQHandler
    .word SPI2_IRQHandler
    .word USART1_IRQHandler
    .word USART2_IRQHandler

.size g_pfnVectors, .-g_pfnVectors

.section .text.Reset_Handler
.thumb_func
Reset_Handler:
    ldr r0, =_estack
    mov sp, r0

    /* Copy .data from Flash to SRAM */
    ldr r0, =_sdata
    ldr r1, =_edata
    ldr r2, =_sidata
    movs r3, #0
1:
    adds r4, r0, r3
    cmp r4, r1
    bcc 2f
    b 3f
2:
    ldr r4, [r2, r3]
    str r4, [r0, r3]
    adds r3, r3, #4
    b 1b

    /* Zero .bss */
3:
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
4:
    cmp r0, r1
    bcc 5f
    b 6f
5:
    str r2, [r0]
    adds r0, r0, #4
    b 4b

6:
    bl main

7:
    b 7b

.section .text.Default_Handler,"ax",%progbits
.thumb_func
Default_Handler:
    b Default_Handler

.macro WEAK_DEFAULT handler
.weak \handler
.set \handler, Default_Handler
.endm

WEAK_DEFAULT NMI_Handler
WEAK_DEFAULT HardFault_Handler
WEAK_DEFAULT SVC_Handler
WEAK_DEFAULT PendSV_Handler
WEAK_DEFAULT SysTick_Handler
WEAK_DEFAULT WWDG_IRQHandler
WEAK_DEFAULT RTC_IRQHandler
WEAK_DEFAULT FLASH_IRQHandler
WEAK_DEFAULT RCC_IRQHandler
WEAK_DEFAULT EXTI0_1_IRQHandler
WEAK_DEFAULT EXTI2_3_IRQHandler
/* EXTI4_15_IRQHandler is implemented in main.c */
WEAK_DEFAULT DMA1_Channel1_IRQHandler
WEAK_DEFAULT DMA1_Channel2_3_IRQHandler
WEAK_DEFAULT DMA1_Channel4_5_IRQHandler
WEAK_DEFAULT ADC1_IRQHandler
WEAK_DEFAULT TIM1_BRK_UP_TRG_COM_IRQHandler
WEAK_DEFAULT TIM1_CC_IRQHandler
WEAK_DEFAULT TIM3_IRQHandler
WEAK_DEFAULT TIM6_IRQHandler
WEAK_DEFAULT TIM14_IRQHandler
WEAK_DEFAULT TIM15_IRQHandler
WEAK_DEFAULT TIM16_IRQHandler
WEAK_DEFAULT TIM17_IRQHandler
WEAK_DEFAULT I2C1_IRQHandler
WEAK_DEFAULT I2C2_IRQHandler
WEAK_DEFAULT SPI1_IRQHandler
WEAK_DEFAULT SPI2_IRQHandler
WEAK_DEFAULT USART1_IRQHandler
WEAK_DEFAULT USART2_IRQHandler
