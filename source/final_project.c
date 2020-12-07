/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    final_project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


#include "stdbool.h"
#include "stdlib.h"
#include "clock.h"
#include "i2c.h"
#include "gpio.h"
#include "accelerometer.h"
#include "tpm.h"
#include "my_debug.h"


// DEBUG_MODE is defined in my_debug.h
// if DEBUG_MODE is defined, program will run in debug mode which will print accelerometer xyz value and times run into PTA IRQ_Handler
// if not defined, it will just blink LED

#ifdef DEBUG_MODE
	#define 		DEBUG_PRINTF 				printf
#else
	#define			DEBUG_PRINTF(...)
#endif


/*
 * @brief   Application entry point.
 */
int main()
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif


    // axis values
    int16_t 	x = 0;
    int16_t		y = 0;
    int16_t		z = 0;
    extern bool 	board_rotate;


    clock_init();
    i2c_init();
    accelerometer_init();
    tpm_init(48000);


    while(1)
    {

    	if(board_rotate)
    	{
    		x = getXAxisValue(); // SENSITIVITY_RATIO;
    		y = getYAxisValue(); // SENSITIVITY_RATIO;
    		z = getZAxisValue(); // SENSITIVITY_RATIO;

    		color_val(x, y, z);	// set TPM.CnV value to set LED duty cycle
    		color_val(COLOR_OFF, COLOR_OFF, COLOR_OFF);		// turn off LED
    		board_rotate = false;

    	#ifdef DEBUG_MODE
    		printf("x1 = %d, y1 = %d, z1 = %d\r\n", x, y, z);
        	printf("PTA IRQ Handler count = %lu\r\n", irq_counter());
		#endif
    	}
    }

}
