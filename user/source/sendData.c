/*
 * sendData.c
 *
 *  Created on: 15 сент. 2020 г.
 *      Author: evgsam
 */

#include <main.h>
#include "usbd_cdc_vcp.h"

extern xQueueSetHandle xDMAData;
extern xSemaphoreHandle xADCSendDataMutex;

void vTaskServiceDataSend(void *pvParameters) {
	uint16_t ui16ServiceData;

#ifdef USE_12_BIT_ADC
	uint16_t vVCPSendBuffer[ui32RecBuffSize];
#else
	uint8_t vVCPSendBuffer[ui8ServiceBuffSize];
#endif
	while (1) {
		if (xQueueReceive(xServiceData, &ui16ServiceData, portMAX_DELAY) == pdPASS) {
				STM_EVAL_LEDToggle(LED6);
				//memset(vVCPSendBuffer, 0, sizeof(vVCPSendBuffer));
				//memcpy(vVCPSendBuffer, ui16ServiceData, sizeof(vVCPSendBuffer));
				VCP_SendData(&USB_OTG_dev, "hello", sizeof("hello"), CDC_IN_EP3);
		}
	}
	vTaskDelete(NULL);
}


void vTaskADCDataSend(void *pvParameters) {
	uint16_t *ui16RecBufferPoint;

#ifdef USE_12_BIT_ADC
	uint16_t vVCPSendBuffer[ui32RecBuffSize];
#else
	uint8_t vVCPSendBuffer[ui32RecBuffSize];
#endif
	while (1) {
		if (xQueueReceive(xDMAData, &ui16RecBufferPoint, portMAX_DELAY) == pdPASS) {
			if (xSemaphoreTake(xADCSendDataMutex, portMAX_DELAY) == pdTRUE) {
				STM_EVAL_LEDToggle(LED4);
				memset(vVCPSendBuffer, 0, sizeof(vVCPSendBuffer));
				memcpy(vVCPSendBuffer, ui16RecBufferPoint, sizeof(vVCPSendBuffer));
				VCP_SendData(&USB_OTG_dev, vVCPSendBuffer, ui32RecBuffSize, CDC_IN_EP);
				xSemaphoreGive(xADCSendDataMutex);
			}
		}
	}
	vTaskDelete(NULL);
}
