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
 * @file uart.h 
 * @brief This file is to be used with ECEN 5813 -- Project 2.
 *
 * This header file contains UART funtion prototypes. Functionalities include 
 * configuring, transmitting and receiving data, and handling interrupts for the  
 * UART on the FRDM-KL25Z board. The corresponding function definitions are  
 * contained in the file "uart.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date October 25, 2017
 *
 */

#ifndef __UART_H__
#define __UART_H__

/** This typedef defines a data type UART_status, to represent an enum corresponding
 * to the status of the UART operation.
 * The status codes contained in the enum are:
 * UART_FAILED -- failure
 * UART_SUCCESS -- success
 */
typedef enum
{
  UART_FAILED = -1,
  UART_SUCCESS
}UART_status;

/**
 * @brief function to configure UART
 * 
 * This function configures the UART on the FRDM-KL25Z according to settings provided
 * in the writeup for project 2.
 *
 * @param none
 * @return UART_status -- failed or success
 */
void UART_configure(void);

/**
 * @brief function to transmit single data byte through the UART
 * 
 * This function sends a single byte of data through the UART. 
 * This function blocks on trasmitting data.
 *
 * @param pointer to data being transmitted
 * @return none
 */
UART_status UART_send(uint8_t * data);

/**
 * @brief function to transmit stream of data bytes through the UART
 * 
 * This function sends multiple bytes of data through the UART. 
 * This function blocks on trasmitting data.
 *
 * @param pointer to data being transmitted, length
 * @return UART_status -- failed or success
 */
UART_status UART_send_n(uint8_t * data, uint16_t length);

/**
 * @brief function to receive single data byte through the UART
 * 
 * This function receives a single byte of data through the UART. 
 * This function blocks until a character has been received.
 *
 * @param pointer to data being received
 * @return UART_status -- failed or success
 */
UART_status UART_receive(uint8_t * data);

/**
 * @brief function to receive stream of data bytes through the UART
 * 
 * This function receives multiple bytes of data through the UART. 
 * This function blocks until requisite number of characters have been received.
 *
 * @param pointer to data being received, length
 * @return UART_status -- failed or success
 */
UART_status UART_receive_n(uint8_t * data, uint16_t length);

/**
 * @brief IRQ handler for the UART
 * 
 * This function handles transmit and receive interrupts for the UART. 
 * It clears the interrupt flag (if set) for either transmit or receive interrupts.
 *
 * @param none
 * @return none
 */
void UART0_IRQHandler(void);

#endif /* __UART_H__ */
