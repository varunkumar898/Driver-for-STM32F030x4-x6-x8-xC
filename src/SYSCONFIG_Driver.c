#include "SYSCONFIG_Driver.h"

void SYSCONFIG_SetEXTIConfig(uint8_t EXTI_Line, uint8_t Exti_lineval)
{
	uint32_t register_index;
	uint32_t bit_position;

	if (EXTI_Line > 15U || Exti_lineval > 15U) {
		return;
	}

	RCC->APB2ENR |= (1U << 0U);

	register_index = EXTI_Line / 4U;
	bit_position = (EXTI_Line % 4U) * 4U;
	SYSCFG->EXTICR[register_index] &= ~(0xFU << bit_position);
	SYSCFG->EXTICR[register_index] |= ((uint32_t)Exti_lineval << bit_position);
}
