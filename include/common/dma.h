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
 * @file dma.h
 * @brief This file is to be used with ECEN 5813 -- Project 3.
 *
 * This header file contains function prototypes for the DMA initialization
 * functions, and the DMA IRQ handler. Also defined is a typedef
 * enum to indicate the status of the DMA operation. Prototypes and definitions of the
 * functions making use of the DMA for data transfer are included in the memory.h, and
 * memory.c files, respectively. The corresponding function definitions are contained
 * in the file "dma.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date November 20, 2017
 *
 */

#include <stddef.h>

#ifndef __DMA_H__
#define __DMA_H__

/** This typedef defines a data type DMA_status, to represent an enum corresponding
 * to the status of the DMA operation.
 * The status codes contained in the enum are:
 * DMA_FAILED -- failure
 * DMA_SUCCESS -- success
 */
typedef enum
{
  DMA_FAILED = -1,
  DMA_SUCCESS
}DMA_status;

/**
 * @brief function to configure DMA for memmove
 *
 * This function configures the DMA for memmove functionality
 * on the FRDM-KL25Z according to settings provided in the writeup for project 3.
 *
 * @param source pointer, destination pointer, no. of bytes to be transferred, transfer size in bytes
 * @return DMA_status -- failed or success
 */
DMA_status DMA_configure_memmove(uint8_t* src, uint8_t* dst, size_t length, uint8_t transfer_size);

/**
 * @brief function to configure DMA for memzero
 *
 * This function configures the DMA for memzero functionality
 * on the FRDM-KL25Z according to settings provided in the writeup for project 3.
 *
 * @param source pointer, no. of locations to be zeroed, transfer size in bytes
 * @return DMA_status -- failed or success
 */
DMA_status DMA_configure_memzero(uint8_t* src_zero, uint8_t* dst, size_t length, uint8_t transfer_size);

/**
 * @brief IRQ handler for the UART
 *
 * This function handles transmit and receive interrupts for the UART.
 * It clears the interrupt flag (if set) for either transmit or receive interrupts.
 *
 * @param none
 * @return none
 */
void DMA0_IRQHandler(void);

#endif /* __DMA_H__ */

