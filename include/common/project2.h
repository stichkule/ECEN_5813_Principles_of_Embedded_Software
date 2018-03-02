/******************************************************************************
 * Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file project2.h
 * @brief This file is to be used with ECEN 5813 -- Project 2.
 *
 * This header file contains definitions for functions used in the file project2.c,
 * specifically calc_statistics() and dump_statistics().
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date October 29, 2017
 *
 */

#ifndef __PROJECT2_H__
#define __PROJECT2_H__

#include <stdint.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "uart.h"

extern uint8_t temp_rx;
extern uint8_t * temp_rx_ptr;
extern uint8_t temp_tx;
extern uint8_t * temp_tx_ptr;
extern CB_t * rx_buffer;
extern CB_t * tx_buffer;
extern uint8_t rx_rv_IRQ;
extern uint8_t tx_rv_IRQ;

/**
 * @brief function to calculate character counts
 *
 * This function takes in a pointer to a integer, classifies it in one of four categories --
 * Miscellaneous, Punctuations, Alphabets, and Numbers, and updates the corresponding
 * category count.
 *
 * @param pointer to integer, pointer to counter array
 * @return none
 */
void calc_statistics(int32_t * ptr, uint8_t * data_ptr);

/**
 * @brief function to dump character count statistics
 *
 * This function displays character count statistics on a terminal
 *
 * @param none
 * @return UART_status type
 */
void dump_statistics(void);

#endif /* __PROJECT2_H__ */

