#ifndef __LOG_H
#define __LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usart_config.h"

#define PRINT_LOG_MESSAGES false

#define LOG(fmt, ...) \
if (PRINT_LOG_MESSAGES) \
    printf(fmt "\n", ##__VA_ARGS__)


#ifdef __cplusplus
}
#endif

#endif