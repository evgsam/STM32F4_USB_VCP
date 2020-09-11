#include "main.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

uint8_t Rxbuffer[64];
__IO uint32_t receive_count = 1;
extern __IO uint32_t data_sent;

void sendHello(uint8_t * pbuf, uint32_t buf_len) {
	VCP_SendData(&USB_OTG_dev, &pbuf, buf_len);
}

int main(void) {
	SystemInit();

	initialization();
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);

	pvrADCConfiguration();
	ADC_SoftwareStartConv(ADC2);
	//EXTILine0_Config();
#ifdef DEBUG_MODE
	xprintf(" hello! \n");
#endif



	/* Main loop */
	while (1) {
		/*while (VCP_CheckDataReceived() == 0);

		//receive one character
		VCP_ReceiveData(&USB_OTG_dev, Rxbuffer, receive_count);
		STM_EVAL_LEDToggle(LED5);

		// Check to see if we have data yet
		if (receive_count != 0) {
			// wait data sent
			while (VCP_CheckDataSent() == 1)
				;
			STM_EVAL_LEDToggle(LED3);
			// send myTxBuffer
			VCP_SendData(&USB_OTG_dev, Rxbuffer, receive_count);
			STM_EVAL_LEDToggle(LED6);

			// INIT received byte count
			receive_count = 0;

		}
		*/

	}
}

