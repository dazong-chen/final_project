/*******************************************************************************************
* file name: tpm.c
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

#include "tpm.h"
#include "clock.h"
#include "stdio.h"
#include "stdbool.h"



extern timer_t  	systick_isr_count;




void tpm_init(uint16_t period)
{
	// set pin to FTM
	// Red LED
	LED_RED_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;			// remove mux setting
	LED_RED_PIN_CTRL_REG |= PORT_PCR_MUX(3); 			// set as FTM CH3

	// LED green
	LED_GREEN_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;		// remove mux setting
	LED_GREEN_PIN_CTRL_REG |= PORT_PCR_MUX(3); 			// set as FTM CH3

	// LED blue
	LED_BLUE_PIN_CTRL_REG &= ~PORT_PCR_MUX_MASK;		// remove mux setting
	LED_BLUE_PIN_CTRL_REG |= PORT_PCR_MUX(4); 			// set as FTM CH4

	// configure TPM0
	TPM0->MOD= period - 1;		// load counter and mod
	TPM0->SC = TPM_SC_PS(1);	// prescalar set to 2
	TPM0->CONF |= TPM_CONF_DBGMODE(3); 		// continue operation in debug mode

	LED_BLUE_TPM_CONTROL.CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;		// set blue LED to TPM0 CH1, edge-aligned low-true PWM
	LED_BLUE_TPM_CONTROL.CnV = 0;		//set initial duty cycle;

	// configure TPM2
	TPM2->MOD= period - 1;		// load counter and mod
	TPM2->SC = TPM_SC_PS(1);	// prescalar set to 2
	TPM2->CONF |= TPM_CONF_DBGMODE(3); 		// continue operation in debug mode

	LED_RED_TPM_CONTROL.CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;			// set red LED to TPM2 CH0, edge-aligned low-true PWM
	LED_RED_TPM_CONTROL.CnV = 0;		//set initial duty cycle;
	LED_GREEN_TPM_CONTROL.CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;		// set green LED to TPM2 CH1, edge-aligned low-true PWM
	LED_GREEN_TPM_CONTROL.CnV = 0;		//set initial duty cycle;

	// start tpm
	TPM0->SC |= TPM_SC_CMOD(1);			// start TPM0
	TPM2->SC |= TPM_SC_CMOD(1);			// start TPM2

}



void color_change(int16_t x, int16_t y, int16_t z)
{
	LED_RED_TPM_CONTROL.CnV = x;			// 100% duty cycle for red LED
	LED_GREEN_TPM_CONTROL.CnV = y;		// 100% duty cycle for green led
	LED_BLUE_TPM_CONTROL.CnV = z;			// 100% duty cycle for blue led
}
