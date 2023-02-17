/*
 * queueAndSemaphore.c
 *
 *  Created on: 4 янв. 2023 г.
 *      Author: user
 */
#include "queueAndSemaphore.h"

extern xSemaphoreHandle xLED3ToggleMutex;
extern xSemaphoreHandle xLED4ToggleMutex;
extern xSemaphoreHandle xLED5ToggleMutex;
extern xSemaphoreHandle xLED6ToggleMutex;
extern xQueueSetHandle xADCData;
extern xQueueSetHandle xServiceData;
extern xQueueSetHandle xVCPRxDataQueue;

extern xSemaphoreHandle xADCSendDataMutex;

//****************************************************************************/
//		FreeRTOS semaphore creator
//****************************************************************************/
void vQueueSemaphoreCreated(void) {
	xADCData = xQueueCreate(2, 4);
	xServiceData = xQueueCreate(2, 4);
	xVCPRxDataQueue = xQueueCreate(10, sizeof(xVCPRxData));

	xADCSendDataMutex = xSemaphoreCreateMutex();
	xSemaphoreTake(xADCSendDataMutex, portMAX_DELAY);

	xLED3ToggleMutex = xSemaphoreCreateMutex();
	xLED4ToggleMutex = xSemaphoreCreateMutex();
	xLED5ToggleMutex = xSemaphoreCreateMutex();
	xLED6ToggleMutex = xSemaphoreCreateMutex();
	xSemaphoreTake(xLED3ToggleMutex, portMAX_DELAY);
	xSemaphoreTake(xLED4ToggleMutex, portMAX_DELAY);
	xSemaphoreTake(xLED5ToggleMutex, portMAX_DELAY);
	xSemaphoreTake(xLED6ToggleMutex, portMAX_DELAY);
}

