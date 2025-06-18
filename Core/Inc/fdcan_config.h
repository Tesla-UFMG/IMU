#ifndef __FDCAN_CONFIG_H
#define __FDCAN_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

// includes ------------------------------------------------------------------
#include "stm32u5xx.h"
#include "main.h"
#include "log.h"

// defines -------------------------------------------------------------------
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_FilterTypeDef sFilterConfig; // Filtro
extern FDCAN_RxHeaderTypeDef RxHeader; // Header do recebimento
extern FDCAN_TxHeaderTypeDef TxHeader; // Header do envio
extern uint8_t RxData[8]; // Dados recebidos
extern uint32_t TxMailbox; // Caixa de envio

// IDs
#define IMU_ID_CAN 0x001

// Filter Configurations
#define FDCAN_FILTER_ID1 0x000 // Esses são os bits a serem comparados
#define FDCAN_FILTER_ID2 0x7FF  // Essa aqui é a mascara

HAL_StatusTypeDef FDCAN_SendMessage(uint8_t *TxData);

void printReceivedMessage();

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);

void reabrirCan();

#ifdef __cplusplus
}
#endif
#endif /* __FDCAN__CONFIG */