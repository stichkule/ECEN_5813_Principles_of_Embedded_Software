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
 * @file uart.c
 * @brief UART setup and functions for project 2.
 * This file is used to setup and configure UART0 on the FRDM-KL25Z. It also
 * implements send and receive functions that are called by the UART0_IRQHandler.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 29, 2017
 *
 */

#include <stdint.h>

#define CLOCK_SETUP (0)

#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "project2.h"
#include "circular_buffer.h"
#include "uart.h"
#include "led.h"
#include "project3.h"
#include "logger.h"
#include "logger_queue.h"

/* Clock and Baud calculation macros */
#define BAUD_RATE 38400
#define OSR 0x0F
#define BUS_CLK ((DEFAULT_SYSTEM_CLOCK)/(((SYSTEM_SIM_CLKDIV1_VALUE&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+0x1))
#define BAUD_RATE_DIV ((BUS_CLK)/((OSR+1)*BAUD_RATE))
#define BAUD_RATE_DIV_H ((BAUD_RATE_DIV>>8)&UART0_BDH_SBR_MASK)
#define BAUD_RATE_DIV_L ((BAUD_RATE_DIV&UART0_BDL_SBR_MASK))

/**
 * @brief function to configure UART
 *
 * This function configures the UART on the FRDM-KL25Z according to settings provided
 * in the writeup for project 2.
 *
 * @param none
 * @return UART_status -- failed or success
 */

void UART_configure(void)
{
  /* Set clock source */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0x1);

  SIM->SCGC4 |= SIM_SCGC4_UART0(1);

  /* Enable Port A clock */
  SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

  /* Enable UART0 pins to Alternative Pin 2 */
  PORTA->PCR[1] = PORT_PCR_MUX(0x2);
  PORTA->PCR[2] = PORT_PCR_MUX(0x2);

  /* Disable Transmit and Receive during configuration */
  UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

  /* Set high and low bits of the SBR (Baud rate clock divider) */
  UART0->BDH |= UART0_BDH_SBR(BAUD_RATE_DIV_H);
  UART0->BDL = UART0_BDL_SBR(BAUD_RATE_DIV_L);

  /* Set 1 stop bit */
  UART0->BDH &= ~(UART0_BDH_SBNS_MASK);
  
  /* Set 8 Bit Transmit and No Parity Bit */
  UART0->C1 &= ~(UART0_C1_M_MASK | UART0_C1_PE_MASK);

  /* Set the oversampling ratio */
  UART0->C4 |= (UART0_C4_OSR(OSR));
  
  /* Re-enable transmit and receive */
  UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);
  
  /* Enable receive interrupt */
  UART0->C2 |= (UART0_C2_RIE_MASK);
}

/**
 * @brief function to transmit single data byte through the UART
 *
 * This function sends a single byte of data through the UART.
 * This function blocks on trasmitting data.
 *
 * @param pointer to data being transmitted
 * @return UART_status -- failed or success
 */

UART_status UART_send(uint8_t * data_tx)
{
  while(!(UART0->S1&UART0_S1_TC_MASK)) //while transmit not complete
  {
    //NOP
  }
  UART0->D = *data_tx; // write buffer data to UART tx register
  //GPIOB->PTOR |= (1<<18);
  return UART_SUCCESS;
}

/**
 * @brief function to transmit stream of data bytes through the UART
 *
 * This function sends multiple bytes of data through the UART.
 * This function blocks on trasmitting data.
 *
 * @param pointer to data being transmitted, length
 * @return UART_status -- failed or success
 */

UART_status UART_send_n(uint8_t * data_tx, uint16_t length)
{
  for(uint16_t i=0; i<length; i++)
  {
    if(UART_send(data_tx+i)==UART_FAILED)
    {
       return UART_FAILED;
    }
  }
  return UART_SUCCESS;
}

/**
 * @brief function to receive single data byte through the UART
 *
 * This function receives a single byte of data through the UART.
 * This function blocks until a character has been received.
 *
 * @param pointer to data being received
 * @return UART_status -- failed or success
 */

UART_status UART_receive(uint8_t * data_rx)
{
  while(!(UART0->S1&UART0_S1_RDRF_MASK)) // while receive buffer not full
  {
    //NOP
  }
  *data_rx = UART0->D; // put UART data into buffer
  //GPIOB->PTOR |= (1<<19);
  return UART_SUCCESS;
}

/**
 * @brief function to receive stream of data bytes through the UART
 *
 * This function receives multiple bytes of data through the UART.
 * This function blocks until requisite number of characters have been received.
 *
 * @param pointer to data being received, length
 * @return UART_status -- failed or success
 */

UART_status UART_receive_n(uint8_t * data_rx, uint16_t length)
{ 
  for(uint16_t i=0; i<length; i++)
  {
    if(UART_receive(data_rx)==UART_FAILED)
    {
      return UART_FAILED;
    }
  }
  return UART_SUCCESS;
}

/**
 * @brief IRQ handler for the UART
 *
 * This function handles transmit and receive interrupts for the UART.
 * It clears the interrupt flag (if set) for either transmit or receive interrupts.
 *
 * @param none
 * @return none
 */
void UART0_IRQHandler(void)
{
	START_CRITICAL();
//	__disable_irq();
	if(CB_is_empty(tx_buffer)){UART0_C2 &= ~UART_C2_TIE_MASK;}
	if((UART0->S1 & UART0_S1_RDRF_MASK)&&CB_is_full(rx_buffer)!=CB_FULL) // if data to be received present in UART register
	{
		//GPIOB->PTOR |= (1<<19);
		rx_rv_IRQ = UART_receive(temp_rx_ptr);
		rx_rv_IRQ = CB_buffer_add_item(rx_buffer, *temp_rx_ptr);
		populate_log_item(log_ptr_1, DATA_RECEIVED, 0, temp_rx_ptr, 1);
		log_item(log_ptr_1, logger_queue);
		//print_log_item(log_ptr_1);
		if(CB_is_full(rx_buffer)==CB_FULL){
			UART0_C2 &= ~UART_C2_RIE_MASK;
			rx_rv_IRQ = CB_FULL;
		}
	}
	/* If tx data reg is empty and tx buffer has data send data */
	if((UART0->S1 & UART0_S1_TDRE_MASK)&&(CB_is_empty(tx_buffer)!=CB_EMPTY))
	{
		//GPIOB->PTOR |= (1<<18);
		tx_rv_IRQ = CB_buffer_remove_item(tx_buffer, temp_tx_ptr);
		tx_rv_IRQ = UART_send(temp_tx_ptr);
		/* Disable tx interrupts if there is no more data *
		 * This prevents being stuck in TX interrupt */
		if(CB_is_empty(tx_buffer)==CB_EMPTY)
		{
			UART0_C2 &= ~UART_C2_TIE_MASK;
		}
	}
	END_CRITICAL();
	//__enable_irq();
}
