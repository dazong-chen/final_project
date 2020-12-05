/*******************************************************************************************
* file name: clock.c
*
* brief description: include all function related to timer and clock
*
* author: Dazong Chen
*
* date: Sep.28.2020
*
* reference source:
* 			Dr. Dean: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
*
*******************************************************************************************/

#include "clock.h"
#include "gpio.h"
#include "tpm.h"


#define			PROCESSOR_FREQ			48000000

timer_t  	total_systick_isr_count = 0;
timer_t		systick_isr_count_after_reset = 0;



// initialize clock
void clock_init()
{
	// enable clock for TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK | SIM_SCGC6_TPM2_MASK;			// enable clock for TPM0 and TPM2

	SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);

	// enable clock for I2C
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;

	// enable clock for PortA, PortB, PortD and PortE
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK
			    | SIM_SCGC5_PORTB_MASK
				| SIM_SCGC5_PORTD_MASK
				| SIM_SCGC5_PORTE_MASK;
}


// delay in milliseconds
void delay_process(int mseconds)
{
	uint32_t  count = 4800 * mseconds;
	while(count-- > 0)
	{
		__asm volatile ("NOP");
	}
}
