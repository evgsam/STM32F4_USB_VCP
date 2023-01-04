/*
 * ledIndication.c
 *
 *  Created on: 4 янв. 2023 г.
 *      Author: user
 */
#include "main.h"

extern xSemaphoreHandle xLED3ToggleMutex;
extern xSemaphoreHandle xLED4ToggleMutex;
extern xSemaphoreHandle xLED5ToggleMutex;
extern xSemaphoreHandle xLED6ToggleMutex;

void vTaskLEDToggle(void *pvParameters) {
	uint8_t ui8LEDNumber;
	ui8LEDNumber = (uint8_t) pvParameters;
	while (1) {
		switch (ui8LEDNumber) {
		case LED3:
			if (xSemaphoreTake(xLED3ToggleMutex, portMAX_DELAY) == pdTRUE) {
				STM_EVAL_LEDToggle(LED3);
				xSemaphoreGive(xLED3ToggleMutex);
			}
			break;
		case LED4:
			if (xSemaphoreTake(xLED4ToggleMutex, portMAX_DELAY) == pdTRUE) {
				STM_EVAL_LEDToggle(LED4);
				xSemaphoreGive(xLED4ToggleMutex);
			}
			break;
		case LED5:
			if (xSemaphoreTake(xLED5ToggleMutex, portMAX_DELAY) == pdTRUE) {
				STM_EVAL_LEDToggle(LED5);
				xSemaphoreGive(xLED5ToggleMutex);
			}
			break;
		case LED6:
			if (xSemaphoreTake(xLED6ToggleMutex, portMAX_DELAY) == pdTRUE) {
				STM_EVAL_LEDToggle(LED6);
				xSemaphoreGive(xLED6ToggleMutex);
			}
			break;
		}
		vTaskDelay(500 / portTICK_RATE_MS);
	}
}
