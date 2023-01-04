/*
 * handlers.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>
extern uint8_t vADCConvertedArray_0[ui32RecBuffSize];
extern uint8_t vADCConvertedArray_1[ui32RecBuffSize];

//extern uint8_t vADCConvertedArray_3[ui32RecBuffSize];
//extern uint8_t vADCConvertedArray_4[ui32RecBuffSize];

extern xQueueSetHandle xDMAData;

/*void vTest(void){
	for (uint16_t i=0;i<ui32RecBuffSize;i++){
		vADCConvertedArray_3[i]='A';
		vADCConvertedArray_4[i]='Z';
	}
	vADCConvertedArray_3[ui32RecBuffSize-1]='\n';
	vADCConvertedArray_4[ui32RecBuffSize-1]='\n';
}
*/
void DMA2_Stream3_IRQHandler(void) {
	//vTest();
	uint8_t* ui16RecBufferPoint;
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

