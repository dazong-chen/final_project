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

#include "i2c.h"
#include "MKL25Z4.h"



#define 		I2C0_SDA_PIN				25
#define			I2C0_SCL_PIN				24
#define			I2C0_SDA_CTRL_REG			PORTE->PCR[I2C0_SDA_PIN]
#define			I2C0_SCL_CTRL_REG			PORTE->PCR[I2C0_SCL_PIN]
#define			I2C0_DATA					I2C0->D
#define			FIXED_DATA					2		// 2 bytes of device_addr and reg_addr



// initialize i2c
void i2c_init()
{
	// set pins to I2C function
	I2C0_SDA_CTRL_REG |= PORT_PCR_MUX(5);
	I2C0_SCL_CTRL_REG |= PORT_PCR_MUX(5);

	// baud = bus_freq/(scl_div * mul)
	// 400k = 48M/120, scl_div = 0x11 and mul = 2
	I2C0->F = I2C_F_ICR(0x10) |I2C_F_MULT(0);

	// enable i2c and set to master mode
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	// select high drive mode (directly link to 3.3V)
	I2C0->C2 |= I2C_C2_HDRS_MASK;
}


// send start signal onto bus
void i2c_start()
{
	I2C0->C1 |= I2C_C1_MST_MASK;	// When the MST bit is changed from a 0 to a 1, a START signal is generated on the bus and master mode is selected.
}


// send stop signal onto bus
void i2c_stop()
{
	I2C0->C1 &= ~I2C_C1_MST_MASK;	// When this bit changes from a 1 to a 0, a STOP signal is generated and the mode of operation changes from master to slave
}


// repeat start condition
void i2c_restart()
{
	I2C0->C1 |= I2C_C1_RSTA_MASK;	// Writing a one to this bit generates a repeated START condition provided it is the current master
}


// set transmit mode
void i2c_transmit()
{
	I2C0->C1 |= I2C_C1_TX_MASK;
}


// set receive mode
void i2c_receive()
{
	I2C0->C1 &= ~I2C_C1_TX_MASK;
}


// a byte and acknowledgment have transferred
void i2c_wait()
{
	while((I2C0->S & I2C_S_IICIF_MASK) == 0)
	{
		// wait for transfer
	}

	I2C0->S |= I2C_S_IICIF_MASK; 	// This bit must be cleared by software by writing a 1 to it
}


// send NACK
void i2c_nack()
{
	I2C0->C1 |= I2C_C1_TXAK_MASK;
}


// send ACK
void i2c_ack()
{
	I2C0->C1 &= ~I2C_C1_TXAK_MASK;
}


// write one byte to slave
void i2c_write_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
	i2c_transmit();			// set to transmit
	i2c_start();			// send start signal

	//i2c_ack();
	I2C0_DATA = dev_addr;	// send device addr
	i2c_wait();				// wait for completion

	//i2c_ack();
	I2C0_DATA = reg_addr;		// send register addr
	i2c_wait();				// wait for completion

	//i2c_ack();

	I2C0_DATA = data;		// send data
	i2c_wait();				// wait for completion

	i2c_stop();				// send stop signal

	// wait for bus being idle
	while((I2C0->S & I2C_S_BUSY_MASK)!=0)
	{
		// bus busy
	}
}


// read one byte from reg_addr
uint8_t i2c_read_one_byte(uint8_t dev_addr, uint8_t reg_addr)
{
	uint8_t		data;


	i2c_transmit();			// set to transmit
	i2c_start();			// send start signal

	I2C0_DATA = dev_addr;	// send device addr
	i2c_wait();				// wait for completion

	I2C0_DATA = reg_addr;			// send register addr
	i2c_wait();				// wait for completion

	i2c_restart();			// repeated start

	I2C0_DATA = (dev_addr | 0x01);		// 0x01 indicates read from slave
	i2c_wait();

	i2c_receive();			// set to receive mode
	i2c_nack();

	data = I2C0_DATA;		// junk info
	i2c_wait();				// wait for completion

	i2c_stop();

	data = I2C0_DATA;		// data

	// wait for bus being idle
	while((I2C0->S & I2C_S_BUSY_MASK)!=0)
	{
		// bus busy
	}

	return data;
}


// read several bytes from reg_addr
void i2c_read_bytes(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t count)
{
	uint8_t 	dummy;
	uint8_t		num_bytes_read = 0;


	i2c_transmit();			// set to transmit
	i2c_start();			// send start signal

	I2C0_DATA = dev_addr;	// send device addr
	i2c_wait();				// wait for completion

	I2C0_DATA = reg_addr;			// send register addr
	i2c_wait();				// wait for completion

	i2c_restart();			// repeated start

	I2C0_DATA = (dev_addr | 0x01);		// 0x01 indicates read from slave
	i2c_wait();

	i2c_receive();			// set to receive mode
	i2c_ack();				// send ack after read

	dummy = I2C0_DATA;		// read data
	i2c_wait();

	// move actual data into data buffer
	do
	{
		i2c_ack();		// send ack after read
		data[num_bytes_read] = I2C0_DATA;	// read data
		num_bytes_read++;
		i2c_wait();		// wait for completion

	}while(num_bytes_read < (count-FIXED_DATA));

	i2c_nack();
	data[num_bytes_read] = I2C0_DATA;
	i2c_wait();
	i2c_stop();


	// wait for bus being idle
	while((I2C0->S & I2C_S_BUSY_MASK)!=0)
	{
		// bus busy
	}
}
