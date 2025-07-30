/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_freertos.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
  uint8_t TxData[8] = {0};

  uint8_t acel_8[8];
  int16_t acel_16[8];

  uint8_t gyro_8[8];
  int16_t gyro_16[8];

  uint8_t temp_8[8];
  int16_t temp_16[8];

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for readSensors */
osThreadId_t readSensorsHandle;
const osThreadAttr_t readSensors_attributes = {
  .name = "readSensors",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for sendToCAN */
osThreadId_t sendToCANHandle;
const osThreadAttr_t sendToCAN_attributes = {
  .name = "sendToCAN",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 128 * 4
};
/* Definitions for newSensorDataAvailable */
osSemaphoreId_t newSensorDataAvailableHandle;
const osSemaphoreAttr_t newSensorDataAvailable_attributes = {
  .name = "newSensorDataAvailable"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */
  /* creation of newSensorDataAvailable */
  newSensorDataAvailableHandle = osSemaphoreNew(1, 0, &newSensorDataAvailable_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of readSensors */
  readSensorsHandle = osThreadNew(StartReadSensors, NULL, &readSensors_attributes);

  /* creation of sendToCAN */
  sendToCANHandle = osThreadNew(StartSendToCAN, NULL, &sendToCAN_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */
  LOG("Entrando no loop principal");
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_StartReadSensors */
/**
* @brief Function implementing the readSensors thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartReadSensors */
void StartReadSensors(void *argument)
{
  /* USER CODE BEGIN readSensors */
  /* Infinite loop */
  for(;;) {
    SENSORS_Read_Accelerometer_8(acel_8);
    SENSORS_8_to_16bits(acel_8, acel_16);

    SENSORS_Read_Gyroscope_8(gyro_8);
    SENSORS_8_to_16bits(gyro_8, gyro_16);

    //SENSORS_Read_Gyroscope_8(temp_8);
    //SENSORS_8_to_16bits(temp_8, temp_16);

    SENSORS_Print_for_Reconstruction(ACEL_CAN_ID, acel_16);
    SENSORS_Print_for_Reconstruction(GYRO_CAN_ID, gyro_16);
    //SENSORS_Print_for_Reconstruction(TEMP_CAN_ID, temp_16);

    // Libera o semáforo
    osSemaphoreRelease(newSensorDataAvailableHandle);

    osDelay(10);
  }
  /* USER CODE END readSensors */
}

/* USER CODE BEGIN Header_StartSendToCAN */
/**
* @brief Function implementing the sendToCAN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendToCAN */
void StartSendToCAN(void *argument)
{
  /* USER CODE BEGIN sendToCAN */
  HAL_StatusTypeDef CAN_status = HAL_ERROR;
  /* Infinite loop */
  for(;;){
    // Espera até um novo dado chegar
    osSemaphoreAcquire(newSensorDataAvailableHandle, osWaitForever);
    while (HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) != SET);

    // Envia aceleração
    FDCAN_Change_TxID(ACEL_CAN_ID);
    FDCAN_Add_Sensor_Data(TxData, acel_8);
    CAN_status = FDCAN_SendMessage(TxData); // HAL_OK or HAL_ERROR
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, !CAN_status); // CAN ESTA FUNCIONANDO

    // Envia giroscpio
    FDCAN_Change_TxID(GYRO_CAN_ID);
    FDCAN_Add_Sensor_Data(TxData, gyro_8);
    CAN_status = FDCAN_SendMessage(TxData); // HAL_OK or HAL_ERROR
    HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, !CAN_status); // CAN ESTA FUNCIONANDO

    // Envia temperatura
    // FDCAN_Change_TxID(TEMP_CAN_ID);
    // FDCAN_Add_Sensor_Data(TxData, temp_8);
    // CAN_status = FDCAN_SendMessage(TxData); // HAL_OK or HAL_ERROR
    // HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, !CAN_status); // CAN ESTA FUNCIONANDO
    

    osDelay(20);
  }
  /* USER CODE END sendToCAN */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

