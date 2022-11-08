/*
 * handlers.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>
extern uint8_t vADCConvertedArray_0[ui32RecBuffSize];
extern uint8_t vADCConvertedArray_1[ui32RecBuffSize];

extern xQueueSetHandle xDMAData;

void DMA2_Stream3_IRQHandler(void) {
	uint16_t* ui16RecBufferPoint;
	if (DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3)) {
		DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
		if (DMA_GetCurrentMemoryTarget(DMA2_Stream3) == 0) {
			ui16RecBufferPoint = vADCConvertedArray_1;
		} else {
			ui16RecBufferPoint = vADCConvertedArray_0;
		}
		xQueueSendToBackFromISR(xDMAData, &ui16RecBufferPoint, 0);
	}
}

