/*******************************************/
/* Author      : Ibrahim Diab              */
/* File Name   : Common_Macros.h           */
/* Description : Commonly used Macros      */
/*******************************************/

#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

// Set a certain bit in any register.
#define SET_BIT(REG,BIT)             (REG |= (1<<BIT))

// Clear a certain bit in any register.
#define CLR_BIT(REG,BIT)             (REG &= ~(1<<BIT))

// Read the value of a certain bit in any register.
#define GET_BIT(REG,BIT)             ((REG & (1<<BIT))>>BIT)

// Toggle a certain bit in any register.
#define TOG_BIT(REG,BIT)             (REG ^= (1<<BIT))

// Rotate right a certain register value with specific number of rotates.
#define ROR(REG,NUM)                 (REG = (REG>>NUM | REG<<((sizeof(REG)*8)-NUM)))

// Rotate left a certain register value with specific number of rotates.
#define ROL(REG,NUM)                 (REG = (REG<<NUM | REG>>((sizeof(REG)*8)-NUM)))

// Modify a 2-bit field in a register starting at bit position FIELD
#define MOD_2BIT(REG, FIELD, VAL)    (REG = (REG &  ~(0x3 << FIELD) ) | (VAL<<FIELD))

// Modify a 3-bit field in a register starting at bit position FIELD
#define MOD_3BIT(REG, FIELD, VAL)    (REG = (REG &  ~(0x7 << FIELD) ) | (VAL<<FIELD))

// Modify a 4-bit field in a register starting at bit position FIELD
#define MOD_4BIT(REG, FIELD, VAL)    (REG = (REG &  ~(0xf << FIELD) ) | (VAL<<FIELD))

// Modify a 8-bit field in a register starting at bit position FIELD
#define MOD_8BIT(REG, FIELD, VAL)    (REG = (REG &  ~(0xff<< FIELD) ) | (VAL<<FIELD))

// Modify a N-bit field in a register starting at bit position FIELD
#define MOD_NBIT(REG, FIELD, N, VAL) (REG = (REG & ~(((1<<N)-1)<<FIELD))|((VAL &(((1<<N)-1)))<<FIELD))

// Read the value of a certain N bits in any register.
#define GET_NBIT(REG, FIELD, N)      ((REG>>FIELD)&(1<<(N-1)))


#ifdef __GNUC__

// Define the naked attribute
#define NAKED		  __attribute__((naked))

// Define the section attribute for placing functions in a specific section
#define SECTION(name) __attribute__((section(name)))

#endif


#endif // COMMON_MACROS_H
