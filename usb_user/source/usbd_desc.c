/**
  ******************************************************************************
  * @file    usbd_desc.c
  * @author  MCD Application Team
  * @version V1.2.1
  * @date    17-March-2018
  * @brief   This file provides the USBD descriptors and string formating method.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      <http://www.st.com/SLA0044>
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_req.h"
#include "usbd_conf.h"
#include "usb_regs.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_DESC 
  * @brief USBD descriptors module
  * @{
  */

/** @defgroup USBD_DESC_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_DESC_Private_Defines
  * @{
  */
#define USBD_VID                        0x0483
#define USBD_PID                        0x5740

/** @defgroup USB_String_Descriptors
  * @{
  */
#define USBD_LANGID_STRING              0x409
#define USBD_MANUFACTURER_STRING        "STMicroelectronics"
#define USBD_PRODUCT_HS_STRING          "STM32 Virtual ComPort in HS mode"
#define USBD_PRODUCT_FS_STRING          "STM32 Virtual ComPort in FS Mode"
#define USBD_CONFIGURATION_HS_STRING    "VCP Config"
#define USBD_INTERFACE_HS_STRING        "VCP Interface"
#define USBD_CONFIGURATION_FS_STRING    "VCP Config"
#define USBD_INTERFACE_FS_STRING        "VCP Interface"
/**
  * @}
  */


/** @defgroup USBD_DESC_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup USBD_DESC_Private_Variables
  * @{
  */

USBD_DEVICE USR_desc = {
  USBD_USR_DeviceDescriptor,
  USBD_USR_LangIDStrDescriptor,
  USBD_USR_ManufacturerStrDescriptor,
  USBD_USR_ProductStrDescriptor,
  USBD_USR_SerialStrDescriptor,
  USBD_USR_ConfigStrDescriptor,
  USBD_USR_InterfaceStrDescriptor,
};



//====================================================================
//                     Device Descriptor
//====================================================================
#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
#endif                          /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_DeviceDesc[USB_SIZ_DEVICE_DESC] __ALIGN_END = {
  0x12,                         // bLength общая длина дескриптора устройства в байтах
  USB_DEVICE_DESCRIPTOR_TYPE,   // bDescriptorType показывает, что это за дескриптор. В данном случае - Device descriptor
  WBVAL(0x0200),                // bcdUSB какую версию стандарта USB поддерживает устройство. 2.0
  0x02,                         // bDeviceClass
  0x02,                         // bDeviceSubClass
  0x00,                         // bDeviceProtocol
  USB_OTG_MAX_EP0_SIZE,         // bMaxPacketSize0 максимальный размер пакетов для Endpoint 0 (при конфигурировании)
  WBVAL(USBD_VID),				// idVendor
  WBVAL(USBD_PID),				// idProduct
  WBVAL(0x0200),                // bcdDevice rel. 2.00
  USBD_IDX_MFC_STR,             // Index of manufacturer string
  USBD_IDX_PRODUCT_STR,         // Index of product string
  USBD_IDX_SERIAL_STR,          // Index of serial number string
  USBD_CFG_MAX_NUM              // bNumConfigurations
};                              // USB_DeviceDescriptor

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
#endif                          /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]
  __ALIGN_END = {
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
#endif                          /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
/* USB Standard Device Descriptor */
__ALIGN_BEGIN uint8_t USBD_LangIDDesc[USB_SIZ_STRING_LANGID] __ALIGN_END = {
  USB_SIZ_STRING_LANGID,
  USB_DESC_TYPE_STRING,
  LOBYTE(USBD_LANGID_STRING),
  HIBYTE(USBD_LANGID_STRING),
};

uint8_t USBD_StringSerial[USB_SIZ_STRING_SERIAL] = {
  USB_SIZ_STRING_SERIAL,
  USB_DESC_TYPE_STRING,
};

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )      /* !< IAR Compiler */
#pragma data_alignment=4
#endif
#endif                          /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
extern __ALIGN_BEGIN uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ] __ALIGN_END;

/**
  * @}
  */


/** @defgroup USBD_DESC_Private_FunctionPrototypes
  * @{
  */
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len);
static void Get_SerialNum(void);
/**
  * @}
  */


/** @defgroup USBD_DESC_Private_Functions
  * @{
  */

/**
* @brief  USBD_USR_DeviceDescriptor 
*         return the device descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_DeviceDescriptor(uint8_t speed, uint16_t * length)
{
  *length = sizeof(USBD_DeviceDesc);
  return (uint8_t *) USBD_DeviceDesc;
}

/**
* @brief  USBD_USR_LangIDStrDescriptor 
*         return the LangID string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_LangIDStrDescriptor(uint8_t speed, uint16_t * length)
{
  *length = sizeof(USBD_LangIDDesc);
  return (uint8_t *) USBD_LangIDDesc;
}


/**
* @brief  USBD_USR_ProductStrDescriptor 
*         return the product string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_ProductStrDescriptor(uint8_t speed, uint16_t * length)
{
  if (speed == 0)
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_PRODUCT_HS_STRING, USBD_StrDesc,
                   length);
  }
  else
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_PRODUCT_FS_STRING, USBD_StrDesc,
                   length);
  }
  return USBD_StrDesc;
}

/**
* @brief  USBD_USR_ManufacturerStrDescriptor 
*         return the manufacturer string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_ManufacturerStrDescriptor(uint8_t speed, uint16_t * length)
{
  USBD_GetString((uint8_t *) (uint8_t *) USBD_MANUFACTURER_STRING, USBD_StrDesc,
                 length);
  return USBD_StrDesc;
}

/**
* @brief  USBD_USR_SerialStrDescriptor 
*         return the serial number string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_SerialStrDescriptor(uint8_t speed, uint16_t * length)
{
  *length = USB_SIZ_STRING_SERIAL;

  /* Update the serial number string descriptor with the data from the unique
   * ID */
  Get_SerialNum();

  return (uint8_t *) USBD_StringSerial;
}

/**
* @brief  USBD_USR_ConfigStrDescriptor 
*         return the configuration string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_ConfigStrDescriptor(uint8_t speed, uint16_t * length)
{
  if (speed == USB_OTG_SPEED_HIGH)
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_CONFIGURATION_HS_STRING,
                   USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_CONFIGURATION_FS_STRING,
                   USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}


/**
* @brief  USBD_USR_InterfaceStrDescriptor 
*         return the interface string descriptor
* @param  speed : current device speed
* @param  length : pointer to data length variable
* @retval pointer to descriptor buffer
*/
uint8_t *USBD_USR_InterfaceStrDescriptor(uint8_t speed, uint16_t * length)
{
  if (speed == 0)
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_INTERFACE_HS_STRING,
                   USBD_StrDesc, length);
  }
  else
  {
    USBD_GetString((uint8_t *) (uint8_t *) USBD_INTERFACE_FS_STRING,
                   USBD_StrDesc, length);
  }
  return USBD_StrDesc;
}

/**
  * @brief  Create the serial number string descriptor
  * @param  None
  * @retval None
  */
static void Get_SerialNum(void)
{
  uint32_t deviceserial0, deviceserial1, deviceserial2;

  deviceserial0 = *(uint32_t *) DEVICE_ID1;
  deviceserial1 = *(uint32_t *) DEVICE_ID2;
  deviceserial2 = *(uint32_t *) DEVICE_ID3;

  deviceserial0 += deviceserial2;

  if (deviceserial0 != 0)
  {
    IntToUnicode(deviceserial0, &USBD_StringSerial[2], 8);
    IntToUnicode(deviceserial1, &USBD_StringSerial[18], 4);
  }
}

/**
  * @brief  Convert Hex 32Bits value into char
  * @param  value: value to convert
  * @param  pbuf: pointer to the buffer
  * @param  len: buffer length
  * @retval None
  */
static void IntToUnicode(uint32_t value, uint8_t * pbuf, uint8_t len)
{
  uint8_t idx = 0;

  for (idx = 0; idx < len; idx++)
  {
    if (((value >> 28)) < 0xA)
    {
      pbuf[2 * idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2 * idx] = (value >> 28) + 'A' - 10;
    }

    value = value << 4;

    pbuf[2 * idx + 1] = 0;
  }
}

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
