/*
 * vcpComand.h
 *
 *  Created on: 4 янв. 2023 г.
 *      Author: user
 */

#ifndef USER_INCLUDE_VCPCOMMAND_H_
#define USER_INCLUDE_VCPCOMMAND_H_

void vTaskVCPRxCommandParser(void *pvParameters);
void vTaskVCPRxCommandHandler(void *pvParameters);

#endif /* USER_INCLUDE_VCPCOMMAND_H_ */
