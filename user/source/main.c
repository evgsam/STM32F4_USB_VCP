#include "main.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

uint8_t Rxbuffer[64];
__IO uint32_t receive_count = 1;
extern __IO uint32_t data_sent;

void delay(uint32_t ui32ms) {
	uint32_t ui32start = ui32ticksDelay;
	while ((ui32ticksDelay - ui32start) < ui32ms)
		;
}

void sendHello(uint32_t *pbuf, uint32_t buf_len) {
	VCP_SendData(&USB_OTG_dev, &pbuf[0], buf_len);
}

int main(void) {
	SystemInit();
	initialization();
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb,
			&USR_cb);
	pvrADCConfiguration();
	ADC_SoftwareStartConv(ADC2);

#ifdef DEBUG_MODE
	xprintf(" hello! \n");
#endif

	/* Main loop */
	while (1) {
	}
}

