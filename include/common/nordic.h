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
 * @file nrf24.h
 * @brief GPIO init functions ECEN 5813 -- Project 3.
 *
 * This header file contains GPIO init functions for the Nordic NRF24 module,
 * as well as the SPI module on the FRDM-KL25Z.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date December 06, 2017
 *
 */

#ifndef NORDIC_H_
#define NORDIC_H_

#include "MKL25Z4.h"
#include "nrf24.h"

#define nrf_chip_enable() (GPIOD->PCOR |= 1<<0)
#define nrf_chip_disable() (GPIOD->PSOR |= 1<<0)
//#define nrf_transmit_enable() (!(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
//#define nrf_transmit_disable() (SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK)

/**
 * @brief function to read from NRF register
 *
 * This function reads a byte from a NRF24 register and returns it
 *
 * @param register number
 * @return byte read
 */
uint8_t nrf_read_register(uint8_t reg);

/**
 * @brief function to write to NRF register
 *
 * This function writes a byte to the NRF24 register specified
 *
 * @param register number, value to be written
 * @return none
 */
void nrf_write_register(uint8_t reg, uint8_t value);

/**
 * @brief function to read NRF status register
 *
 * This function reads a byte from the NRF24 status register
 *
 * @param none
 * @return byte read
 */
uint8_t nrf_read_status(void);

/**
 * @brief function to write to NRF config register
 *
 * This function writes a byte to the NRF24 config register
 *
 * @param configuration byte
 * @return none
 */
void nrf_write_config(uint8_t config);

/**
 * @brief function to read NRF config register
 *
 * This function reads data from the NRF24 config register
 *
 * @param void
 * @return byte read
 */
uint8_t nrf_read_config(void);

/**
 * @brief function to read NRF RF_SETUP register
 *
 * This function reads data from the NRF24 RF_SETUP register
 *
 * @param void
 * @return byte read
 */
uint8_t nrf_read_rf_setup(void);

/**
 * @brief function to write to NRF RF_SETUP register
 *
 * This function writes a byte to the NRF24 RF_SETUP register
 *
 * @param configuration byte
 * @return none
 */
void nrf_write_rf_setup(uint8_t config);

/**
 * @brief function to read NRF RF_CH register
 *
 * This function reads data from the NRF24 RF_CH register
 *
 * @param void
 * @return byte read
 */
uint8_t nrf_read_rf_ch(void);

/**
 * @brief function to write to NRF RF_CH register
 *
 * This function writes a byte to the NRF24 RF_CH register
 *
 * @param channel number
 * @return none
 */
void nrf_write_rf_ch(uint8_t channel);

/**
 * @brief function to read TX_ADDR register
 *
 * This function reads 5 bytes of data from the NRF24 TX_ADDR register
 *
 * @param pointer to TX_ADDR reg
 * @return none
 */
void nrf_read_tx_addr(uint8_t * tx_addr);

/**
 * @brief function to read TX_ADDR register
 *
 * This function writes 5 bytes of data to the NRF24 TX_ADDR register
 *
 * @param pointer to TX_ADDR reg
 * @return none
 */
void nrf_write_tx_addr(uint8_t * tx_addr);

/**
 * @brief function to read fifo status of the NRF24
 *
 * This function the status of the fifo queue of the NRF24.
 *
 * @param none
 * @return status byte
 */
uint8_t nrf_read_fifo_status(void);

/**
 * @brief function to flush TX fifo of the NRF24
 *
 * This function flushes the TX fifo queue of the NRF24.
 *
 * @param none
 * @return none
 */
void nrf_flush_tx_fifo(void);

/**
 * @brief function to flush RX fifo of the NRF24
 *
 * This function flushes the RX fifo queue of the NRF24.
 *
 * @param none
 * @return none
 */
void nrf_flush_rx_fifo(void);

#endif /*NORDIC_H_*/
