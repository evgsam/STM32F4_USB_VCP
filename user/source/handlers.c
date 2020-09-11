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
	//sendHello("hello \n", sizeof("hello \n"));
}

void DMA2_Stream3_IRQHandler(void) {
	if (DMA_GetCurrentMemoryTarget(DMA2_Stream3) == 0) {
		memcpy(ui8SPITransmittedArray, ui8ADCConvertedArray_0, ui32RecBuffSize);
		sendHello(ui8ADCConvertedArray_0,ui32RecBuffSize);
	} else {
		memcpy(ui8SPITransmittedArray, ui8ADCConvertedArray_1, ui32RecBuffSize);
		sendHello(ui8ADCConvertedArray_1,ui32RecBuffSize);
	}
	DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
}
