/*
 * main.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>

int main(void) {
	SystemInit();
	initialization();
#ifdef DEBUG_MODE
	xprintf(" hello! \n");
#endif

	while (1) {
		STM_EVAL_LEDToggle(LED3);
		delay(800);
		STM_EVAL_LEDToggle(LED5);
		delay(300);
		STM_EVAL_LEDToggle(LED6);
		delay(200);
		STM_EVAL_LEDToggle(LED4);
		delay(100);
	}
}
