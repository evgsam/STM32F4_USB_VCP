/*
 * main.h
 *
 *  Created on: 3 мая 2020 г.
 *      Author: evgsam
 */

#ifndef USER_INCLUDE_MAIN_H_
#define USER_INCLUDE_MAIN_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stm32f4xx.h>

#include <stm32f4_discovery.h>
#include <stm32f4_discovery_debug.h>


#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_core_loopback.h"

volatile uint32_t ui32ticksDelay;

void sendHello(void);

#endif /* USER_INCLUDE_MAIN_H_ */
