[#ftl]
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.h
  * Description        : FreeRTOS applicative header file
  ******************************************************************************
[@common.optinclude name=mxTmpFolder+"/license.tmp"/][#--include License text --]
  ******************************************************************************
  */
/* USER CODE END Header */

[#compress]
[#if cpucore!="" && (contextFolder=="" || contextFolder=="/")]
[#assign contextFolder = cpucore?replace("ARM_CORTEX_","C")?replace("+","PLUS")+"/"]
[/#if]
[#assign inMain = 0]
[#assign useNewHandle = 0]
[#assign useTimers = 0]
[#assign hookUsed = 0]

[#list SWIPdatas as SWIP]
  [#if SWIP.variables??]
    [#list SWIP.variables as variable]
      [#if variable.name=="HALCompliant"]
        [#assign inMain = 1]
      [/#if]
    [/#list]
  [/#if]
[/#list]

[#list SWIPdatas as SWIP]
  [#if SWIP.defines??]
    [#list SWIP.defines as definition]
      [#if definition.name=="configENABLE_BACKWARD_COMPATIBILITY"]
        [#if definition.value=="0"]
          [#assign useNewHandle = 1]
        [/#if]
      [/#if]
      [#if definition.name=="configUSE_TIMERS"]
        [#if definition.value=="1"]
          [#assign useTimers = 1]
        [/#if]
      [/#if]
    [/#list]
  [/#if]
[/#list]
[/#compress]

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_FREERTOS_H
#define __APP_FREERTOS_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "${main_h}" [#-- for user defines --]
[#if inMain == 0]
[@common.optinclude name=contextFolder+mxTmpFolder+"/rtos_inc.tmp"/][#--include freertos includes --]
[/#if]
#n
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Exported macro -------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */
[#compress]
  [#if RTOSdatas??]
    [#assign RTOS = RTOSdatas[0]]

    [#list RTOS.tasks as task]
      extern osThreadId_t ${task.name}Handle;
    [/#list]

    [#list RTOS.mutexes as mutex]
      extern osMutexId_t ${mutex.name}Handle;
    [/#list]

    [#list RTOS.recursiveMutexes as mutex]
      extern osMutexId_t ${mutex.name}Handle;
    [/#list]

    [#list RTOS.timers as timer]
      extern osTimerId_t ${timer.name}Handle;
    [/#list]

    [#list RTOS.queues as queue]
      extern osMessageQueueId_t ${queue.name}Handle;
    [/#list]

    [#list RTOS.countingSems as sem]
      extern osSemaphoreId_t ${sem.name}Handle;
    [/#list]

    [#list RTOS.binarySems as sem]
      extern osSemaphoreId_t ${sem.name}Handle;
    [/#list]

    [#list RTOS.events as event]
      extern osEventFlagsId_t ${event.name}Handle;
    [/#list]
  [/#if]
[/#compress]
#n
/* Exported function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */
[#compress]
#n
[#if inMain == 0]
[@common.optinclude name=contextFolder+mxTmpFolder+"/rtos_pfp.tmp"/]
#n
void MX_FREERTOS_Init(void);  /* (MISRA C 2004 rule 8.1) */
#n
[/#if]

[#list SWIPdatas as SWIP]
  [#if SWIP.defines??]
    [#list SWIP.defines as definition]
      [#if definition.name=="configGENERATE_RUN_TIME_STATS"]
        [#if definition.value=="1"]
          [#assign hookUsed = 1]
        [/#if]
      [/#if]
      [#if definition.name=="configUSE_IDLE_HOOK"]
        [#if definition.value=="1"]
          [#assign hookUsed = 1]
        [/#if]
      [/#if]
      [#if definition.name=="configUSE_TICK_HOOK"]
        [#if definition.value=="1"]
          [#assign hookUsed = 1]
        [/#if]
      [/#if]
      [#if definition.name=="configUSE_DAEMON_TASK_STARTUP_HOOK"]
        [#if definition.value=="1"]
          [#assign hookUsed = 1]
        [/#if]
      [/#if]
        [#if definition.name=="configCHECK_FOR_STACK_OVERFLOW"]
          [#if definition.value !="0"]
            [#assign hookUsed = 1]
          [/#if]
        [/#if]
        [#if definition.name=="configUSE_MALLOC_FAILED_HOOK"]
          [#if definition.value=="1"]
            [#assign hookUsed = 1]
          [/#if]
        [/#if]
     [/#list]
 [/#if]
[/#list]

[#if hookUsed==1]
#n/* Hook prototypes */
  [#list SWIPdatas as SWIP]
    [#if SWIP.defines??]
      [#list SWIP.defines as definition]
        [#if definition.name=="configGENERATE_RUN_TIME_STATS"]
          [#if definition.value=="1"]
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
          [/#if]
        [/#if]
        [#if definition.name=="configUSE_IDLE_HOOK"]
          [#if definition.value=="1"]
void vApplicationIdleHook(void);
          [/#if]
        [/#if]
        [#if definition.name=="configUSE_TICK_HOOK"]
          [#if definition.value=="1"]
void vApplicationTickHook(void);
          [/#if]
        [/#if]
        [#if definition.name=="configUSE_DAEMON_TASK_STARTUP_HOOK"]
          [#if definition.value=="1"]
void vApplicationDaemonTaskStartupHook(void);
          [/#if]
        [/#if]
        [#if definition.name=="configCHECK_FOR_STACK_OVERFLOW"]
          [#if definition.value !="0"]
            [#if useNewHandle==0]
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName);
            [#else]
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
            [/#if]
          [/#if]
        [/#if]
        [#if definition.name=="configUSE_MALLOC_FAILED_HOOK"]
          [#if definition.value=="1"]
void vApplicationMallocFailedHook(void);
          [/#if]
        [/#if]
      [/#list]
    [/#if]
  [/#list]
[/#if]
[/#compress]

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

#ifdef __cplusplus
}
#endif
#endif /* __APP_FREERTOS_H */
