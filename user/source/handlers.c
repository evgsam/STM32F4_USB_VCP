/*
 * handlers.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>



void EXTI0_IRQHandler(void) {
	EXTI_ClearITPendingBit(EXTI_Line0);


#ifdef DEBUG_MODE
	xprintf("EXTI_Line0 event \n");
#endif
	STM_EVAL_LEDToggle(LED4);
	//sendHello("hello \n", sizeof("hello \n"));
}

void DMA2_Stream3_IRQHandler(void) {
	if (DMA_GetCurrentMemoryTarget(DMA2_Stream3) == 0) {
		sendHello(ui8ADCConvertedArray_0,ui32RecBuffSize);
		STM_EVAL_LEDToggle(LED3);
	} else {
		sendHello(ui8ADCConvertedArray_1,ui32RecBuffSize);
		STM_EVAL_LEDToggle(LED6);
	}
	DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
}
