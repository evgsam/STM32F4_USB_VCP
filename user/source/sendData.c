/*
 * sendData.c
 *
 *  Created on: 15 сент. 2020 г.
 *      Author: evgsam
 */

#include <main.h>

extern xQueueSetHandle xDMAData;
extern xSemaphoreHandle xADCSendDataMutex;

void vTaskADCDataSend(void *pvParameters) {
	uint16_t* ui16RecBufferPoint;

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
#ifdef USE_12_BIT_ADC
				memcpy(vVCPSendBuffer, ui16RecBufferPoint, sizeof(vVCPSendBuffer));
#else
				memcpy(vVCPSendBuffer, ui16RecBufferPoint, ui32RecBuffSize);
#endif

				VCP_SendData(&USB_OTG_dev, vVCPSendBuffer, ui32RecBuffSize, CDC_IN_EP);
				xSemaphoreGive(xADCSendDataMutex);
			}
		}
	}
	vTaskDelete(NULL);
}
