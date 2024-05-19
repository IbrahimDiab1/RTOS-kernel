/*********************************************************************************/
/* Author      : Ibrahim Diab                                                    */
/* File Name   : STK_config.h                                                    */
/* Compiler	   : GCC , C99															  */
/* Target	   : STM32F10x - ARM cortex-M3										      */
/* Description : Configuration for System Tick core peripheral for ARM CORTEX-M3 */
/*********************************************************************************/


#ifndef STK_CONFIG_H
#define STK_CONFIG_H



/*
[Must]
Options: 
         STK_AHB_DIV8 // clock input: AHB/8
         STK_AHB      // clock input: AHB
*/
#define STK_CLOCK_PRESCALER  STK_AHB_DIV8

#endif // STK_CONFIG_H
