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


void accelerometer_init();

void accelerometer_calibration();

uint16_t getAxisValue(uint8_t axis_addr);

uint16_t getXAxisValue();

uint16_t getYAxisValue();

uint16_t getZAxisValue();

// check if byte is written into the register
void test_if_written(uint8_t reg_addr, uint8_t reg_data);


#endif
