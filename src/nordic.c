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
#include "nordic.h"
#include "nrf24.h"
#include "spi.h"

uint8_t nrf_read_register(uint8_t reg)
{
	uint8_t rv_read=9;
	nrf_chip_enable();
	reg = R_REGISTER | reg;
	rv_read=SPI_write_byte(reg);
		rv_read = SPI_write_byte(NOP);
		rv_read = SPI_write_byte(NOP);
		//rv_read = SPI_write_byte(NOP);
		rv_read = SPI0_D;
	nrf_chip_disable();
	return rv_read;
}

void nrf_write_register(uint8_t reg, uint8_t value)
{
	nrf_chip_enable();
	reg = W_REGISTER | reg;
	SPI_write_byte(reg);
	SPI_write_byte(value);
	//status = nrf_read_status();
	//SPI_read_byte();
	nrf_chip_disable();
}
uint8_t nrf_read_status(void)
{
	//nrf_chip_enable();
	uint8_t rv;
	rv = nrf_read_register(STATUS);
	return rv;
}

void nrf_write_config(uint8_t config)
{
	nrf_write_register(CONFIG, config);
}

uint8_t nrf_read_config(void)
{
	return nrf_read_register(CONFIG);
}

uint8_t nrf_read_rf_setup(void)
{
   return nrf_read_register(RF_SETUP);
}

void nrf_write_rf_setup(uint8_t config)
{
	nrf_write_register(RF_SETUP, config);
}

uint8_t nrf_read_rf_ch(void)
{
	return nrf_read_register(RF_CH);
}

void nrf_write_rf_ch(uint8_t channel)
{
	nrf_write_register(RF_CH, channel);
}

void nrf_read_tx_addr(uint8_t * tx_addr)
{
	//uint8_t status;
	nrf_chip_enable();
	uint8_t reg = (R_REGISTER|TX_ADDR);
	SPI_write_byte(reg);
	//SPI_write_byte(NOP);
	for(uint8_t i=0;i<5;i++)
	{
		SPI_write_byte(NOP);
		*(tx_addr+i) = SPI0_D;
	}
	nrf_chip_disable();
}

void nrf_write_tx_addr(uint8_t * tx_addr)
{
	//uint8_t status;
	nrf_chip_enable();
	uint8_t reg = (TX_ADDR|W_REGISTER);
	SPI_write_byte(reg);
	for(uint8_t i=0;i<5;i++)
	{
		SPI_write_byte(*(tx_addr+i));
	}
	nrf_chip_disable();
}

uint8_t nrf_read_fifo_status(void)
{
	return nrf_read_register(FIFO_STATUS);
}

void nrf_flush_tx_fifo(void)
{
	nrf_chip_enable();
	SPI_write_byte(FLUSH_TX);
	nrf_chip_disable();
}

void nrf_flush_rx_fifo(void)
{
	nrf_chip_enable();
	SPI_write_byte(FLUSH_RX);
	nrf_chip_disable();
}
