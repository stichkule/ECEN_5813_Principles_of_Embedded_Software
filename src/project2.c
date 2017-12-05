/*
 * project2.c
 *
 *  Created on: Dec 2, 2017
 *      Author: windo
 */

#include <stdint.h>
#include <math.h>
#include "circular_buffer.h"
#include "project2.h"
#include "uart.h"
#include "memory.h"
#include "conversion.h"
#include "MKL25Z4.h"

/* Function to calculate character statistics from our buffer */

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
void calc_statistics(int32_t * ptr, uint8_t * data_ptr)
{
	if(*data_ptr <= 32 || *data_ptr == 127) *(ptr+0) += 1; // Misc.
	if((*data_ptr >= 33 && *data_ptr <= 48) || (*data_ptr >= 91 && *data_ptr <= 96)\
			|| (*data_ptr >= 123 && *data_ptr <= 126) || (*data_ptr >= 58 && *data_ptr <= 64)) *(ptr+1) += 1; // Punct.
	if(*data_ptr >= 48 && *data_ptr <= 57) *(ptr+2) += 1; // Num.
	if((*data_ptr >= 65 && *data_ptr <= 90) || (*data_ptr >= 97 && *data_ptr <= 122)) *(ptr+3) += 1; // Alpha.
}

/**
 * @brief function to dump character count statistics
 *
 * This function displays character count statistics on a terminal
 *
 * @param none
 * @return UART_status type
 *
 */
UART_status dump_statistics(void) //function to dump statistics to terminal
{
	/* Initialize variables*/
	int32_t char_count[4] = {0,0,0,0}; //Array to hold data type counts
	uint8_t temp_1 = 0;
	uint8_t * storage = &temp_1;
	CB_status rv;
	uint8_t categories[4][6] = {"MISC:", "PUNC:", "NUMS:", "ALPH:"}; //Categories
	uint32_t base = 10; //Use decimal base
	uint8_t * res_ptr;
	uint8_t size = 0;
	res_ptr = (uint8_t*) reserve_words(10);

	/* Empty RX buffer and calculate statistics */
	while(CB_is_empty(rx_buffer)!=CB_EMPTY){
		rv = CB_buffer_remove_item(rx_buffer, storage);
		calc_statistics(char_count, storage);
	}

	/* Fill TX buffer with table */
	for(uint8_t m = 0; m < 4; m++)
	{
		for(uint8_t j = 0; j < 6; j++)
		{
			rv = CB_buffer_add_item(tx_buffer, categories[m][j]);
		}
		size = my_itoa(*(char_count+m), res_ptr, base);
		for(uint8_t k = 0; k<size; k++)
		{
			rv = CB_buffer_add_item(tx_buffer,*(res_ptr+k));
		}
		rv = CB_buffer_add_item(tx_buffer,32);
	}

	/* Re-enable RX interrupts */
	UART0_C2 |= UART_C2_RIE_MASK;
	/* Enable TX interrupts */
	UART0_C2 |= UART_C2_TIE_MASK;


	return rv;
}
