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
 * @file dma.c
 * @brief DMA function definitions for project 3.
 * This file implements functions to configure the DMA module to work with memmove and memzero.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date December 04, 2017
 *
 */

 #include <stdint.h>

#define CLOCK_SETUP (0)

#include "MKL25Z4.h"
#include "system_MKL25Z4.h"
#include "project3.h"
#include "dma.h"

DMA_status DMA_configure_memmove(uint8_t* src, uint8_t* dst, size_t length, uint8_t transfer_size)
{
  /* Set clock source */
  SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;    // Enable clock to DMA MUX
  SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;       // Enable clock to DMA

  // Disable DMA MUX channel 0
  //DMAMUX0_CHCFG0 = 0x00;

  // Clear pending errors and/or the done bit
  /*if (((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK)
  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
  DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;*/

  // Clear Source size and Destination size fields.
  DMA_DCR0 &= ~(DMA_DCR_SSIZE_MASK | DMA_DCR_DSIZE_MASK);

  // Configure DMA settings:
  DMA_DCR0 |= (DMA_DCR_SSIZE(transfer_size) // Source transfer size
  | DMA_DCR_DSIZE(transfer_size) // Destination transfer size
  | DMA_DCR_SINC_MASK // Source address will be incremented after each transfer
  | DMA_DCR_DINC_MASK // Destination address will be incremented after each transfer
  | DMA_DCR_EADREQ_MASK // Asynchronous DMA requests are enabled
  | DMA_DCR_EINT_MASK); // Enable DMA interrupt on transfer complete

  // Set no. of bytes to transfer
  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);

  // Set source and destination addresses
  DMA_SAR0 = (uint32_t)src;
  DMA_DAR0 = (uint32_t)dst;

  // Select the DMA Channel Source
  //DMAMUX0_CHCFG0 = 0x3c; // Always enabled channel source for DMA MUX -- channel no. 60
  //DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; // Enable the DMA MUX channel

  return DMA_SUCCESS;
}

DMA_status DMA_configure_memzero(uint8_t* src_zero, uint8_t* dst, size_t length, uint8_t transfer_size)
{
	/* Set clock source */
	  SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;    // Enable clock to DMA MUX
	  SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;       // Enable clock to DMA

	  // Disable DMA MUX channel 0
	  //DMAMUX0_CHCFG0 = 0x00;

	  // Clear pending errors and/or the done bit
	  /*if (((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK)
	  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
	  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
	  | ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
	  DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;*/

	  // Clear Destination size field.
	  DMA_DCR0 &= ~(DMA_DCR_DSIZE_MASK);

	  // Clear SINC field
	  DMA_DCR0 &= ~(DMA_DCR_SINC_MASK);

	  // Configure DMA settings:
	  DMA_DCR0 |= (DMA_DCR_SSIZE(1) // Source transfer size = 1
	  | DMA_DCR_DSIZE(transfer_size) // Destination transfer size
	  | DMA_DCR_DINC_MASK // Destination address will be incremented after each transfer
	  | DMA_DCR_EADREQ_MASK // Asynchronous DMA requests are enabled
	  | DMA_DCR_EINT_MASK); // Enable DMA interrupt on transfer complete

	  // Set no. of bytes to transfer
	  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(length);

	  // Set destination addresses
	  DMA_SAR0 = (uint32_t)src_zero;
	  DMA_DAR0 = (uint32_t)dst;

	  // Select the DMA Channel Source
	  //DMAMUX0_CHCFG0 = 0x3c; // Always enabled channel source for DMA MUX -- channel no. 60
	  //DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; // Enable the DMA MUX channel

	  return DMA_SUCCESS;
}
