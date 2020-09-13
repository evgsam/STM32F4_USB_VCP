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

void TIM2_IRQHandler(void) {
	static uint16_t *ui16RecBufferPoint;
	static uint32_t i = 0;
	static bool flag1;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1,  ADC_SampleTime_3Cycles);			//PC4
		ADC_SoftwareStartConv(ADC2);

		if (i <ui32RecBuffSize) {
			ui8ADCConvertedArray_0[i] =ADC_GetConversionValue(ADC2);
			flag1=true;
			i++;
		} else {
			if (flag1) {
				sendHello(&ui8ADCConvertedArray_0[0],sizeof(ui8ADCConvertedArray_0));
				STM_EVAL_LEDToggle(LED3);
				flag1=false;
			}
			if (i == (2 * ui32RecBuffSize)) {
				sendHello(&ui8ADCConvertedArray_1[0],sizeof(ui8ADCConvertedArray_1));
				STM_EVAL_LEDToggle(LED6);
				i = 0;
			}
			if (i < (2 * (sizeof(ui8ADCConvertedArray_0)))) { //
				ui8ADCConvertedArray_1[i - ui32RecBuffSize] =ADC_GetConversionValue(ADC2);// (uint8_t)(value);//, (uint8_t)value;// {ADC_GetConversionValue(ADC2)&0xff,;
				i++;
			}
		}

	}
}

void DMA2_Stream3_IRQHandler(void) {
	if (DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3)) {
		DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
		if (DMA_GetCurrentMemoryTarget(DMA2_Stream3) == 0) {
			//ui16RecBufferPoint = usADCConvertedValue_1;
			//sendHello(&ui8TestArray_0[0], sizeof(ui8TestArray_0));
			sendHello(&ui8ADCConvertedArray_0[0],
					sizeof(ui8ADCConvertedArray_0));
			STM_EVAL_LEDToggle(LED3);
		} else {
			//ui16RecBufferPoint = usADCConvertedValue_2;
			//	sendHello(&ui8TestArray_1[0], sizeof(ui8TestArray_1));
			sendHello(&ui8ADCConvertedArray_1[0],
					sizeof(ui8ADCConvertedArray_1));
			STM_EVAL_LEDToggle(LED6);
		}
	}

	/*DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
	 sendHello(&ui8ADCConvertedArray_0[0], sizeof(ui8ADCConvertedArray_0));
	 STM_EVAL_LEDToggle(LED3);
	 */
}
