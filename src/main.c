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
 * This file contains a function that runs project1 if the flag is set
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 1, 2017
 *
 */

#include <stdint.h>
#include "project1.h"
#include "debug.h"

int main(void)
{
  /* Calls a compile time switch for project1 */
  #ifdef PROJECT1
    project1();
  #endif
  /* Calls a compile time switch for project2 */
  #ifdef PROJECT2
    project2();
  #endif
  return 0;
}
