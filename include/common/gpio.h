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

#ifndef GPIO_H_
#define GPIO_H_

/**
 * @brief function to initialize GPIO
 *
 * This function initializes the GPIO pins for the Nordic NRF24 module,
 * as well as the SPI module on the FRDM-KL25Z.
 *
 * @param none
 * @return none
 */
void GPIO_nrf_init(void);
#endif /*GPIO_H_*/
