/*******************************************************************************************
* file name: accelerometer.h
*
* brief description: include all function related to MMA8451Q data sheet
*
* author: Dazong Chen
*
* date: Dec.03.2020
*
* reference source:
* 		MMA8451Q Data sheet https://www.nxp.com/docs/en/data-sheet/MMA8451Q.pdf
* 		https://community.nxp.com/t5/Sensors-Knowledge-Base/MMA8451Q-Bare-metal-example-project/ta-p/1127268
* 		https://www.nxp.com/docs/en/application-note/AN4069.pdf
*******************************************************************************************/

#include "accelerometer.h"
#include "i2c.h"
#include "clock.h"
#include <stdio.h>
#include "stdbool.h"
#include "assert.h"

// Accelerometer related #define
#define		DEVICE_ADDR				0x1D<<1		// device address is held in upper 7-bit, so left shift 1
#define		REG_WHO_AM_I			0x0D		// WHO_AM_I Device ID register
#define		WHO_AM_I_VAL			0x1A		// value of WHO_AM_I Device ID register

#define		STATUS_REG				0x00		// status register address

#define		CTRL_REG_1				0x2A        // ctrl register 1 address
#define		CTRL_REG_1_VAL			0x19		// ODR = 100Hz, reduced noise mode, Active mode
#define		CTRL_REG_1_STANDBY		0x00		// standby MMA

#define		CTRL_REG_2				0x2B		// ctrl register 2 address
#define		CTRL_REG_2_RST			0x40		// set reset bit
#define		CTRL_REG_2_VAL			0x02		// high resolution set

#define		CTRL_REG_3				0x2C		// ctrl register 3 address
#define		CTRL_REG_3_VAL			0x00		// Push-pull, active low interrupt

#define		CTRL_REG_4				0x2D		// ctrl register 4 address
#define		CTRL_REG_4_VAL			0x04		// motion interrupt enabled

#define		CTRL_REG_5				0x2E		// ctrl register 5 address
#define		CTRL_REG_5_VAL			0x04		// Interrupt is routed to INT1 pin

#define 	OFF_X					0x2F    	// XYZ Offset Correction Registers
#define 	OFF_Y					0x30
#define 	OFF_Z					0x31

#define 	XYZ_DATA_CFG			0x0E		// XYZ_DATA_CFG address
#define		XYZ_DATA_CFG_VAL		0x00		// choose 2g scale

#define		FF_MT_CFG				0x15		// FF_MT_CFG address
#define		FF_MT_CFG_VAL			0xF8		// ELE = 0, OAE = 1, ZEFE = 1, YEFE = 1, XEFE = 1

#define		FF_MT_THS				0x17		// FF_MT_THS
#define		FF_MT_THS_VAL			0x20		// THS = 32, 2g/0.063 = 31.7 round up 32

#define		FF_MT_COUNT				0x18		// FF_MT_COUNT
#define		FF_MT_COUNT_VAL			0x0A		// debounce 80 counts, 100ms/1.25ms = 80

#define     DATA_REG_OUT_X_MSB      0x01        // x-axis data register
#define     DATA_REG_OUT_Y_MSB      0x03        // y-axis data register
#define		DATA_REG_OUT_Z_MSB		0x05        // z-axis data register

#define		DATA_REG_MSB_SHIFT		8           // MSB register reads data from data bit6-bit13
#define		DATA_REG_LSB_SHIFT		2           // LSB register reads data from data bit0-bit5

#define		CALIBRATION_RATIO		8			// 2g value calibration




void accelerometer_init()
{
	uint8_t reset_in_process;


	// configure accelerometer
	if(i2c_read_one_byte(DEVICE_ADDR, REG_WHO_AM_I) == WHO_AM_I_VAL)
	{
		// reset MMA
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_2, CTRL_REG_2_RST);

		// Wait for the RST bit to clear, reset done, after reset done, MMA will be in standy mode
		do
		{
			reset_in_process = i2c_read_one_byte(DEVICE_ADDR, CTRL_REG_2) & 0x40;
		}while (reset_in_process);

		// using 2g scale
		i2c_write_byte(DEVICE_ADDR, XYZ_DATA_CFG, XYZ_DATA_CFG_VAL);

		// Push-pull, active low interrupt
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_3, 0x00);

		// ELE = 1, OAE = 1, ZEFE = 1, YEFE = 1, XEFE = 1, FF_MT_CFG_VAL = 0xF8
		i2c_write_byte(DEVICE_ADDR, FF_MT_CFG, FF_MT_CFG_VAL);

		// THS = 32, 2g/0.063 = 31.7 round up 32, FF_MT_THS_VAL = 32
		i2c_write_byte(DEVICE_ADDR, FF_MT_THS, FF_MT_THS_VAL);

		// debounce 10 counts, FF_MT_COUNT_VAL = 0x0A
		i2c_write_byte(DEVICE_ADDR, FF_MT_COUNT, FF_MT_COUNT_VAL);

		// Enable motion interrupt, CTRL_REG_4_VAL - 0x04
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_4, CTRL_REG_4_VAL);

		// test if i2c write byte is actually writing to the MMA CTRL_REG_4 register
		test_if_written(CTRL_REG_4, CTRL_REG_4_VAL);	// register value got written

		// motion interrupt routed to INT1 - PTA14, CTRL_REG_4_VAL = 0x04
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_5, CTRL_REG_4_VAL);

		// using high resolution mode
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_2, CTRL_REG_2_VAL);

		// 100Hz, active mode
		i2c_write_byte(DEVICE_ADDR, CTRL_REG_1, CTRL_REG_1_VAL);

		printf("MMA8451Q Accelerometer is successfully initialized \r\n");
	}
}


// get axis value depends on axis addr
int16_t getAxisValue(uint8_t axis_addr)
{
	int16_t 	data;
	uint8_t 	axis_data[2];
	int 		length = sizeof(axis_data)/sizeof(axis_data[0]);


	if(axis_addr < 0)
	{
		data = -1;		// invalid input
	}

	else
	{
		i2c_read_bytes(DEVICE_ADDR, axis_addr, axis_data, length);	// read MSB bytes and LSB byte from axis wanted

		data = (axis_data[0] << DATA_REG_MSB_SHIFT) | (axis_data[1] >> DATA_REG_LSB_SHIFT);   // MSB | LSB to get 14bits of data
	}

	return data;
}


// get X axis value
int16_t getXAxisValue()
{
	return getAxisValue(DATA_REG_OUT_X_MSB);
}


// get Y axis value
int16_t getYAxisValue()
{
	return getAxisValue(DATA_REG_OUT_Y_MSB);
}


// get Z axis value
int16_t getZAxisValue()
{
	return getAxisValue(DATA_REG_OUT_Z_MSB);
}


// check if data byte is written into the register
void test_if_written(uint8_t reg_addr, uint8_t reg_data)
{
	uint8_t data = i2c_read_one_byte(DEVICE_ADDR, reg_addr);
	assert(data == reg_data);
}
