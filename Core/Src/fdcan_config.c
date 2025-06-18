#include "fdcan_config.h"

FDCAN_FilterTypeDef sFilterConfig; // Filtro
FDCAN_RxHeaderTypeDef RxHeader; // Header do recebimento
FDCAN_TxHeaderTypeDef TxHeader; // Header do envio
uint8_t RxData[8]; // Dados recebidos
uint32_t TxMailbox; // Caixa de envio

// Functions --------------------------------------------------
HAL_StatusTypeDef FDCAN_SendMessage(uint8_t *TxData) {
    HAL_StatusTypeDef status = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &TxHeader, TxData); 
    if (status != HAL_OK) {
        LOG("Não foi possível enviar a mensagem FDCAN");
        uint32_t err = hfdcan1.ErrorCode;
        LOG("Erro FDCAN TX (handle): 0x%08lX", err);
        reabrirCan(); // Isso aqui é a gambiarra da gambiarra kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
    }
    return status;
}

void printReceivedMessage() {
    printf("Mensagem recebida FDCAN:\n");
    printf("ID: 0x%03lX - ", RxHeader.Identifier);
    printf("%s - ", (RxHeader.IdType == FDCAN_STANDARD_ID) ? "FDCAN_STANDARD_ID" : "FDCAN_EXTENDED_ID");
    printf("%s\n", (RxHeader.RxFrameType == FDCAN_DATA_FRAME) ? "FDCAN_DATA_FRAME" : "FDCAN_REMOTE_FRAME");

    printf("Dados: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", RxData[i]);
    }
    printf("\n");
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs){
    LOG("Ola");
    if ((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET) {
        LOG("Nova mensagem recebida no FDCAN RX FIFO 0");
        if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
            LOG("Falha ao ler mensagem RX");
            return;
        }
        printReceivedMessage();
    }
}

void reabrirCan() {
    LOG("Reabrindo FDCAN");
    if (HAL_FDCAN_Stop(&hfdcan1) != HAL_OK) {
        LOG("Erro ao parar o FDCAN");
    }
    
    if (HAL_FDCAN_Start(&hfdcan1) != HAL_OK) {
        LOG("Erro ao iniciar o FDCAN");
    }
    
    LOG("FDCAN reaberto com sucesso");
}