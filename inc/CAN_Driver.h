#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include <stdint.h>

/*
 * STM32F030R8 has NO integrated CAN peripheral.
 *
 * This file intentionally provides a project-level CAN interface without
 * inventing CAN registers. A real CAN driver must be selected for an MCU
 * that contains CAN (for example an appropriate STM32F0/F1/F4 device).
 */

typedef enum {
    CAN_STATUS_OK = 0,
    CAN_STATUS_UNSUPPORTED = -1
} CAN_Status_t;

typedef struct {
    uint32_t bitrate;
    uint32_t mode;
} CAN_InitTypeDef;

CAN_Status_t CAN_Init(const CAN_InitTypeDef *config);
CAN_Status_t CAN_Send(uint32_t id, const uint8_t *data, uint8_t length);
CAN_Status_t CAN_Receive(uint32_t *id, uint8_t *data, uint8_t *length);

#endif
