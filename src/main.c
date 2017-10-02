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
 * @file main.c 
 * @brief Main function for project 1.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 1, 2017
 *
 */

#include <stdint.h>
#include "project1.h"
#include "conversion.h"
#include "memory.h"
#include "debug.h"
#include "platform.h"

int main(void){
  #ifdef PROJECT1
	course1();
  #endif
  return 0;
}
