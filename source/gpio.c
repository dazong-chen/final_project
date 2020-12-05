/*******************************************************************************************
* file name: clock.c
*
* brief description: include all functions protocols related to gpio
*
* author: Dazong Chen
*
* date: Dec.03.2020
*
* reference source:
* 			Howdy Pierce: PES 10 KL25Z and GPIO pt2.pptx
* 			Dr. Dean: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
*
*******************************************************************************************/

#include "gpio.h"
#include "stdbool.h"

// PTA14 related #define
#define		INT1_PORT				GPIOA
#define		INT1_PIN				14
#define		INT1_CTRL_REG			PORTA->PCR[INT1_PIN]


bool 		board_rotate = false;
uint32_t	int1_signal_counter = 0;

// initialize INT1 pin
void int1_signal_init()
{
	// configure INT1
	INT1_CTRL_REG &= ~PORT_PCR_MUX_MASK;	// remove mux setting
	INT1_CTRL_REG |= PORT_PCR_MUX(1);		// set to gpio,

	INT1_CTRL_REG |= PORT_PCR_IRQC(0x0A)	// enable interrupt on falling edge.
				   | PORT_PCR_PS_MASK
				   | PORT_PCR_PE_MASK;

	INT1_PORT->PDDR &= ~(1<<INT1_PIN);		// set pin to input

	NVIC_SetPriority(PORTA_IRQn, 2);
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);

	__enable_irq();
}

bool board_move()
{
	return board_rotate;
}

uint32_t get_INT1IRQ_count()
{
	return int1_signal_counter;
}

// PORT A interrupt
void PORTA_IRQHandler()
{
	// if PTA14 ISF is detected
	if(PORTA->ISFR & (1 << INT1_PIN))
	{
		board_rotate = true;
		PORTA->ISFR &= (1 << INT1_PIN);		// clear status flags

		int1_signal_counter++;
	}
}
