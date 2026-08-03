#ifndef SYSCONFIG_DRIVER_H
#define SYSCONFIG_DRIVER_H  
#include "STM32F030x4.h"
#include "stdint.h"

/**Sets the EXTI configuration for the specified line */

void SYSCONFIG_SetEXTIConfig(uint8_t EXTI_Line, uint8_t Exti_lineval);


#endif // SYSCONFIG_DRIVER_H