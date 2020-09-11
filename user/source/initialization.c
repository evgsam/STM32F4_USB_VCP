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
