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
 * @file project2.c 
 * @brief UART functionality for project 2.
 * This file calls functions from uart.c and implements interrupts for data transfer
 * over the UART.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 29, 2017
 *
 */

#include <stdint.h>
#include <math.h>
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "core_cmInstr.h"
#include "core_cmFunc.h"
#include "circular_buffer.h"
#include "uart.h"
#include "project2.h"
#include "conversion.h"
#include "memory.h"

#define PRIORITY 1 //UART interrupt priority

/* define variables and buffers */
CB_t * rx_buffer = NULL;
CB_t * tx_buffer = NULL;
uint8_t temp_rx = 0;
uint8_t * data_rx = &temp_rx;
uint8_t temp_tx = 0;
uint8_t * data_tx = &temp_tx;
uint8_t rx_rv_IRQ = 0;
uint8_t tx_rv_IRQ = 0;


/**
 * @brief function to calculate character counts
 * 
 * This function takes in a pointer to a integer, classifies it in one of four categories --
 * Miscellaneous, Punctuations, Alphabets, and Numbers, and updates the corresponding 
 * category count.
 *
 * @param pointer to integer, pointer to counter array
 * @return none
 */

void calc_statistics(int32_t * ptr, uint8_t * data_ptr) //function to calculate character count statistics
{
	if(*data_ptr <= 32 || *data_ptr == 127) *(ptr+0) += 1; // Miscellaneous
	if((*data_ptr >= 33 && *data_ptr <= 48) || (*data_ptr >= 91 && *data_ptr <= 96)\
			|| (*data_ptr >= 123 && *data_ptr <= 126) || (*data_ptr >= 58 && *data_ptr <= 64)) *(ptr+1) += 1; // Punctuations
	if(*data_ptr >= 48 && *data_ptr <= 57) *(ptr+2) += 1; // Numbers
	if((*data_ptr >= 65 && *data_ptr <= 90) || (*data_ptr >= 97 && *data_ptr <= 122)) *(ptr+3) += 1; // Alphabets
}

/**
 * @brief function to dump character count statistics
 * 
 * This function displays character count statistics on a terminal
 *
 * @param none
 * @return UART_status type
 */

UART_status dump_statistics(void) //function to dump statistics to terminal
{
	int32_t char_count[4] = {0,0,0,0}; //array to hold counts
	uint8_t temp_1 = 0;
	uint8_t * storage = &temp_1;
	CB_status rv;
	uint8_t categories[4][6] = {"MISC:", "PUNC:", "NUMS:", "ALPH:"}; //categories
	uint32_t base = 10; // base in which counts are represented

	for(uint8_t i=0;i<rx_buffer->size;i++) //remove item from rx_buffer and calculate statistics
	{
		rv = CB_buffer_remove_item(rx_buffer, storage);
		if(rv) break;
		calc_statistics(char_count, storage);
	}
	rv = CB_buffer_add_item(tx_buffer,32);
	for(uint8_t m=0;m<4;m++) // populate transmit buffer with strings and counts
	{
		for(uint8_t j=0;j<5;j++)
		{
			rv = CB_buffer_add_item(tx_buffer,categories[m][j]); // add count categories
		}
		uint8_t *res_ptr;
		uint8_t size=0;
		size = my_itoa(*(char_count+m),res_ptr,base); // convert count to char
		for(uint8_t k=0;k<size;k++)
		{
			rv = CB_buffer_add_item(tx_buffer,*(res_ptr+k)); // add each character to buffer
		}
		rv = CB_buffer_add_item(tx_buffer,32);
	}
	for(uint8_t n=tx_buffer->count; n<tx_buffer->size;n++)
	{
		rv = CB_buffer_add_item(tx_buffer,32); // fill tx_buffer to print to terminal
	}
	return rv;
}

int project2(void)
{
  /* Setup return value and length for circular buffer */
  CB_status rv;
  uint16_t length = 32;

  /* Setup return value for UART */
  UART_status rv_UART;
  rv_UART = UART_configure();
  if(rv_UART)
  {
	  return UART_FAILED;
  }
  
  /* initialize rx circular buffer */
  rx_buffer = malloc(sizeof(CB_t));
  rv = CB_init(rx_buffer, length);

  /* if initialization fails return */
  if(rv)
  {
	rv = CB_destroy(rx_buffer);
    return rv;
  }
  
  /* initialize tx circular buffer */
  tx_buffer = malloc(sizeof(CB_t));
  rv = CB_init(tx_buffer, length);

  /* if initialization fails return */
  if(rv)
  {
  rv = CB_destroy(tx_buffer);
    return rv;
  }

  /* Enable interrupts and set priority at NVIC */
  NVIC_EnableIRQ(UART0_IRQn);
  NVIC_SetPriority(UART0_IRQn, PRIORITY);

  /* Enable interrupts at GLOBAL */
  __enable_irq();

  while(1)
  {
	  while (rx_rv_IRQ == 0)
	  {
		  // Wait for Rx interrupt
	  }
	  rv_UART = dump_statistics();
	  if(rv_UART)
	  {
	  	return UART_FAILED;
	  }
	  /* Enable transmit interrupt */
	  UART0->C2 |= (UART0_C2_TCIE_MASK);
  }
}
