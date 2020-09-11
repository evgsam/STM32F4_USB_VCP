/*
 * initialization.c
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#include <main.h>

#include <stm32f4xx_adc.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_spi.h>

#include "global_variables.h"

#define ADC_SampleTime ADC_SampleTime_56Cycles

#define RecNVICSubPriority 			2
#define RecNVICTimer2Prority		5

#define RecNVICDMA2Prority			3
#define RecNVICButton1Prority		4

#define ADCDMAPriority				DMA_Priority_High
#define SPIDMAPriority				DMA_Priority_VeryHigh


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

void EXTILine0_Config(void) {

	//STM_EVAL_PBInit(BUTTON_USER,BUTTON_MODE_EXTI);
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef gpioConf;
	// инициализация входа, подключенного к кнопке
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	gpioConf.GPIO_Pin = GPIO_Pin_0;
	gpioConf.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &gpioConf);
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Connect EXTI Line0 to PA0 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	/* Configure EXTI Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


void pvrADCConfiguration(void) {
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseStructure;

	//****************************************************************************/
	//		Enabled clocking ADC2,GPIOx,DMA2,TIM3
	//****************************************************************************/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//****************************************************************************/
	//		ADC2 analog pin's input settings
	//****************************************************************************/
	//A0,A2,A4,A6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//C1,C3,C4
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//B0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//***************************************************************************/
	//		ADC main settings
	//***************************************************************************/
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;	//36Mhz
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;	//ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

	//***************************************************************************/
	//		ADC2 main settings
	//***************************************************************************/
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_RisingFalling;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1; ui8ChanalSum;
	ADC_Init(ADC2, &ADC_InitStructure);

	//*****************************************************************************/
	//		ADC_ExternalTrigConv_T3_TRGO Timer configuration
	//*****************************************************************************
	TIM_TimeBaseStructInit(&TIM_BaseStructure);
	TIM_BaseStructure.TIM_Prescaler = ((SystemCoreClock) / (2 * ui16RecFreq * 10)) - 1;
	TIM_BaseStructure.TIM_Period = 10 - 1;
	TIM_BaseStructure.TIM_ClockDivision = 1;
	TIM_BaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_BaseStructure);
	TIM_SelectOutputTrigger(TIM3, TIM_TRGOSource_Update);
	TIM_Cmd(TIM3, ENABLE);

	//*****************************************************************************/
	//		DMA2 Stream3 Channel1 configuration (ADC2)
	//*****************************************************************************/
	DMA_DeInit(DMA2_Stream3);
	DMA_InitStructure.DMA_Channel = DMA_Channel_1;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &ADC2->DR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t) &ui8ADCConvertedArray_0;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = ui32RecBuffSize;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = ADCDMAPriority;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_DoubleBufferModeConfig(DMA2_Stream3, (uint32_t) &ui8ADCConvertedArray_1, DMA_Memory_0);
	DMA_DoubleBufferModeCmd(DMA2_Stream3, ENABLE);

	DMA_Init(DMA2_Stream3, &DMA_InitStructure);
	DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
	DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);

	//****************************************************************************/
	//		DMA2 stream2 interrupt configuration
	//****************************************************************************/
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = RecNVICDMA2Prority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = RecNVICSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	//****************************************************************************/
	//		ADC channel sequence
	//****************************************************************************/

	ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime);			//PC4
/*	ADC_RegularChannelConfig(ADC2, ADC_Channel_8, 2, ADC_SampleTime);			//PB0

	ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 3, ADC_SampleTime);	 		//PA4
	ADC_RegularChannelConfig(ADC2, ADC_Channel_6, 4, ADC_SampleTime);			//PA6

	ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 5, ADC_SampleTime);			//PA0
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 6, ADC_SampleTime);			//PA2

	ADC_RegularChannelConfig(ADC2, ADC_Channel_11, 7, ADC_SampleTime);			//PC1
	ADC_RegularChannelConfig(ADC2, ADC_Channel_13, 8, ADC_SampleTime);			//PC3
*/
	//*****************************************************************************/
	//		ADC DMA Configuration enable
	//*****************************************************************************/
	//ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);
	ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
	ADC_DMACmd(ADC2, ENABLE);
	ADC_Cmd(ADC2, ENABLE);

	//****************************************************************************/
	//		Interrupts start
	//****************************************************************************/
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	DMA_Cmd(DMA2_Stream3, ENABLE);
}
