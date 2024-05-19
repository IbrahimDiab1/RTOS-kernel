/*************************************************************************************/
/* Author      : Ibrahim Diab                                                        */
/* File Name   : STK_private.h                                                       */
/* Compiler	   : GCC , C99															  */
/* Target	   : STM32F10x - ARM cortex-M3										      */
/* Description : Private addresses for System Tick core peripheral for ARM CORTEX-M3 */
/*************************************************************************************/


#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H

typedef struct
{
    uint32 CTRL  ;
    uint32 LOAD  ;
    uint32 VAL   ;
    uint32 CALIB ;
}STK_t;

#define STK ((volatile STK_t *) 0xE000E010)

#define STK_AHB               0
#define STK_AHB_DIV8          1


#endif // STK_PRIVATE_H
