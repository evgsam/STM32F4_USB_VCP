/*
 * global_variables.c
 *
 *  Created on: 8 нояб. 2022 г.
 *      Author: user
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "main.h"


#ifdef USE_12_BIT_ADC
uint16_t vADCConvertedArray_0[ui32RecBuffSize];
uint16_t vADCConvertedArray_1[ui32RecBuffSize];
#else
uint8_t vADCConvertedArray_0[ui32RecBuffSize];
uint8_t vADCConvertedArray_1[ui32RecBuffSize];

uint8_t vADCConvertedArray_3[ui32RecBuffSize];
uint8_t vADCConvertedArray_4[ui32RecBuffSize];

#endif

__IO uint32_t receive_count;
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

//*************************************************************************************************
//                      Хендлы FreeRTOS
//*************************************************************************************************
xQueueSetHandle xDMAData;
xQueueSetHandle xVCPRxDataQueue;  //Хендл очереди данных, принимаемых по VCP
xQueueSetHandle xLEDToggleQueue;  //Хендл очереди данных, принимаемых по VCP
xSemaphoreHandle xLED3ToggleMutex;
xSemaphoreHandle xLED4ToggleMutex;
xSemaphoreHandle xLED5ToggleMutex;
xSemaphoreHandle xLED6ToggleMutex;

xSemaphoreHandle xADCSendDataMutex;

