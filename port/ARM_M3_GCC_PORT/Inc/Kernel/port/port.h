/**
 ********************************************************************************************
 * File           : port.h
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : STM32F10x - ARM cortex-M3
 * Brief          : Main header for kernel port APIs related to the specific target.
 ********************************************************************************************
 */

#ifndef _PORT_H_
#define _PORT_H_

#include "../../LIB/std_types.h"

#include "../kernel_interface.h"
#include "../Task.h"

#ifndef SHCSR
#define SHCSR		    		 (*(volatile uint32*)0xE000ED24)
#endif

#ifndef ICSR
#define ICSR					 (*(volatile uint32*)0xE000ED04)
#endif

#ifndef SRAM_END
#define SRAM_END				 ( 0x20000000 + (1024 * 20) )
#endif


#define DUMMY_XPSR				 (0x01000000)
#define DUMMY_LR				 (0xFFFFFFFD)


#define DISABLE_INTERRUPTS() 	 do{ __asm__ volatile ("cpsid i"); } while(0)
#define ENABLE_INTERRUPTS()  	 do{ __asm__ volatile ("cpsie i"); } while(0)

#define enablePENDSV()		     SET_BIT(ICSR,28)



void initTaskStack( Task_t *taskHandler);

void NAKED initScheduleStack(uint32 scheduleStackAddress);

void NAKED saveContext(void);

void NAKED retrieveContext(void);

void NAKED turnToPSP(void);

void savePSP(uint32* psp);

void enableSystemFaults(void);

uint32* getCurrentTaskPSP();

uint32* getNextTaskPSP();







#endif // _PORT_H_
