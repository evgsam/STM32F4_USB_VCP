#include "stm32f4_discovery.h"
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

int main(void) {
	SystemInit();
	initialization();
#ifdef DEBUG_MODE
	xprintf(" hello! \n");
#endif

	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb,
			&USR_cb);

	/* Main loop */
	while (1) {
		STM_EVAL_LEDToggle(LED3);
		delay(100);
		STM_EVAL_LEDToggle(LED5);
		delay(100);
		STM_EVAL_LEDToggle(LED6);
		delay(100);
		STM_EVAL_LEDToggle(LED4);
		delay(100);
	}
}

