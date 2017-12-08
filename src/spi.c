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
 * @file spi.c
 * @brief SPI function definitions for project 3.
 * This file implements functions to initialize the SPI module on the KL25Z.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date December 06, 2017
 *
 */

#include "MKL25Z4.h"
#include "spi.h"


void SPI_init(void)
{
	SPI0_C1 = SPI_C1_MSTR_MASK | SPI_C1_SPE_MASK; // Check CPOL CPHA
	// Check BUS_CLK, pre-scaler, BR divisor
	SPI_BR_REG(SPI0) = 0x03;
}

void SPI_read_byte(uint8_t byte)
{
	while(WAIT_SPRF); // Wait until data received in SPI RX buffer
	byte = SPI0_D;
}

void SPI_write_byte(uint8_t byte)
{
	SPI_flush();
	SPI0_D = byte;
}

void SPI_send_packet(uint8_t * p, size_t length)
{
	SPI_flush();
	while(length>0)
	{
		SPI_flush();
		SPI0_D = *(p);
		p++;
		length--;
	}
}

void SPI_flush(void)
{
	while(WAIT_SPTEF){}; // Block until SPI TX buffer completes transmitting
}
