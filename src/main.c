#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "core_cm0plus.h"
#include "core_cmInstr.h"
#include "core_cmFunc.h"
#include "dma.h"
#include "memory.h"
#include "uart.h"
#include "logger.h"
#include "led.h"
#include "nrf24.h"
#include "spi.h"
#include "nordic.h"
#include "gpio.h"
#include "project2.h"
#include "project3.h"
#include "logger_queue.h"
#include "circular_buffer.h"

// Define Global Variables
CB_t * rx_buffer = NULL;
CB_t * tx_buffer = NULL;
uint8_t temp_rx = 0;
uint8_t * temp_rx_ptr = &temp_rx;
uint8_t temp_tx = 0;
uint8_t * temp_tx_ptr = &temp_tx;
uint8_t rx_rv_IRQ = 0;
uint8_t tx_rv_IRQ = 0;
log_q * logger_queue = NULL;
log_t * log_ptr_1 = NULL;
log_t * log_ptr_2 = NULL;
prof_t * prof_ptr = NULL;

uint32_t start_count = 0;
uint32_t end_count = 0;
uint32_t count_diff = 0;

#define getcount() (SysTick->VAL) // get current value of systick counter
#define systick_overflow (SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk) // check counter overflow
#define systickzero() (SysTick->VAL= 0UL) // reset counter

void SysTick_Init(uint32_t ticks)
{
    SysTick->LOAD  = (uint32_t)(ticks - 1UL); // counter reload value
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; // enable counter
    SysTick->VAL   = 0UL;
}

void DMA0_IRQHandler(void)
{
	end_count=getcount(); // get count at ISR entry
    // interrupt generated upon DMA transfer completion.
	// disable interrupts
	__disable_irq();
	// set return value of DMA IRQ to indicate memory transfer/set is complete
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
	uint8_t rv_DMA_IRQ = 1;
	// enable interrupts again
	__enable_irq();
}

int main(void)
{
  port_configure();
  UART_configure();
  DMA_status rv_DMA;
  size_t transfer_length = 5000;
  uint8_t transfer_size = 1; // (0,1,2):(4 bytes, 1 byte, 2 byte)
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

  // Enable DMA0 interrupt
  NVIC->ISER[0]=0x00000001;
  //NVIC_EnableIRQ(DMA0_IRQn);
  //NVIC_SetPriority(DMA0_IRQn, DMA_PRIORITY);
  // Enable interrupts at GLOBAL
  __enable_irq();


  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
  start_count=getcount(); // count value before DMA transfer initiated

  dst = my_memmove_dma(src, dst, transfer_length, transfer_size);

  if(systick_overflow)
  {
	  systick_overflow_count++;
  }

  count_diff = start_count - end_count;
  LOG_RAW_STRING("Clock cycles for memmove -- DMA -- 10 byte -- 1 byte blocks");
  LOG_RAW_INT(count_diff);

  systickzero(); // reset counter for next timing operation

  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
  start_count=getcount(); // count value before DMA transfer initiated

  dst = my_memzero_dma(src_zero, dst, transfer_length, transfer_size);

  if(systick_overflow)
  {
  	  systick_overflow_count++;
  }

  count_diff = start_count - end_count;
  LOG_RAW_STRING("Clock cycles for memzero -- DMA -- 10 byte -- 1 byte blocks");
  LOG_RAW_INT(count_diff);

  systickzero(); // reset counter for next timing operation

  SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
    start_count=getcount(); // count value before DMA transfer initiated
    dst = my_memmove(src, dst, transfer_length);
    end_count = getcount();

    if(systick_overflow)
    {
  	  systick_overflow_count++;
    }

    count_diff = start_count - end_count;
    LOG_RAW_STRING("Clock cycles for memmove -- MY -- 10 byte -- 1 byte blocks");
    LOG_RAW_INT(count_diff);

    systickzero(); // reset counter for next timing operation

    SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
    start_count=getcount(); // count value before DMA transfer initiated
    dst = my_memzero(dst, transfer_length);
    end_count = getcount();

    if(systick_overflow)
    {
    	  systick_overflow_count++;
    }

    count_diff = start_count - end_count;
    LOG_RAW_STRING("Clock cycles for memzero -- MY -- 10 byte -- 1 byte blocks");
    LOG_RAW_INT(count_diff);

//LOGGER stuff

	// Enable interrupts and set priority at NVIC
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable DMA0 interrupt
    NVIC->ISER[0]=0x00000001;

	CB_status rv;
	uint16_t buffer_length = 32;

	// Initialize TX, RX Circular buffers
	rx_buffer = malloc(sizeof(CB_t));
	rv = CB_init(rx_buffer, buffer_length);
	if(rv)
	{
		rv = CB_destroy(rx_buffer);
	}
	tx_buffer = malloc(sizeof(CB_t));
	rv = CB_init(tx_buffer, buffer_length);
	if(rv)
	{
		rv = CB_destroy(tx_buffer);
	}

	logger_queue = malloc(sizeof(log_q));
	LQ_status rv_LQ = LQ_init(logger_queue,2);

	// Run hardware configurations
	LED_configure();

	uint32_t current_epoch = 1512626382;
	rtc_configure();
	rtc_init(current_epoch);

	log_ptr_1 = malloc(sizeof(log_t));
	log_ptr_1->log_id = 0;
	log_ptr_1->timestamp = 0;
	log_ptr_1->log_length = 0;
	log_ptr_1->payload = NULL;
	log_ptr_1->checksum = 0;

	log_ptr_2 = malloc(sizeof(log_t));
	log_ptr_2->log_id = 0;
	log_ptr_2->timestamp = 0;
	log_ptr_2->log_length = 0;
	log_ptr_2->payload = NULL;
	log_ptr_2->checksum = 0;

	prof_ptr = malloc(sizeof(prof_t));
	prof_ptr->profile_time = 0;
	prof_ptr->profiler_id = 0;

	//LOGGER_INITIALIZED
	populate_log_item(log_ptr_1, LOGGER_INITIALIZED, 0, NULL, 0);
	//log_item(log_ptr_1, logger_queue);
	print_log_item(log_ptr_1);

	//SYSTEM_INITIALIZED
	populate_log_item(log_ptr_1, SYSTEM_INITIALIZED, 0, NULL, 0);
	//log_item(log_ptr_1, logger_queue);
	print_log_item(log_ptr_1);

	//INFO
	uint8_t info_string[13] = "Entered Main";
	populate_log_item(log_ptr_1, INFO, 0, info_string, 13);
	//log_item(log_ptr_1, logger_queue);
	print_log_item(log_ptr_1);

	//DMA
	size_t transfer_length[4] = {10,100,1000,5000};
	uint8_t transfer_size = 0; // (0,1,2):(4 bytes, 1 byte, 2 byte)
    uint16_t data_length[4] = {10,100,1000,5000};

    //PROFILING STARTED
    uint8_t analysis_string[27] = "Profiling Analysis Started";
    populate_log_item(log_ptr_1, PROFILING_STARTED, 0, analysis_string, 27);
    //log_item(log_ptr_1, logger_queue);
    print_log_item(log_ptr_1);

    for(uint8_t j=0;j<4;j++)
    {
    	uint16_t i=0;
    	uint8_t * src = malloc(data_length[j]*sizeof(uint8_t));
        uint8_t * dst = malloc(transfer_length[j]*sizeof(uint8_t));
        uint8_t * src_zero = malloc(1*sizeof(uint8_t));
        *(src_zero) = 0x00;

        for(i=0;i<data_length[j];i++){*(src+i) = (uint8_t)i;}
        for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

        SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
       	start_count=getcount(); // count value before DMA transfer initiated
       	dst = my_memmove_dma(src, dst, transfer_length[j], transfer_size);
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (uint8_t)(DMA_MOVE_10+j), prof_ptr, 0);
       	//log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	for(i=0;i<data_length[j];i++){*(src+i) = (uint8_t)i;}
       	for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

       	SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
        start_count=getcount(); // count value before DMA transfer initiated
   	    dst = my_memmove(src, dst, transfer_length[j]);
       	end_count = getcount();
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (MY_MOVE_10+j), prof_ptr, 0);
       	//log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	for(i=0;i<data_length[j];i++){*(src+i) = (uint8_t)i;}
       	for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

       	SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
       	start_count=getcount(); // count value before DMA transfer initiated
        memmove(src, dst, transfer_length[j]);
       	end_count = getcount();
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (STD_MOVE_10+j), prof_ptr, 0);
        //log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

       	SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
       	start_count=getcount(); // count value before DMA transfer initiated
       	dst = my_memzero_dma(src_zero, dst, transfer_length[j], transfer_size);
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (DMA_ZERO_10+j), prof_ptr, 0);
       	//log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

       	SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
       	start_count=getcount(); // count value before DMA transfer initiated
       	dst = my_memzero(dst, transfer_length[j]);
       	end_count = getcount();
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (MY_ZERO_10+j), prof_ptr, 0);
       	//log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	for(i=0;i<data_length[j];i++){*(dst+i) = 0xAA;}

       	SysTick_Init(0xFFFFFF); // Load maximum count in systick counter
       	start_count=getcount(); // count value before DMA transfer initiated
       	memset(dst, 0, transfer_length[j]);
       	end_count = getcount();
       	count_diff = start_count - end_count;
       	systickzero(); // reset counter for next timing operation

       	// PROFILING RESULT
       	populate_log_item(log_ptr_1, PROFILING_RESULT, (STD_ZERO_10+j), prof_ptr, 0);
       	//log_item(log_ptr_1, logger_queue);
       	print_log_item(log_ptr_1);

       	free(src);
       	free(dst);
       	free(src_zero);
    }

	for (;;)
	{
		if(LQ_is_full(logger_queue) == LQ_FULL)
		{
			LQ_flush(logger_queue);
		}
		if(rx_rv_IRQ==CB_FULL)
		{
			rx_rv_IRQ = 0;
			dump_statistics();
			// Re-enable RX interrupts
			//UART0_C2 |= UART_C2_RIE_MASK;

		}
	}
    return 0;
}

// SPI stuff
/*
#include "MKL25Z4.h"
#include "nrf24.h"
#include "spi.h"
#include "nordic.h"
#include "gpio.h"
#include <stdint.h>
#include "uart.h"
#include "project2.h"
#include "project3.h"
#include "logger.h"
#include "logger_queue.h"
#include "circular_buffer.h"

// Define Global Variables
CB_t * rx_buffer = NULL;
CB_t * tx_buffer = NULL;
uint8_t temp_rx = 0;
uint8_t * temp_rx_ptr = &temp_rx;
uint8_t temp_tx = 0;
uint8_t * temp_tx_ptr = &temp_tx;
uint8_t rx_rv_IRQ = 0;
uint8_t tx_rv_IRQ = 0;
log_q * logger_queue = NULL;
log_t * log_ptr_1 = NULL;
log_t * log_ptr_2 = NULL;
prof_t * prof_ptr = NULL;

uint32_t start_count = 0;
uint32_t end_count = 0;
uint32_t count_diff = 0;

int main(void)
{
	uint8_t rv_status,rv_config,rv_tx_addr[5],rv_rf_setup,rv_rf_ch,rv_fifo_status,send_tx_addr[5];
	GPIO_nrf_init();

	// Write registers and read values from NRF module

	nrf_write_register(CONFIG, 0x02); // Power up and configure NRF module
	rv_config = nrf_read_register(CONFIG);
	rv_status = nrf_read_status();
	for(uint8_t i=0;i<4;i++)
		{
			*(send_tx_addr+i) = 0xB3+i;
		}
	*(send_tx_addr+4) = 0x0F;

	nrf_write_tx_addr(send_tx_addr);

	nrf_read_tx_addr(rv_tx_addr);

	nrf_write_rf_setup(0x00);
	rv_rf_setup = nrf_read_rf_setup();

	nrf_write_rf_ch(0x04);
	rv_rf_ch = nrf_read_rf_ch();

	rv_fifo_status = nrf_read_fifo_status();

	return 0;
}*/
