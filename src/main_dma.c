#include <stdint.h>
#include <stdlib.h>
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "core_cmInstr.h"
#include "core_cmFunc.h"
#include "dma.h"
#include "memory.h"
#include "project3.h"

uint32_t start_count; // count variables for start and end times
uint32_t end_count;

#define getcount() (SysTick->VAL) // get current value of systick counter
#define systick_overflow (SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk) // check counter overflow
#define systickzero() (SysTick->VAL= 0UL) // reset counter

void SysTick_Init(uint32_t ticks)
{
    SysTick->LOAD  = (uint32_t)(ticks - 1UL); // counter reload value
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // enable counter
    SysTick->VAL   = 0UL;
}

void port_configure() // LED port to test interrupt
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; //Clock Port B
	PORTB->PCR[18] = PORT_PCR_MUX(1); //Alternative GPIO function for red LED pin
	PTB->PDDR = 1 << 18; //Set as output pin
}

void DMA0_IRQHandler(void)
{
	end_count=getcount(); // get count at ISR entry
    // interrupt generated upon DMA transfer completion.
	// disable interrupts
	START_CRITICAL();
	//__disable_irq();
	// set return value of DMA IRQ to indicate memory transfer/set is complete
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	uint8_t rv_DMA_IRQ = 1;
	PTB->PTOR = 1 << 18; //Toggle PTB18 (red LED)
	//GPIOD->PCOR |= (1<<0); // Clear the pin and write 1 to the ISF flag to clear interrupt
	//PORTD->PCR[0] |=PORT_PCR_ISF_MASK;
	// enable interrupts again
	END_CRITICAL();
	//__enable_irq();
}

int main(void)
{

  port_configure();
  DMA_status rv_DMA;
  size_t transfer_length = 5000;
  uint8_t transfer_size = 0; // (0,1,2):(4 bytes, 1 byte, 2 byte)
  uint16_t data_length = 5000;

  uint8_t * src = malloc(data_length*sizeof(uint8_t));
  uint8_t * dst = malloc(transfer_length*sizeof(uint8_t));
  uint8_t * src_zero = malloc(1*sizeof(uint8_t));
  *(src_zero) = 0x00;

  uint8_t systick_overflow_count = 0; // count no. of times timer overflowed

  uint16_t i;
  for(i=0;i<data_length;i++)
  {
	  *(src+i) = (uint8_t)i;
  }

  for(i=0;i<data_length;i++)
    {
  	  *(dst+i) = 0xAA;
    }

  /* Enable DMA0 interrupt*/
  NVIC->ISER[0]=0x00000001;
  //NVIC_EnableIRQ(DMA0_IRQn);
  //NVIC_SetPriority(DMA0_IRQn, DMA_PRIORITY);
  /* Enable interrupts at GLOBAL */
  __enable_irq();

  /*
  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
  start_count=getcount(); // count value before DMA transfer initiated

  dst = my_memmove_dma(src, dst, transfer_length, transfer_size);

  if(systick_overflow)
  {
	  systick_overflow_count++;
  }

  systickzero(); // reset counter for next timing operation

  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
  start_count=getcount(); // count value before DMA transfer initiated

  dst = my_memzero_dma(src_zero, dst, transfer_length, transfer_size);

  if(systick_overflow)
  {
  	  systick_overflow_count++;
  }

  systickzero(); // reset counter for next timing operation
  return 0;*/

  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
    start_count=getcount(); // count value before DMA transfer initiated
    dst = my_memmove(src, dst, transfer_length);
    end_count = getcount();

    if(systick_overflow)
    {
  	  systick_overflow_count++;
    }

    systickzero(); // reset counter for next timing operation

    SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
    start_count=getcount(); // count value before DMA transfer initiated
    dst = my_memzero(dst, transfer_length);
    end_count = getcount();

    if(systick_overflow)
    {
    	  systick_overflow_count++;
    }

    systickzero(); // reset counter for next timing operation
    return 0;
}
