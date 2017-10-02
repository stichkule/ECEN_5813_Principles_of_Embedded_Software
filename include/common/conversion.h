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
 * @file conversion.h 
 * @brief This file is to be used with ECEN 5813 -- Project 1.
 *
 * This header file contains prototypes for basic data manipulation functions
 * listed under the C-Programming Modules for Project 1. The corresponding
 * function definitions are contained in the file "conversion.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date September 28, 2017
 *
 */

#ifndef __CONVERSION_H__
#define __CONVERSION_H__

/**
 * @brief function to convert data from standard integer type to ASCII string
 * 
 * This function takes in a signed 32-bit integer, converts it to a string
 * including the sign (if negative), and returns the pointer. Bases range from 
 * 2 to 16.
 *
 * @param integer data, pointer to string, base
 *
 * @return size of converted ASCII string
 */
uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base);

/**
 * @brief function to convert ASCII string to integer type
 * 
 * This function takes in a string pointer, number of digits in the character
 * set, and the base, and converts the ASCII string to an integer. It should
 * support bases 2 through 16, and also be able to handle signed data.
 *
 * @param pointer to string, number of digits, base
 *
 * @return integer converted from ASCII string
 */
uint8_t my_atoi(uint8_t* ptr, uint8_t digits, uint32_t base);

/**
 * @brief function to convert data from big endian to little endian
 * 
 * This function takes in a source pointer, a length parameter, and
 * converts that data from big endian to little endian representation.
 * It must return an error if the conversion fails for any reason.
 *
 * @param pointer to memory, length
 *
 * @return error code
 */
int8_t big_to_little32(uint32_t* data, uint32_t length);

/**
 * @brief function to convert data from little endian to big endian
 * 
 * This function takes in a source pointer, a length parameter, and
 * converts that data from little endian to big endian representation.
 * It must return an error if the conversion fails for any reason.
 *
 * @param pointer to memory, length
 *
 * @return error code
 */
int8_t little_to_big32(uint32_t* data, uint32_t length);


#endif /* __CONVERSION_H__ */
