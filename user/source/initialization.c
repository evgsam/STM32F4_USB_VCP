/*
 * initialization.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>

void delay(uint32_t ui32ms) {
  uint32_t ui32start = ui32ticksDelay;
  while((ui32ticksDelay - ui32start) < ui32ms);
}


void initialization(void) {
#ifdef DEBUG_MODE
	STM32f4_Discovery_Debug_Init();
#endif
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	volatile uint32_t ticks_delay = 0;
	SysTick_Config((SystemCoreClock / 1000)-1); //частота systick
}
