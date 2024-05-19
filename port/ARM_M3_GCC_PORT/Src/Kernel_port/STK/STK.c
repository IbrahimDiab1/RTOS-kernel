/********************************************************************************************/
/* Author      : Ibrahim Diab                                                               */
/* File Name   : STK.c                                                                      */
/* Description : Functions Implementation for System Tick core peripheral for ARM CORTEX-m3 */
/********************************************************************************************/

#include <STM32F103x.h>

#include <../Inc/LIB/common_macros.h>
#include <../Inc/LIB/std_types.h>

#include <Kernel/port/STK/STK_config.h>
#include <Kernel/port/STK/STK_interface.h>
#include <Kernel/port/STK/STK_private.h>

#if MCU == STM32F103C6
#define CPU_INPUT_CLOCK RCC_AHB_CLK_FRQ
#endif

static volatile float32 microSecToTicksRatio = 0;


// Initialize the SysTick timer.
void STK_init ()
{
    // Set number of Ticks for one microsecond.
     microSecToTicksRatio = (float32)CPU_INPUT_CLOCK / 1000000;
     
    #if STK_CLOCK_PRESCALER == STK_AHB_DIV8
    microSecToTicksRatio = microSecToTicksRatio / 8;
    #endif 
    
    /*Enable SysTick*/
    STK->CTRL=0b1;

    /*Configure the SysTick timer with the selected Clock*/
    #if STK_CLOCK_PRESCALER == STK_AHB
    SET_BIT(STK->CTRL,2);
    #endif
    
}


// Set the SysTick timer to trigger periodic interrupts after a specified number of microseconds.
void STK_setIntervalPeriodic ( uint32 NoMicroSec )
{
    // Enable SYSTick.
    SET_BIT(STK->CTRL,0);

    // Enable Interrupt.
    SET_BIT(STK->CTRL,1);

    //Load number of ticks to Load Register.
    STK->LOAD = (NoMicroSec *microSecToTicksRatio);
    
}


// Stop the SysTick timer from generating interrupts.
void STK_stopInterval (void)
{
    /* Disable interrupt and Timer bins */
    STK->CTRL = 0;
    
    /* Clear the SysTick reload value */
    STK->LOAD = 0;
    
    /* Clear the SysTick current value */   
    STK->VAL  = 0;

}

// Get the amount of time that has elapsed since the last SysTick interrupt in microseconds.
uint32 STK_getElapsedTime(void)
{
    // Initialize ElapsedTime to 0.
    float32 ElapsedTime = 0;

    // Calculate the number of ticks that have elapsed.
    ElapsedTime = (STK->LOAD - STK->VAL);

    // Convert ticks to microseconds using the microSecToTicksRatio constant.
    ElapsedTime /= microSecToTicksRatio;

    // Return the elapsed time in microseconds.
    return (uint32)ElapsedTime;
}

// Get the remaining time until the next SysTick interrupt in microseconds.
uint32 STK_getRemainingTime(void)
{
    // Initialize RemainingTime to 0.
    float32 RemainingTime = 0;

    // Calculate the number of ticks remaining until the next interrupt.
    RemainingTime = STK->VAL;

    // Convert ticks to microseconds using the microSecToTicksRatio constant.
    RemainingTime /= microSecToTicksRatio;

    // Return the remaining time in microseconds.
    return (uint32)RemainingTime;
}


