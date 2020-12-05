/*******************************************************************************************
* file name: clock.c
*
* brief description: include all functions protocols related to gpio
*
* author: Dazong Chen
*
* date: Sep.28.2020
*
* reference source:
* 			Howdy Pierce: PES 10 KL25Z and GPIO pt2.pptx
* 			Dr. Dean: https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_2/Source/main.c
*
*******************************************************************************************/


#ifndef _GPIO_H_
#define _GPIO_H_

#include "MKL25Z4.h"
#include "stdbool.h"

// LED RED is on PortB, Pin18
#define			LED_RED_GPIO_PORT			GPIOB
#define			LED_RED_PIN					18
#define			LED_RED_PIN_CTRL_REG		PORTB->PCR[LED_RED_PIN]

// LED GREEN is on PortB, Pin19
#define			LED_GREEN_GPIO_PORT			GPIOB
#define			LED_GREEN_PIN				19
#define			LED_GREEN_PIN_CTRL_REG		PORTB->PCR[LED_GREEN_PIN]

// LED BLUE is on PortD, Pin1
#define			LED_BLUE_GPIO_PORT			GPIOD
#define			LED_BLUE_PIN				1
#define			LED_BLUE_PIN_CTRL_REG		PORTD->PCR[LED_BLUE_PIN]


/**********************************************************************************************
 * function name: int1_signal_init()
 *
 * function description: initialize INT1 signal which is routed to PTA14
 *
 * parameter: none
 *
 * return value: none
 *********************************************************************************************/
void int1_signal_init();


/**********************************************************************************************
 * function name: board_move()
 *
 * function description: detect if board gets moved
 *
 * parameter: none
 *
 * return value: true for moved and false for not moved
 *********************************************************************************************/
bool board_move();

uint32_t get_ptairq_count();


#endif
