/**
 *******************************************************************************
 * File           : Task.h
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : STM32F10x - ARM cortex-M3
 * Brief          : Including APIs and interfaces of task management functions
 *******************************************************************************
 */
#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_


// Function pointer type for task functions
typedef void (*osFunc_t)(void);

// Enumeration representing the possible states of a task
typedef enum Task_State_t
{
    RUNNING,    // Task is currently executing
    READY,      // Task is ready to be executed
    BLOCKED,    // Task is blocked and waiting for an event to occur
    SUSPENDED,  // Task is suspended and temporarily inactive
    DELETED     // Task is deleted and no longer exists
} Task_State_t;


// Structure representing a task
typedef struct Task_t
{
    volatile osFunc_t task_func;    	 // Pointer to the task function
    volatile uint32 id;          		 // Task ID
    volatile uint32 priority;    		 // Task priority level
    volatile uint32 stackSize;   		 // Size of the task's stack
    volatile uint32 *psp;        		 // Pointer to the Process Stack Pointer (PSP)
    volatile Task_State_t state;   		 // Current state of the task
    volatile uint32 blockTicks;  		 // Number of ticks to delay task execution (if blocked)
    volatile char name[TASK_NAME_LEN];   // Name of the task
} Task_t;


// Define Enumeration for error codes
typedef enum {
    OS_TASK_SUCCESS = 0,    // Task creation successful
    OS_TASK_NULL_FUNC,      // Task function pointer is NULL
    OS_TASK_LONG_NAME,      // Task name exceeds maximum length
    OS_TASK_STACK_OVERFLOW  // Insufficient stack space
} OS_TaskError_t;


typedef Task_t* Task_Handler_t;


/* Function to create a new task in the operating system
 Parameters:
   - task_handler: Pointer to a task handler variable where the task control block pointer will be stored (optional)
   - task_func: Pointer to the task function to be executed by the new task
   - name: Name of the task
   - priority: Priority level of the task
   - stackSize: Size of the task's stack
 Returns:
   - OS_TaskError_t: Error code indicating the result of the task creation operation */
OS_TaskError_t OS_createTask(Task_Handler_t* task_handler, const osFunc_t task_func, const char* name, const uint32 priority, const uint32 stackSize);


// To introduce a delay in the execution of the current task
void os_delay(uint32 ticks);

// Suspend the specified task.
void os_suspendTask(Task_Handler_t taskhandler);

// Resume the specified suspended task.
void os_resumeTask(Task_Handler_t taskhandler);

// Delete the specified task for ever.
void os_deleteTask(Task_Handler_t taskhandler);




#endif /* KERNEL_TASK_H_ */
