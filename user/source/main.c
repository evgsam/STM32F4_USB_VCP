#include <vcpCommand.h>
#include "main.h"
#include "ledIndication.h"


int main(void) {
	SystemInit();
	vPererheryInit();

	xTaskCreate(vTaskADCDataSend, "vTaskADCDataSend", 4500, NULL, configMAX_PRIORITIES, NULL);
	xTaskCreate(vTaskVCPRxCommandHandler, "vTaskVCPRxCommandHandler", 2000, NULL, configMAX_PRIORITIES - 2, NULL);
	xTaskCreate(vTaskVCPRxCommandParser, "vTaskVCPRxCommandParser", 1000, NULL, configMAX_PRIORITIES - 2, NULL);

	xTaskCreate(vTaskLEDToggle, "vTaskLEDToggle3", 100, (void*)LED3, 0, NULL);
	xTaskCreate(vTaskLEDToggle, "vTaskLEDToggle4", 100, (void*)LED4, 0, NULL);
	xTaskCreate(vTaskLEDToggle, "vTaskLEDToggle5", 100, (void*)LED5, 0, NULL);
	xTaskCreate(vTaskLEDToggle, "vTaskLEDToggle6", 100, (void*)LED6, 0, NULL);

	vTaskStartScheduler();
	while (1) {
	}
}
