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


void color_change(uint32_t start_color, uint32_t end_color, uint32_t duration)
{
	// current color value
	uint16_t  		red_current = 0;
	uint16_t  		green_current = 0;
	uint16_t  		blue_current = 0;

	// start state color value
	uint16_t  		red_start = 0;
	uint16_t  		green_start = 0;
	uint16_t  		blue_start = 0;

	// end state color value
	uint16_t  		red_end = 0;
	uint16_t  		green_end = 0;
	uint16_t  		blue_end = 0;


	color_decode(start_color, &red_start, &green_start, &blue_start);		// get start state RGB individual color val
	color_decode(end_color, &red_end, &green_end, &blue_end);				// get end state RGB individual color val

	// color val difference between end state and start state
	float red_diff = red_end - red_start;
	float green_diff = green_end - green_start;
	float blue_diff = blue_end - blue_start;

	reset_timer();

	// LED duty cycle changes based on time duration
	while(get_timer() <= duration)
	{
		// RGB current value
		red_current = red_diff * get_timer() * 0.001 + red_start;
		green_current = green_diff * get_timer() * 0.001 + green_start;
		blue_current = blue_diff * get_timer() * 0.001 + blue_start;

		LED_RED_TPM_CONTROL.CnV = red_current * COLOR_MULTIPLIER;			// calculate current red LED duty cycle
		LED_GREEN_TPM_CONTROL.CnV = green_current * COLOR_MULTIPLIER;		// calculate current green LED duty cycle
		LED_BLUE_TPM_CONTROL.CnV = blue_current * COLOR_MULTIPLIER;			// calculate current blue LED duty cycle
	}
}


// how long to spent in same state
void color_steady_state(const uint32_t color, uint32_t duration)
{
	uint16_t  		red_val = 0;
	uint16_t  		green_val = 0;
	uint16_t  		blue_val = 0;

	color_decode(color, &red_val, &green_val, &blue_val);

	LED_RED_TPM_CONTROL.CnV = red_val * COLOR_MULTIPLIER;			// 100% duty cycle for red LED
	LED_GREEN_TPM_CONTROL.CnV = green_val * COLOR_MULTIPLIER;		// 100% duty cycle for green led
	LED_BLUE_TPM_CONTROL.CnV = blue_val * COLOR_MULTIPLIER;			// 100% duty cycle for blue led

	reset_timer();

	while(get_timer() <= duration)
	{
		// wait until reaches duration time
	}
}


// convert color code into individual RGB value
void color_decode(const uint32_t color,uint16_t *red, uint16_t *green, uint16_t *blue)
{
	// color value comes in format as 0xRRGGBB
	*red = color >> 16;
	*green = (color >> 8) & 0xFF;
	*blue = color & 0xFF;
}

