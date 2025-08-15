#include "fdcan_config.h"

// VARIAVEIS PARA O ENVIO
uint32_t CURRENT_CAN_ID = ACEL_CAN_ID;
FDCAN_TxHeaderTypeDef TxHeader; 
uint32_t TxMailbox; 

// VARIAVEIS PARA TESTAR A RECEPÇÃO
FDCAN_FilterTypeDef sFilterConfig; 
FDCAN_RxHeaderTypeDef RxHeader; 
uint8_t RxData[8];

// Functions --------------------------------------------------
HAL_StatusTypeDef   FDCAN_SendMessage(uint8_t *TxData) {
    TxHeader.Identifier = CURRENT_CAN_ID;
    HAL_StatusTypeDef status = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData); 
    if (status != HAL_OK) {
        LOG("Não foi possível enviar a mensagem FDCAN");
        uint32_t err = hfdcan1.ErrorCode;
        LOG("Erro FDCAN TX (handle): 0x%08lX", err);
        FDCAN_Restart();
    }
    return status;
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs){
    LOG("Ola");
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        LOG("Nova mensagem recebida no FDCAN RX FIFO 0");
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
            LOG("Falha ao ler mensagem RX");
            return;
        }
        FDCAN_Print_for_Reconstruction(RxHeader.Identifier, RxData);
    }
}

void FDCAN_Restart() {
    LOG("Reabrindo FDCAN");
    if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK) {
        LOG("Erro ao parar o FDCAN");
    }
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        LOG("Erro ao iniciar o FDCAN");
    }
}

void FDCAN_Add_Sensor_Data(uint8_t *TxData, uint8_t *data) {
    for (int i = 0; i < 6; i++){
        TxData[i] = data[i];
    }
}


void FDCAN_Change_TxID(uint32_t new_ID) {
    CURRENT_CAN_ID = new_ID;
}

void FDCAN_Print_for_Reconstruction(uint32_t id, int8_t* data) {
    printf("%lx,", id);
    size_t vecSize = 8;
    for (size_t i = 0; i < vecSize; i++){
        printf("%d", data[i]);
        if (i < vecSize - 1)
            putchar(',');
    }
    putchar('\n');
}