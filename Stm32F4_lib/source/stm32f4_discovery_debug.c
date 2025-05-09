/**
  ******************************************************************************
  * <h2><center>&copy; COPYRIGHT 2012 Embest Tech. Co., Ltd.</center></h2>
  * @file    stm32f4_discovery_debug.c
  * @author  CMP Team
  * @version V1.0.0
  * @date    28-December-2012
  * @brief   Contains some utilities that used for debugging through UART   
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, Embest SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
  * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
  * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  ******************************************************************************
  */ 
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_debug.h"
#include <xprintf.h>


/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup stm32f4_discovery_debug
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Display Init (LCD or/and USART)
  * @param  None
  * @retval None
  */

void usart_sendb(USART_TypeDef * USART, char ch) {
	  USART_SendData(EVAL_COM1, (uint8_t) ch);

	  /* Loop until the end of transmission */
	  while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
	  {}


}
/*USART1 send byte */
void ser1_sendb(unsigned char byte) {
    usart_sendb(USART1, byte);
}

void STM32f4_Discovery_Debug_Init(void)
{ 
  USART_InitTypeDef USART_InitStructure;
  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM1, &USART_InitStructure);
  xdev_out(ser1_sendb);

}

/**
  * @brief  Read character but no wait if no key
  * @param  None
  * @retval None
  */
/*  */
int Get_Peek_Key(void)
{
	if (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_RXNE) == RESET) 
	{
		return EOF;
	}
	return (USART_ReceiveData(EVAL_COM1));
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */



/****************** COPYRIGHT 2012 Embest Tech. Co., Ltd.*****END OF FILE******/
