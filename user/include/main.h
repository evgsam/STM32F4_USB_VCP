/*
 * main.h
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#ifndef MAIN_H_
#define MAIN_H_

#pragma once

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stm32f4xx.h>

#include <stm32f4_discovery.h>
#include <stm32f4_discovery_debug.h>

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_adc.h>

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_core_loopback.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "FreeRTOSConfig.h"
#include "timers.h"

#include "global_variables.h"

#define ui8ChanalSum 1
#define ui16RecFreq 16000
#define ui32RecBuffSize (ui16RecFreq/10)*ui8ChanalSum

extern __ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

typedef struct {
	unsigned char ucVCPRxCommandBuf[30];
	uint8_t ui8VCPRxCommandBuSize;
} xVCPRxData;

typedef struct {
	uint8_t ui8LedToggleNumber;
} xLEDToggle;

void vTaskADCDataSend(void *pvParameters);

//*************************************************************************************************
//                      Хендлы FreeRTOS
//*************************************************************************************************
extern xQueueSetHandle xDMAData;
extern xQueueSetHandle xVCPRxDataQueue;  //Хендл очереди данных, принимаемых по VCP
extern xQueueSetHandle xLEDToggleQueue;  //Хендл очереди данных, принимаемых по VCP
extern xSemaphoreHandle xLED3ToggleMutex;
extern xSemaphoreHandle xLED4ToggleMutex;
extern xSemaphoreHandle xLED5ToggleMutex;
extern xSemaphoreHandle xLED6ToggleMutex;

extern xSemaphoreHandle xADCSendDataMutex;

#endif /* USER_INCLUDE_MAIN_H_ */
