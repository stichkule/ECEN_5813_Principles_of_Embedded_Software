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
 * @file logger.c
 * @brief Logger function definitions for project 3.
 * This file implements functions for logging data, strings, integers, and timestamps.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date December 05, 2017
 *
 */
#include "MKL25Z4.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "conversion.h"
#include "logger.h"
#include "project3.h"
#include "string.h"
#include "uart.h"

void log_data (uint8_t * ptr, size_t length)
{
	if(ptr == NULL) return;
	for(size_t i=0;i<length;i++)
	{
		printf("%x\n",*(ptr+i));
	}

}

void log_string (uint8_t * str)
{
	if(str == NULL) return;
	size_t length = strlen(str);
	UART_send_n(str,(uint16_t)length);
}

void log_integer (uint32_t integer)
{
	uint8_t holder[32];
	uint8_t * ptr = holder;
	uint8_t size = my_itoa(integer,ptr,10);
	for(uint8_t i=0;i<size;i++)
	{
		UART_send(ptr+i);
	}
}

void log_flush (void);

void log_init(log_t * log_ptr)
{
	log_ptr = malloc(sizeof(log_t));
	log_ptr->log_id = 0;
	log_ptr->timestamp = 0;
	log_ptr->log_length = 0;
	log_ptr->payload = NULL;
	log_ptr->checksum = 0;
}

void log_destroy(log_t * log_ptr)
{
	free(log_ptr);
}

void populate_log_item(log_t * log_ptr, uint8_t log_id, uint8_t profile_id, void * payload_info, size_t length){
  switch(log_id){
    case INFO :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case WARNING :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case ERROR :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case PROFILING_STARTED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case PROFILING_RESULT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      prof_t temp;
      prof_t * temp_ptr = &temp;
      log_ptr->log_length = sizeof(temp);
      temp_ptr->profiler_id = profile_id;
      temp_ptr->profile_time = count_diff;
      log_ptr->payload = (prof_t *) temp_ptr;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case PROFILING_COMPLETED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case DATA_RECEIVED :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case DATA_ALPHA_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
      break;
    case DATA_NUMERIC_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
         break;
    case DATA_PUNCTUATION_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
         break;
    case DATA_MISC_COUNT :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = length;
      log_ptr->payload = (uint8_t *) payload_info;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length+(uint32_t)log_ptr->payload;
         break;
    default :
      log_ptr->log_id = log_id;
      log_ptr->timestamp = RTC_TSR;
      log_ptr->log_length = 0;
      log_ptr->payload = NULL;
      log_ptr->checksum = (uint32_t)log_id+(uint32_t)log_ptr->timestamp+(uint32_t)log_ptr->log_length;
      break;
  }
}

void print_log_item(log_t * log_ptr)
{
	if(log_ptr->log_id==HEARTBEAT)
	{
		LOG_RAW_STRING("HEARTBEAT ");
	}
	else
	{
		LOG_RAW_STRING("LOG ID: ");
		LOG_RAW_INT(log_ptr->log_id);
		LOG_RAW_STRING(", ");
	}
	LOG_RAW_STRING("EPOCH: ");
	LOG_RAW_INT(log_ptr->timestamp);
	LOG_RAW_STRING(", ");
	size_t len = log_ptr->log_length;
	LOG_RAW_STRING("LOG LENGTH: ");
	LOG_RAW_INT(len);
	LOG_RAW_STRING(", ");


	if(len == 1)
	{
		uint32_t *temp = log_ptr->payload;
		if(log_ptr->log_id==DATA_RECEIVED)
		{
			LOG_RAW_STRING("CHAR RX: ");
			LOG_RAW_DATA(log_ptr->payload,len);
			LOG_RAW_STRING(", ");
		}
		else
		{
			LOG_RAW_STRING("COUNT: ");
			LOG_RAW_INT(*temp);
			LOG_RAW_STRING(", ");
		}

	}
	else if(len>1)
	{
		if(log_ptr->log_id==PROFILING_RESULT)
		{
			prof_t* temp_prof = log_ptr->payload;
			LOG_RAW_STRING("PROFILE TIME: ");
			LOG_RAW_INT(temp_prof->profile_time);
			LOG_RAW_STRING(", ");
			LOG_RAW_STRING("PROFILER ID: ");
			LOG_RAW_INT(temp_prof->profiler_id);
			LOG_RAW_STRING(", ");
		}
		else
		{
			LOG_RAW_STRING("PAYLOAD: ");
			LOG_RAW_STRING(log_ptr->payload);
			LOG_RAW_STRING(", ");
		}
	}
	LOG_RAW_STRING("CHECKSUM: ");
	LOG_RAW_INT(log_ptr->checksum);
	LOG_RAW_STRING("\n\r");
}

void rtc_configure (void)
{
	MCG_C1 |= MCG_C1_IRCLKEN_MASK; //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);  //Internal Reference Clock -->Slow

	//**RTC_CLKIN**//
	SIM_SOPT1 |= SIM_SOPT1_OSC32KSEL(0b10);  //32 Khz clock source for RTC
	SIM_SCGC5 |= SIM_SCGC5_PORTC(1);
	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));       //PTC1 as RTC_CLKIN

	//**32KHz Frequency**//
	SIM_SOPT2 |= SIM_SOPT2_CLKOUTSEL(0b100); //Clockout pin --> 32 KHz

	PORTC_PCR3 |= (PORT_PCR_MUX(0x5)); //PTC3 as CLKOUT
}

void rtc_init(uint32_t epoch)
{
	/* disable timer */
	//RTC_SR &= ~RTC_SR_TCE_MASK;

    /*enable the clock to SRTC module register space*/
	SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;

	/*Clear software reset Register*/
    RTC_CR  &= ~RTC_CR_SWR_MASK;

    if (RTC_SR & RTC_SR_TIF_MASK){
        RTC_TSR = 0x00000000;   //  this action clears the TIF
    }

    /*Set time compensation parameters*/
    RTC_TCR = RTC_TCR_CIR(0) | RTC_TCR_TCR(0);

    /*Enable Seconds Interrupt*/
    RTC_IER |= RTC_IER_TSIE_MASK; //Seconds interrupt enable

    /*Enable RTC seconds irq*/
    //NVIC_EnableIRQ(21);

    /*Write to the TSR to clear SR[TOF] and SR[TIF] flags*/
    RTC_TSR = epoch;

    /*Timer enable*/
    RTC_SR |= RTC_SR_TCE_MASK;
}

void RTC_Seconds_IRQHandler(void)
{
	__disable_irq();
	GPIOB->PTOR |= (1<<19);
	populate_log_item(log_ptr_1, HEARTBEAT, 0, NULL, 0);
	log_item(log_ptr_1, logger_queue);
	print_log_item(log_ptr_1);
	__enable_irq();
    //Log heartbeat
}
