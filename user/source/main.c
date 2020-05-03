/*
 * main.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>

void delay(uint32_t milliseconds) {
  uint32_t start = ticks_delay;
  while((ticks_delay - start) < milliseconds);
}

int main(void) {
	SystemInit();

	volatile uint32_t ticks_delay = 0;

	STM32f4_Discovery_Debug_Init();
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	SysTick_Config((SystemCoreClock / 1000)-1); //168МГц

	STM32f4_Discovery_Debug_Init();

	while (1) {
		STM_EVAL_LEDToggle(LED3);
		delay(100);
		STM_EVAL_LEDToggle(LED5);
		delay(100);
		STM_EVAL_LEDToggle(LED6);
		delay(100);
		STM_EVAL_LEDToggle(LED4);
		delay(100);
	}
}
