/**************************************************************************************/
/* Author      : Ibrahim Diab                                                         */
/* File Name   : STK_interface.h                                                      */
/* Compiler	   : GCC , C99															  */
/* Target	   : STM32F10x - ARM cortex-M3										      */
/* Description : Interfacing macros for System Tick core peripheral for ARM CORTEX-M3 */
/**************************************************************************************/


#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


// Initialize the SysTick timer.
void STK_init(void);

// Set the SysTick timer to trigger periodic interrupts after a specified number of microseconds.
void STK_setIntervalPeriodic ( uint32 NoMicroSec );

// Stop the SysTick timer from generating interrupts.
void STK_stopInterval(void);

// Get the amount of time in microseconds that has elapsed since the last SysTick interrupt in ticks.
uint32 STK_getElapsedTime(void);

// Get the remaining time in microseconds until the next SysTick interrupt in ticks.
uint32 STK_getRemainingTime(void);



#endif // STK_INTERFACE_H
