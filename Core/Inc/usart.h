/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */
#define PRINT_LOG_MESSAGES false

#define LOG(fmt, ...) \
if (PRINT_LOG_MESSAGES) \
    printf(fmt "\n", ##__VA_ARGS__)
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void __io_putchar(int ch);
void PRINT_for_Reconstruction_u8_bits(uint32_t id, uint8_t* data);
void PRINT_for_Reconstruction_16_bits(uint32_t id, int16_t* data);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

