/*******************************************************************************************
* file name: i2c.h
*
* brief description: include all function related to I2C
*
* author: Dazong Chen
*
* date: Nov.29.2020
*
* reference source:
* 			Dr. Dean Chapter 8
*
*******************************************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

#include "stdint.h"



/**********************************************************************************************
 * function name: i2c_init()
 *
 * function description: initialize I2C
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_init();


/**********************************************************************************************
 * function name: i2c_start()
 *
 * function description: send start signal onto bus
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_start();


/**********************************************************************************************
 * function name: i2c_stop()
 *
 * function description: send stop signal onto bus
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_stop();


/**********************************************************************************************
 * function name: i2c_restart()
 *
 * function description: repeat start condition
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_restart();


/**********************************************************************************************
 * function name: i2c_transmit()
 *
 * function description: enable transmit mode
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_transmit();


/**********************************************************************************************
 * function name: i2c_receive()
 *
 * function description: enable receive mode
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_receive();


/**********************************************************************************************
 * function name: i2c_wait()
 *
 * function description: wait for completion
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_wait();


/**********************************************************************************************
 * function name: i2c_nack()
 *
 * function description: send a NACK onto bus
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_nack();


/**********************************************************************************************
 * function name: i2c_ack()
 *
 * function description: send an ACK onto bus
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void i2c_ack();


/**********************************************************************************************
 * function name: i2c_write_byte()
 *
 * function description: write a byte of data onto bus
 *
 * parameter:
 * 		dev_addr: device address
 * 		reg_addr: register address
 * 		data: one byte of data
 *
 * return value: none
 *********************************************************************************************/
void i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);


/**********************************************************************************************
 * function name: i2c_read_one_byte()
 *
 * function description: read one byte from register
 *
 * parameter:
 * 		dev_addr: device address
 * 		reg_addr: register address
 *
 * return value: value of register
 *********************************************************************************************/
uint8_t i2c_read_one_byte(uint8_t dev_addr, uint8_t reg_addr);


/**********************************************************************************************
 * function name: i2c_read_bytes
 *
 * function description: write a byte of data onto bus
 *
 * parameter:
 * 		dev_addr: device address
 * 		reg_addr: start register address
 * 		*data: data buffer than will contain the output data
 * 		count: bytes to be read
 *
 * return value: none
 *********************************************************************************************/
void i2c_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t count);


#endif
