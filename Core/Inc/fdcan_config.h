#ifndef __FDCAN_CONFIG_H
#define __FDCAN_CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif

// INCLUDES ------------------------------------------------------------------
#include "stm32u5xx.h"
#include "main.h"
#include "log.h"

// DEFINES -------------------------------------------------------------------
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_TxHeaderTypeDef TxHeader; // Header do envio
extern uint32_t TxMailbox; // Caixa de envio

// IDs -----------------------------------------------------------------------
#define ACEL_CAN_ID 0x103
#define GYRO_CAN_ID 0x104
extern uint32_t CURRENT_CAN_ID;

// ISSO DAQUI É SÓ PRA TESTAR RECEPÇÃO RECURSIVA -----------------------------
#define FDCAN_FILTER_ID1 0x000 
#define FDCAN_FILTER_ID2 0x7FF  
extern FDCAN_FilterTypeDef sFilterConfig; 
extern uint8_t RxData[8]; 
extern FDCAN_RxHeaderTypeDef RxHeader; 

// SENDING
void FDCAN_Change_TxID(uint32_t new_ID);
HAL_StatusTypeDef FDCAN_SendMessage(uint8_t *TxData);
void FDCAN_Add_Sensor_Data(uint8_t *TxData, uint8_t *data);

// RESTART CAN
void FDCAN_Restart();

// RECEPÇÃO
void FDCAN_Print_RxMessage();
void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs);



#ifdef __cplusplus
}
#endif
#endif /* __FDCAN__CONFIG */