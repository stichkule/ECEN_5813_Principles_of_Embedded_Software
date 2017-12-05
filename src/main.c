/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "uart.h"
#include "memory.h"
#include "conversion.h"
#include "led.h"
#include "project2.h"
#include <stdlib.h>
#include <stdint.h>

#define PRIORITY 1

/* Define Global Variables */
CB_t * rx_buffer = NULL;
CB_t * tx_buffer = NULL;
uint8_t temp_rx = 0;
uint8_t * temp_rx_ptr = &temp_rx;
uint8_t temp_tx = 0;
uint8_t * temp_tx_ptr = &temp_tx;
uint8_t rx_rv_IRQ = 0;
uint8_t tx_rv_IRQ = 0;

int main(void)
{
	/* Run hardware configurations */
	UART_configure();
	LED_configure();

	/* Initialize variables */
	UART_status rv_tx, rv_rx;
	uint8_t string[] = "Hello World";
	int8_t k = 0;
	uint8_t * tx_ptr = string;
	uint8_t rx_data[1];
	uint8_t * rx_ptr = rx_data;
	int8_t length_temp = 12;

	while(k != length_temp)
	{
		rv_tx = UART_send((string+k));
	    k++;
	}

	CB_status rv;
	uint16_t buffer_length = 32;

	/* Initialize global pointers */
	temp_tx_ptr = &temp_tx;
	temp_rx_ptr = &temp_rx;

	/* Initialize RX Circular buffer */
	rx_buffer = malloc(sizeof(CB_t));
	rv = CB_init(rx_buffer, buffer_length);
	if(rv)
	{
		rv = CB_destroy(rx_buffer);
		uint8_t rx_init_fail[] = "RX Buffer Init Failed\n";
		length_temp = 23;
		k = 0;
		while(k != length_temp)
		{
			rv_tx = UART_send((rx_init_fail+k));
		    k++;
		}
		return rv;
	}

	/* Initialize TX Circular buffer */
	tx_buffer = malloc(sizeof(CB_t));
	rv = CB_init(tx_buffer, buffer_length);
	if(rv)
	{
		rv = CB_destroy(tx_buffer);
		uint8_t tx_init_fail[] = "TX Buffer Init Failed\n";
		length_temp = 23;
		k = 0;
		while(k != length_temp)
		{
			rv_tx = UART_send((tx_init_fail+k));
			k++;
		}
		return rv;
	}

	/* Enable interrupts and set priority at NVIC */
	NVIC_EnableIRQ(UART0_IRQn);
	NVIC_SetPriority(UART0_IRQn, PRIORITY);

	/* Enable global interrupts */
	__enable_irq();


	for (;;)
	{
		/*Code based on polling
		 * while(k != length){
		 * rv_tx = UART_send((string+k));
		 * k++;
		 * }
		 * while(1){
		 * rv_rx = UART_receive(rx_ptr);
		 * rv_tx = UART_send(rx_ptr);
		 * }
		 */
		if(rx_rv_IRQ==CB_FULL)
		{
			while((CB_is_empty(rx_buffer)) != CB_EMPTY)
			{
				rv = CB_buffer_remove_item(rx_buffer, rx_ptr);
			}
			//rv_tx = dump_statistics();
			length_temp = 14;
			k=0;
			uint8_t tx_flag[]="32 Chars Sent";
			while(k != length_temp)
			{
				rv = CB_buffer_add_item(tx_buffer, *(tx_flag+k));
				k++;
			}
			/* Re-enable RX interrupts */
			UART0_C2 |= UART_C2_RIE_MASK;
			/* Enable TX interrupts */
			UART0_C2 |= UART_C2_TIE_MASK;
		}
	}
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
