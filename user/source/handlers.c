/*
 * handlers.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>



void EXTI0_IRQHandler(void) {
	EXTI_ClearITPendingBit(EXTI_Line0);


#ifdef DEBUG
	xprintf("EXTI_Line0 event \n");
#endif
	STM_EVAL_LEDToggle(LED4);
	sendHello();
}
