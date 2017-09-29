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
 * This header file contains prototypes for the memory manipulation functions
 * listed under the C-Programming Modules for Project 1. The corresponding
 * function definitions are contained in the file "memory.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date September 28, 2017
 *
 */

#ifndef __MEMORY_H__
#define __MEMORY_H__

/**
 * @brief function to move data from source location to destination
 * 
 * This function takes in source and destination pointers, along with a length 
 * parameter, to move data from the source to the destination. It should be 
 * able to handle cases where source and destination memory areas overlap, and
 * also copy data without any corruption.
 *
 * @param source pointer, destination pointer, length
 *
 * @return pointer to destination
 */
uint8_t* my_memmove(uint8_t* src, uint8_t* dst, ​size_t ​length);

/**
 * @brief function to copy data from source location to destination
 * 
 * This function takes in source and destination pointers, along with a length 
 * parameter, to copy data from the source to the destination. In cases where 
 * source and destination memory areas overlap, the behavior is undefined, and
 * although the copy should occur, data will likely be corrupted.
 *
 * @param source pointer, destination pointer, length
 *
 * @return pointer to destination
 */
uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, size_t length);

/**
 * @brief function to set memory locations to a certain value
 * 
 * This function takes in a source pointer, a length parameter, and
 * sets corresponding memory locations to a certain value.
 *
 * @param source pointer, length, value
 * 
 * @return pointer to the source
 */
int8_t* my_memset(uint8_t* src, size_t length, uint8_t value);

/**
 * @brief function to set memory locations to zero
 * 
 * This function takes in a source pointer, a length parameter, and
 * sets corresponding memory locations to zero.
 *
 * @param source pointer, length
 *
 * @return pointer to the source
 */
uint8_t* my_memzero(uint8_t* src, size_t length);

/**
 * @brief function to reverse order of bytes in memory
 * 
 * This function takes in a source pointer, a length parameter, and
 * reverses the order of all the bytes.
 *
 * @param source pointer, length
 *
 * @return pointer to the source
 */
uint8_t* my_reverse(uint8_t* src, size_t length);

/**
 * @brief function to allocate memory
 * 
 * This function allocates the designated number of words in dynamic memory.
 *
 * @param length
 *
 * @return pointer to start of allocated memory
 */
int32_t* reserve_words(size_t length);

/**
 * @brief function to free memory
 * 
 * This function frees up a dynamic memory allocation using a source pointer.
 *
 * @param source pointer
 *
 * @return void
 */
void free_words(int32_t* src);

#endif /* __MEMORY_H__ */
