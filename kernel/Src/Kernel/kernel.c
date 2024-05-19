/**
 ********************************************************************************************
 * File           : kernel.c
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : Portable
 * Brief          : Main kernel body implementation including functions.
 ********************************************************************************************
 */

#include <string.h>

#include <../Inc/LIB/std_types.h>
#include <../Inc/LIB/common_macros.h>

#include <../Inc/kernel/kernel_cfg.h>
#include <../Inc/kernel/kernel_interface.h>

#include "../../Inc/kernel/port/port.h"

#include "../../Inc/kernel/port/STK/STK_interface.h"
#include "../../Inc/kernel/Task.h"


extern Task_t Tasks[];
extern uint32 Current_Task, Task_counter;
volatile uint32 SysTick, App_Consumed_Stack = SCHEDULE_STACK_SIZE;


// Handler for the Idle Task
void IdleTask_Handler(void)
{
    // Infinite loop to keep the idle task running
    while (1);
}

void os_init()
{
    // Enable system faults if specified
#if SYSTEM_FAULTS == ENABLED
    enableSystemFaults();
#endif

    STK_init();

    // Check if the schedule stack start address is different from SRAM end address
#if SCHEDULE_STACK_START != SRAM_END
        // Initialize the schedule stack with the specified start address
        initScheduleStack(SCHEDULE_STACK_START);
#endif


    // Create the idle task
    (void)OS_createTask(NULL, &IdleTask_Handler, "IDLE_TASK", 0, 100);
}


// Function to check and unblock tasks that are waiting for a certain number of ticks
void checkBlockedTasks(void)
{

	for (uint32 i = 0; i < Task_counter; i++)
    {
        if (Tasks[i].state == BLOCKED)
        {
            // If the task's block ticks have elapsed, change its state to READY
            if (Tasks[i].blockTicks == SysTick)
                Tasks[i].state = READY;
        }
    }
}


// Function to perform task scheduling and determine the next task to run
void schedule()
{
    // Calculate the index of the next task in the task list
    uint32 nextTask = (Current_Task + 1) % Task_counter;

    // Perform task scheduling based on the selected scheduling algorithm from kernel_cfg.h
    #if SCHEDULE_ALGORITHM == ROUND_ROBIN

    // Iterate through the task list to find the next ready task in round-robin
    for (uint32 i = 0; i < Task_counter; i++, nextTask++)
    {
        // Wrap around the task index if it exceeds the number of tasks
        nextTask %= Task_counter;

        // Skip the task index 0 (the idle task), in case there are another ready tasks to execute
        if (!nextTask)
            continue;

        // Check if the next task is in the READY state
        if (Tasks[nextTask].state == READY)
        {
            // Update the current task to the next ready task
            Current_Task = nextTask;
            return;
        }
    }

    // If no ready task is found, set the current task to the idle task (index 0)
    Current_Task = 0;

    #endif
}



void os_start()
{
    // Set the interval of the SysTick timer for periodic interrupts
    // The interval is defined by the SYSTEM_TICK constant (kernel_cfg.h), converted to microseconds
    STK_setIntervalPeriodic(SYSTEM_TICK * 1000);

    // Execute the scheduling algorithm to determine the next task to run
    schedule();

    // Switch the processor mode to PSP (Process Stack Pointer) for task execution
    turnToPSP();

    // Execute the function associated with the current task
    Tasks[Current_Task].task_func();
}



