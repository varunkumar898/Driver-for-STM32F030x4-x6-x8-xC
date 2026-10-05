#include "CAN_Driver.h"

CAN_Status_t CAN_Init(const CAN_InitTypeDef *config)
{
    (void)config;
    return CAN_STATUS_UNSUPPORTED;
}

CAN_Status_t CAN_Send(uint32_t id, const uint8_t *data, uint8_t length)
{
    (void)id; (void)data; (void)length;
    return CAN_STATUS_UNSUPPORTED;
}

CAN_Status_t CAN_Receive(uint32_t *id, uint8_t *data, uint8_t *length)
{
    (void)id; (void)data; (void)length;
    return CAN_STATUS_UNSUPPORTED;
}
