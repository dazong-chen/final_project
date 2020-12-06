/*******************************************************************************************
* file name: tpm.h
*
* brief description: include all function protocols related to tpm module
*
* author: Dazong Chen
*
* date: Dec.04.2020
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

#define				COLOR_OFF					0



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
