/*
 * global_variables.h
 *
 *  Created on: 27 мая 2016 г.
 *      Author: evgsam
 */

#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define ui8ChanalSum 1
#define ui16RecFreq 16000
#define ui8PollindTime 16
#define ui32RecBuffSize 16000//25//(ui16RecFreq/1000)*ui8ChanalSum*ui8PollindTime


uint8_t ui8ADCConvertedArray_0[ui32RecBuffSize];
uint8_t ui8ADCConvertedArray_1[ui32RecBuffSize];



#endif /* GLOBAL_VARIABLES_H_ */
