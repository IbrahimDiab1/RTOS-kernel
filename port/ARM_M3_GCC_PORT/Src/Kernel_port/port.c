/**
 ************************************************************************
 * File           : port.c
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : STM32F10x - ARM cortex-M3
 * Brief          : Functions specific to target in the kernel.
 ************************************************************************
 */

#include <../Inc/LIB/std_types.h>
#include <../Inc/LIB/common_macros.h>

#include <Kernel/port/port.h>
#include <Kernel/Task.h>


extern Task_t Tasks[];
extern uint32 Current_Task, SysTick;


void NAKED initScheduleStack(uint32 scheduleStackAddress)
{
    __asm__ volatile
	(
        "MSR MSP, R0  \n"  // Move the value in R0 (function parameter) to the main stack pointer (MSP)
        "BX LR"            // Branch to the address in the link register (LR), returning from the function
    );

}


// Function to initialize the stack for a new task
void initTaskStack(Task_t *taskHandler)
{
    // Decrement the stack pointer (Full Descending Stack) and set the initial xPSR value
    (taskHandler->psp)--;
    *(taskHandler->psp) = DUMMY_XPSR;

    // Decrement the stack pointer and set the initial program counter (PC) to the task's function
    (taskHandler->psp)--;
    *(taskHandler->psp) = (uint32)taskHandler->task_func;

    // Decrement the stack pointer and set the link register (LR) with a dummy value
    (taskHandler->psp)--;
    *(taskHandler->psp) = DUMMY_LR;

    // Decrement the stack pointer and initialize R4-R11 and other general-purpose registers to 0
    for (uint8 i = 0; i < 13; i++)
    {
        (taskHandler->psp)--;
        *(taskHandler->psp) = 0;
    }
}


void NAKED saveContext(void)
{
	__asm__ volatile
	(
	    "MRS R0, PSP         \n"    // Move PSP (Process Stack Pointer) to R0
	    "STMDB R0!, {R4-R11} \n"    // Store multiple registers (R4-R11) onto the stack, decrementing the stack pointer
	    "PUSH {LR}           \n"    // Save the link register (LR) onto the stack
	    "BL setTaskPSP       \n"    // Branch and link to setTaskPSP function
	    "POP {LR}            \n"    // Restore the link register (LR) from the stack
	    "BX LR"                     // Branch to the address in the link register (return)
	);
}


void NAKED retrieveContext(void)
{
	__asm__ volatile
	(
	    "PUSH {LR}           \n"    // Save the link register (LR) onto the stack
	    "BL getTaskPSP       \n"    // Branch and link to getTaskPSP function
	    "LDM R0!, {R4-R11}   \n"    // Load multiple registers (R4-R11) from the stack into R0, incrementing the stack pointer
	    "MSR PSP, R0         \n"    // Move the value in R0 to the Process Stack Pointer (PSP)
	    "POP {LR}            \n"    // Restore the link register (LR) from the stack
	    "BX LR"                     // Branch to the address in the link register (return)
	);
}

void NAKED turnToPSP(void)
{
	__asm__ volatile
	(
	    "PUSH {LR}           \n"    // Save the link register (LR) onto the stack
	    "BL getTaskPSP       \n"    // Branch and link to getTaskPSP function
	    "POP {LR}            \n"    // Restore the link register (LR) from the stack
	    "MSR PSP, R0         \n"    // Move the value in R0 to the Process Stack Pointer (PSP)
	    "MOV R0, #0x02       \n"    // Move the value 0x02 to R0
	    "MSR CONTROL, R0     \n"    // Move the value in R0 to the CONTROL register
	    "BX LR"                     // Branch to the address in the link register (return)
	);
}

void NAKED PendSV_Handler(void)
{
	__asm__ volatile
	(
	    "PUSH {LR}             \n"    // Save the link register (return address)
	    "BL saveContext        \n"    // Branch and link to saveContext function
	    "BL schedule           \n"    // Branch and link to schedule function
	    "BL retrieveContext    \n"    // Branch and link to retrieveContext function
	    "POP {LR}              \n"    // Restore the link register (return address)
	    "BX LR"                       // Return from function
	);
}

void SysTick_Handler(void)
{
    // Increment SysTick counter for scheduling purposes
    SysTick++;

    // Check and handle blocked tasks if any
    checkBlockedTasks();

    // Enable PendSV interrupt to trigger context switch
    enablePENDSV();
}


uint32* getTaskPSP()
{
	return Tasks[Current_Task].psp;
}


void setTaskPSP(uint32* psp)
{
	Tasks[Current_Task].psp = psp;
}



void enableSystemFaults(void)
{
    // to enable system fault exceptions (usage faults, bus faults, and memory faults)
    MOD_3BIT(SHCSR, 16, 0b111);
}









