/*
 * handlers.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>

void SysTick_Handler(void) {
	ui32ticksDelay++;
}
