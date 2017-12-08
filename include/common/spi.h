/******************************************************************************
 * Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. The authors and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file spi.h
 * @brief SPI functions ECEN 5813 -- Project 3.
 *
 * This header file contains SPI functions that interface the Nordic NRF24 module,
 * with the FRDM-KL25Z.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date December 06, 2017
 *
 */

#ifndef SPI_H_
#define SPI_H_

#include <stddef.h>

#define WAIT_SPTEF (!(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_SPRF (!(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))

/**
 * @brief function to initialize GPIO
 *
 * This function initializes the GPIO pins for the Nordic NRF24 module,
 * as well as the SPI module on the FRDM-KL25Z.
 *
 * @param none
 * @return none
 */
void SPI_init(void);

/**
 * @brief function to read byte from SPI
 *
 * This function reads a single byte from the SPI bus
 *
 * @param byte to read into
 * @return none
 */
void SPI_read_byte(uint8_t byte);

/**
 * @brief function to write byte to SPI
 *
 * This function sends a single byte onto the SPI bus
 *
 * @param byte to be written
 * @return none
 */
void SPI_write_byte(uint8_t byte);

/**
 * @brief function to send a packet of bytes over SPI
 *
 * This function sends a packet of multiple bytes onto the SPI bus
 *
 * @param byte pointer, no. of bytes to send
 * @return none
 */
void SPI_send_packet(uint8_t * p, size_t length);

/**
 * @brief function to block on SPI transmit
 *
 * This function blocks until the SPI buffer has completed transmitting
 *
 * @param none
 * @return none
 */
void SPI_flush(void);

#endif /*SPI_H_*/
