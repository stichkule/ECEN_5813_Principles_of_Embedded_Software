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
#include "core_cm0plus.h"
#include "nrf24.h"


void SPI_init(void)
{
	SPI0_C1 = 0x50;
	//SPI0_C1 |= SPI_C1_MSTR_MASK;
	//SPI0_C1 |= SPI_C1_SPE_MASK;
	SPI0_C2 |= SPI_C2_MODFEN_MASK;
	// Clear CPOL and CPHA
	//SPI0_C1 &= (SPI_C1_CPOL_MASK);
	//SPI0_C1 &= ~(SPI_C1_CPHA_MASK);
	// pre-scaler of 1, BR divisor of 2
	SPI_BR_REG(SPI0) = 0x00;
}

uint8_t SPI_read_byte(void)
{
	uint8_t byte;
	while(!(SPI0_S & SPI_S_SPRF_MASK)); // Wait until data received in SPI RX buffer
	//SPI0_D = NOP;
	//SPI_flush();
	byte = SPI0_D;
	return byte;
}

uint8_t SPI_write_byte(uint8_t byte)
{
	while(!(SPI0_S & SPI_S_SPTEF_MASK));
	SPI0_D = byte;
	uint8_t rv = SPI0_D;
	return rv;
	//SPI_flush();
}

void SPI_send_packet(uint8_t * p, size_t length)
{
	//SPI_flush();
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
	while(WAIT_SPRF){}; // Block until SPI TX buffer completes transmitting
}
