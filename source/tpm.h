/*******************************************************************************************
* file name: tpm.h
*
* brief description: include all function protocols related to tpm module
*
* author: Dazong Chen
*
* date: Sep.28.2020
*
* reference source:
* 			Dr. Dean's Embedded Systems Fundamentals with Arm Cortex-M based Microcontrollers P197
*
*******************************************************************************************/


#ifndef _TPM_H_
#define _TPM_H_

#include "MKL25Z4.h"
#include "gpio.h"


#define 			LED_RED_TPM_CONTROL			TPM2->CONTROLS[0]		// RED LED TPM2 CH0
#define 			LED_GREEN_TPM_CONTROL		TPM2->CONTROLS[1]		// GREEN LED TPM2 CH1
#define 			LED_BLUE_TPM_CONTROL		TPM0->CONTROLS[1]		// BLUE LED TPM0 CH1
#define 			COLOR_MULTIPLIER			257						// 65535(UINT16 MAX) / 255(RGB MAX) = 257
#define				STOP_COLOR					0x611E3C
#define 			GO_COLOR					0x229622
#define				WARNING_COLOR				0xFFB200
#define 			CROSSWALK_COLOR				0x001030
#define				COLOR_OFF					0x000000



/**********************************************************************************************
 * function name: tpm_init(uint16_t period)
 *
 * function description: enable clock for specific ports
 *
 * parameter:
 * 		period: value load into mod register
 *
 * return value: none
 *********************************************************************************************/
void tpm_init(uint16_t period);


/**********************************************************************************************
 * function name: color_val(int16_t x, int16_t y, int16_t z)
 *
 * function description: color duty cycle value
 *
 * parameter:
 * 		x: x axis value
 * 		y: y axis value
 * 		z: z axis value
 *
 * return value: none
 *********************************************************************************************/
void color_val(int16_t x, int16_t y, int16_t z);



#endif
