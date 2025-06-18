#ifndef __USART_CONFIG_H
#define __USART_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// Includes ------------------------------------------------------------------
#include "stm32u5xx.h"
#include "main.h"
#include <stdio.h>

// Exported types ------------------------------------------------------------
extern UART_HandleTypeDef huart1;

// Functions --------------------------------------------------
void __io_putchar(int ch);

#ifdef __cplusplus
}
#endif

#endif /* __USART_CONFIG_H */