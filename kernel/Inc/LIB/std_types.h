/************************************************/
/* Author      : Ibrahim Diab                   */
/* File Name   : Std_Types.h                    */
/* Description : Common Standard types file     */
/************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#ifndef DISABLED
#define DISABLED    (0u)
#endif

#ifndef ENABLED
#define ENABLED     (1u)
#endif

#ifndef NULL
#define NULL        ((void*)0)
#endif

typedef uint8_t     boolean;    /*                FALSE .. TRUE                  */
typedef uint8_t     uint8;      /*                    0 .. 255                   */
typedef int8_t      int8;       /*                 -128 .. +127                  */
typedef uint16_t    uint16;     /*                    0 .. 65535                 */
typedef int16_t     int16;      /*               -32768 .. +32767                */
typedef uint32_t    uint32;     /*                    0 .. 4294967295            */
typedef int32_t     int32;      /*          -2147483648 .. +2147483647           */
typedef uint64_t    uint64;     /*                    0 .. 18446744073709551615  */
typedef int64_t     int64;      /* -9223372036854775808 .. 9223372036854775807   */
typedef float       float32;
typedef double      float64;

#endif  // STD_TYPES_H
