/**
 ************************************************************************
 * File           : kernel_cfg.h
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : Portable
 * Brief          : Main header for kernel configurations.
 ************************************************************************
 */

#ifndef KERNEL_CFG_H_
#define KERNEL_CFG_H_


#define SCHEDULE_ALGORITHM          ROUND_ROBIN

#define SYSTEM_TICK                 1           // 1 Millisecond

#define MAX_TASKS                   10          // Preferred to specify the actual number of tasks for memory efficiency

#define SCHEDULE_STACK_SIZE         1024        // 1024 bytes

#define DEFAULT_TASK_STACK_SIZE     1024        // 1024 bytes

// Define the total application stack size in bytes
#define APP_STACK_SIZE              16384       // 16 kB,  Note: Must be less than or equal to the MCU stack memory size

#define TASK_NAME_LEN               12          // 12 characters

// Define whether system faults are enabled or disabled
#define SYSTEM_FAULTS               ENABLED

// Define the start address of the schedule stack
#define SCHEDULE_STACK_START        SRAM_END    // Start address of the schedule stack (assuming it starts at the end of SRAM)



#endif /* KERNEL_CFG_H_ */
