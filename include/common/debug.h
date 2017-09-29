/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.h 
 * @brief This file is to be used with ECEN 5813 -- Project 1.
 *
 * This header file contains a prototype for the print_memory() function
 * listed under the C-Programming Modules for Project 1. The corresponding
 * function definition is contained in the file "debug.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date September 28, 2017
 *
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

/**
 * @brief function to enable/disable debug printing
 * 
 * This function takes in a pointer to memory, along with a length parameter,
 * and prints out the hex values contained. The function should print as
 * normal in case the VERBOSE flag is enabled during complile time, but should
 * print nothing if this flag is disabled.
 *
 * @param pointer to start of memory location, length
 * @return void
 */
void print_memory(uint8_t* start, uint32_t length);

#endif /* __DEBUG_H__ */
