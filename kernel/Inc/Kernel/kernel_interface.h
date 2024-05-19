/**
 ************************************************************************
 * File           : kernel_interface.h
 * Author         : Ibrahim Diab
 * Compiler		  : GCC , C99
 * Target		  : Portable
 * Brief          : Main header for kernel APIs.
 ************************************************************************
 */
 
#ifndef _KERNEL_INTERFACE_H_
#define _KERNEL_INTERFACE_H_

#include <../Inc/LIB/std_types.h>
#include <../Inc/LIB/common_macros.h>

#include "kernel_cfg.h"


void  os_init();

void  os_start();
 
 
#endif //_KERNEL_INTERFACE_H_
