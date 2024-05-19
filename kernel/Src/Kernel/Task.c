/**
 ******************************************************************************
 * File           : Task.c
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : STM32F10x - ARM cortex-M3
 * Brief          : Implementation of task management functions for kernel
 ******************************************************************************
 */
#include <string.h>

#include <../Inc/LIB/std_types.h>
#include <../Inc/LIB/common_macros.h>

#include "../Inc/kernel/kernel_cfg.h"
#include "../../Inc/kernel/port/port.h"
#include "../../Inc/Kernel/Task.h"


extern uint32 SysTick, App_Consumed_Stack;

volatile Task_t Tasks[MAX_TASKS+1];

volatile uint32 Current_Task, Task_counter;


/* Function to create a new task in the operating system
 Parameters:
   - task_handler: Pointer to a task handler variable where the task control block pointer will be stored (optional)
   - task_func: Pointer to the task function to be executed by the new task
   - name: Name of the task
   - priority: Priority level of the task
   - stackSize: Size of the task's stack
 Returns:
   - OS_TaskError_t: Error code indicating the result of the task creation operation */
OS_TaskError_t OS_createTask(Task_Handler_t* task_handler, const osFunc_t task_func, const char* name, const uint32 priority, const uint32 stackSize)
{
    // Error handling: Check if the task function pointer is NULL
    if (task_func == NULL)
        return OS_TASK_NULL_FUNC;

    // Error handling: Check if the task name exceeds the maximum length
    if (strlen(name) > TASK_NAME_LEN)
        return OS_TASK_LONG_NAME;

    // Error handling: Check if there is sufficient stack space available
    if ((stackSize + App_Consumed_Stack) > (APP_STACK_SIZE - App_Consumed_Stack))
        return OS_TASK_STACK_OVERFLOW;

    // Copy the task name into the task control block
    for (uint8 i = 0; i < TASK_NAME_LEN; i++)
        Tasks[Task_counter].name[i] = name[i];

    // Initialize task control block fields
    Tasks[Task_counter].task_func = task_func;
    Tasks[Task_counter].priority  = priority;
    Tasks[Task_counter].psp       = (uint32*)(SRAM_END - App_Consumed_Stack);
    Tasks[Task_counter].id		  = Task_counter;
    Tasks[Task_counter].stackSize = stackSize;
    Tasks[Task_counter].state     = READY;

    // Initialize task stack
    initTaskStack(&Tasks[Task_counter]);

    // Update consumed stack size and task counter
    App_Consumed_Stack += stackSize;
    ++Task_counter;

    // If task_handler pointer is provided, store the task control block pointer
    if (task_handler != NULL)
        *task_handler = &Tasks[Task_counter];

    // Return success
    return OS_TASK_SUCCESS;
}


// To introduce a delay in the execution of the current task
void os_delay(uint32 ticks)
{
	DISABLE_INTERRUPTS();  // Enter critical section

    // Set the state of the current task to BLOCKED
    // This indicates that the task is blocked and should not be scheduled until the delay expires
    Tasks[Current_Task].state = BLOCKED;

    // Calculate the future tick value when the task will be unblocked
    // by adding the current SysTick value with the delay duration
    Tasks[Current_Task].blockTicks = SysTick + ticks;

    ENABLE_INTERRUPTS();	// Exit from critical section

    // Enable PendSV interrupt to trigger context switch
    enablePENDSV();
}

void os_suspendTask(Task_Handler_t taskhandler)
{
    if (taskhandler != NULL)
    	if(taskhandler->state != DELETED)
    		taskhandler->state = SUSPENDED;
}

void os_resumeTask(Task_Handler_t taskhandler)
{
    if (taskhandler != NULL)
    {
    	if(taskhandler->state == SUSPENDED)
    	{
    		if(taskhandler->blockTicks <SysTick)
    			taskhandler->state = READY;
    		else
    			taskhandler->state = BLOCKED;
    	}
    }
}

void os_deleteTask(Task_Handler_t taskhandler)
{
    if (taskhandler != NULL)
    	taskhandler->state = DELETED;
}


