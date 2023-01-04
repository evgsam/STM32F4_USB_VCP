/*
 *  vcpComand.c
 *
 *  Created on: 4 янв. 2023 г.
 *      Author: user
 */

#include "main.h"

extern xSemaphoreHandle xLED3ToggleMutex;
extern xSemaphoreHandle xLED4ToggleMutex;
extern xSemaphoreHandle xLED5ToggleMutex;
extern xSemaphoreHandle xLED6ToggleMutex;

extern xQueueSetHandle xVCPRxDataQueue;
extern xSemaphoreHandle xADCSendDataMutex;

void vTaskVCPRxCommandParser(void *pvParameters) {
	xVCPRxData pTaskVCPRxData;

#define ADC_SEND_DATA_START "11"
#define ADC_SEND_DATA_STOP "12"

#define LED3_ON "31"
#define LED3_OFF "32"
#define LED3_TOGGLE "33"
#define LED3_TOGGLE_OFF "34"

#define LED4_ON "41"
#define LED4_OFF "42"
#define LED4_TOGGLE "43"
#define LED4_TOGGLE_OFF "44"

#define LED5_ON "51"
#define LED5_OFF "52"
#define LED5_TOGGLE "53"
#define LED5_TOGGLE_OFF "54"

#define LED6_ON "61"
#define LED6_OFF "62"
#define LED6_TOGGLE "63"
#define LED6_TOGGLE_OFF "64"

	while (1) {
		if (xQueueReceive(xVCPRxDataQueue, &pTaskVCPRxData, portMAX_DELAY) == pdPASS) {
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, ADC_SEND_DATA_START) == 0) {
				xSemaphoreGive(xADCSendDataMutex);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, ADC_SEND_DATA_STOP) == 0) {
				xSemaphoreTake(xADCSendDataMutex, 100);
				STM_EVAL_LEDOff(LED4);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED3_ON) == 0) {
				STM_EVAL_LEDOn(LED3);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED4_ON) == 0) {
				STM_EVAL_LEDOn(LED4);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED5_ON) == 0) {
				STM_EVAL_LEDOn(LED5);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED6_ON) == 0) {
				STM_EVAL_LEDOn(LED6);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED3_OFF) == 0) {
				STM_EVAL_LEDOff(LED3);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED4_OFF) == 0) {
				STM_EVAL_LEDOff(LED4);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED5_OFF) == 0) {
				STM_EVAL_LEDOff(LED5);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED6_OFF) == 0) {
				STM_EVAL_LEDOff(LED6);
			}

			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED3_TOGGLE) == 0) {
				xSemaphoreGive(xLED3ToggleMutex);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED4_TOGGLE) == 0) {
				xSemaphoreGive(xLED4ToggleMutex);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED5_TOGGLE) == 0) {
				xSemaphoreGive(xLED5ToggleMutex);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED6_TOGGLE) == 0) {
				xSemaphoreGive(xLED6ToggleMutex);
			}

			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED3_TOGGLE_OFF) == 0) {
				xSemaphoreTake(xLED3ToggleMutex, 100);
				STM_EVAL_LEDOff(LED3);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED4_TOGGLE_OFF) == 0) {
				xSemaphoreTake(xLED4ToggleMutex, 100);
				STM_EVAL_LEDOff(LED4);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED5_TOGGLE_OFF) == 0) {
				xSemaphoreTake(xLED5ToggleMutex, 100);
				STM_EVAL_LEDOff(LED5);
			}
			if (strcmp(pTaskVCPRxData.ucVCPRxCommandBuf, LED6_TOGGLE_OFF) == 0) {
				xSemaphoreTake(xLED6ToggleMutex, 100);
				STM_EVAL_LEDOff(LED6);
			}

		}
	}
}
void vTaskVCPRxCommandHandler(void *pvParameters) {
	xVCPRxData pTaskVCPRxData;
	uint8_t ui8RxBuffer[sizeof(pTaskVCPRxData.ucVCPRxCommandBuf)];
	uint8_t ui8RxBufferIndex = 0;
	bool boolStartFlag = false;

	pTaskVCPRxData.ui8VCPRxCommandBuSize = 0;
	memset(&pTaskVCPRxData.ucVCPRxCommandBuf[0], 0, sizeof(pTaskVCPRxData.ucVCPRxCommandBuf));

	while (1) {
		VCP_ReceiveData(&USB_OTG_dev, ui8RxBuffer, sizeof(ui8RxBuffer), CDC_OUT_EP3);
		for (ui8RxBufferIndex = 0; ui8RxBufferIndex < sizeof(ui8RxBuffer); ui8RxBufferIndex++) {
			if (ui8RxBuffer[ui8RxBufferIndex] == '>') {
				boolStartFlag = true;
				ui8RxBufferIndex++;
			}
			if (boolStartFlag) {
				if ((ui8RxBuffer[ui8RxBufferIndex] != 0x0d) && (ui8RxBuffer[ui8RxBufferIndex] != 0x0A)
						&& (ui8RxBuffer[ui8RxBufferIndex] != '<')) {
					if (ui8RxBuffer[ui8RxBufferIndex] != '>') {
						pTaskVCPRxData.ucVCPRxCommandBuf[pTaskVCPRxData.ui8VCPRxCommandBuSize++] = ui8RxBuffer[ui8RxBufferIndex];
					}
				} else {
					boolStartFlag = false;
					pTaskVCPRxData.ucVCPRxCommandBuf[pTaskVCPRxData.ui8VCPRxCommandBuSize] = 0;
					xQueueSend(xVCPRxDataQueue, &pTaskVCPRxData, 100);
					memset(ui8RxBuffer, 0, sizeof(ui8RxBuffer));
					memset(&pTaskVCPRxData.ucVCPRxCommandBuf[0], 0, sizeof(pTaskVCPRxData.ucVCPRxCommandBuf));
					pTaskVCPRxData.ui8VCPRxCommandBuSize = 0;

				}
			}
		}

		vTaskDelay(100 / portTICK_RATE_MS);
	}
	vTaskDelete(NULL);
}
