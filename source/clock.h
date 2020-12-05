/*******************************************************************************************
* file name: clock.c
*
* brief description: include all function protocols related to timer and clock
*
* author: Dazong Chen
*
* date: Sep.28.2020
*
* reference source:
* 			Dr. Dean: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
*
*******************************************************************************************/


#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "MKL25Z4.h"
#include "core_cm0plus.h"


typedef uint32_t timer_t;


/**********************************************************************************************
 * function name: clock_init();
 *
 * function description: enable clock for specific ports
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void clock_init();


/**********************************************************************************************
 * function name: systick_init()
 *
 * function description: initialize systick
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void systick_init();


/**********************************************************************************************
 * function name: delay_process(int mseconds)
 *
 * function description: delay in milliseconds
 *
 * parameter:
 * 		mseconds: the amount of milliseconds
 *
 * return value: none
 *********************************************************************************************/
void delay_process(int mseconds);


/**********************************************************************************************
 * function name: get_timer()
 *
 * function description: time passed since last time called reset_timer()
 *
 * parameter: none
 *
 * return value: time in ms
 *********************************************************************************************/
timer_t get_timer();


/**********************************************************************************************
 * function name: reset_timer()
 *
 * function description: restart timer
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void reset_timer();


/**********************************************************************************************
 * function name: now()
 *
 * function description: time passed since startup
 *
 * parameter: none
 *
 * return value: time in ms
 *********************************************************************************************/
timer_t now();




#endif
