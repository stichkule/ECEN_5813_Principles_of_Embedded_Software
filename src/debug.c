/******************************************************************************
 * Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Shiril Tichkule, Kyle Harlow, and the University of Colorado are 
 * not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file debug.c 
 * @brief Print memory function definition for project 1.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 1, 2017
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "debug.h"

void print_memory(uint8_t * start, uint32_t length){
	uint32_t i;
	for(i=0; i < length; i++){
		printf("Location %d, Value %x\n", i, *(start+i));
	}
}
