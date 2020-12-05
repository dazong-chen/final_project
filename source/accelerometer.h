/*******************************************************************************************
* file name: accelerometer.h
*
* brief description: include all function related to MMA8451Q data sheet
*
* author: Dazong Chen
*
* date: Dec.02.2020
*
* reference source:
* 		MMA8451Q Data sheet https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf
*******************************************************************************************/


#ifndef _ACCELEROMETER_H_
#define _ACCELEROMETER_H_

#include "MKL25Z4.h"
#include "i2c.h"


#define		SENSITIVITY_RATIO		4096        // 2g mode


/**********************************************************************************************
 * function name: accelerometer_init()
 *
 * function description: initialize accelerometer
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void accelerometer_init();


/**********************************************************************************************
 * function name: getAxisValue(uint8_t axis_addr)
 *
 * function description: read axis 14-bit data
 *
 * parameter:
 * 		uint8_t axis_addr: x, y, or z axis register address
 *
 * return value: none
 *********************************************************************************************/
int16_t getAxisValue(uint8_t axis_addr);


/**********************************************************************************************
 * function name: getXAxisValue()
 *
 * function description: read x-axis 14-bit value from accelerometer
 *
 * parameter: none
 *
 * return value: x-axis 14-bit value
 *********************************************************************************************/
int16_t getXAxisValue();


/**********************************************************************************************
 * function name: getYAxisValue()
 *
 * function description: read y-axis 14-bit value from accelerometer
 *
 * parameter: none
 *
 * return value: y-axis 14-bit value
 *********************************************************************************************/
float getYAxisValue();


/**********************************************************************************************
 * function name: getZAxisValue()
 *
 * function description: read z-axis 14-bit value from accelerometer
 *
 * parameter: none
 *
 * return value: z-axis 14-bit value
 *********************************************************************************************/
int16_t getZAxisValue();


/**********************************************************************************************
 * function name: test_if_written
 *
 * function description: check if data is being written into register, assert() will report failure
 *
 * parameter:
 * 		reg_addr: register address
 * 		reg_data: configured register data
 *
 * return value: none
 *********************************************************************************************/
void test_if_written(uint8_t reg_addr, uint8_t reg_data);

void read_full_xyz();
#endif
