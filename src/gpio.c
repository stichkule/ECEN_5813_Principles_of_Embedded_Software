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
 * @file gpio.c
 * @brief GPIO function definitions for project 3.
 * This file implements functions to configure GPIO pins for SPI communication
 * with the Nordic NRF24 device.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date December 06, 2017
 *
 */

#include "MKL25Z4.h"
#include "gpio.h"

void GPIO_nrf_init(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; // Set up port D for SPI0 and clock it
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK; // Turn on SPI0 clock

    PORTD->PCR[0] |= PORT_PCR_MUX(1); // GPIO pin for CS
    PORTD->PCR[1] |= PORT_PCR_MUX(2); // SCK
    PORTD->PCR[2] |= PORT_PCR_MUX(2); // MOSI
    PORTD->PCR[3] |= PORT_PCR_MUX(2); // MISO
    PTD_BASE_PTR->PDDR |= 1<<0; // Set data direction to output
}
