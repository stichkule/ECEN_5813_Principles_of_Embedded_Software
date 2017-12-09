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
 * @file logger_queue.c
 * @brief Circular Buffer function definitions for project 2.
 * This file contains definitions for circular buffer functions listed in
 * the header file circular_buffer.h.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 24, 2017
 *
 */

#include "MKL25Z4.h"
#include <stdint.h>
#include <stdlib.h>
#include "logger_queue.h"
#include "project3.h"
#include "core_cm0plus.h"

LQ_status LQ_init(log_q * log_queue, size_t length) // function to initialize circular buffer
{
  if(log_queue == NULL) // null pointer check
  {
    return LQ_NULL_PTR;
  }
  if(length == 0) // no length check
  {
    return LQ_NO_LENGTH;
  }
  log_queue->buf = malloc(length*sizeof(log_t)); // allocate memory for circular buffer
  if(log_queue->buf == NULL)
  {
    return LQ_BUFFER_ALLOCATION_FAILURE;
  }
  else
  {
    log_queue->size = length;
    log_queue->count = 0;
    log_queue->head = log_queue->buf;
    log_queue->tail = log_queue->head;
    return LQ_NO_ERROR;
  }
}

LQ_status LQ_destroy(log_q* log_queue) // function to destroy circular buffer
{
  if(log_queue == NULL) // null pointer check
  {
    return LQ_NULL_PTR;
  }
  free(log_queue->buf); // free memory
  free(log_queue);
  log_queue->buf = NULL;
  log_queue->head = log_queue->buf;
  log_queue->tail = log_queue->head;
  log_queue = NULL;
  return LQ_NO_ERROR;
}

__STATIC_INLINE LQ_status LQ_is_full(log_q * log_queue) // function to check whether circular buffer is full
{
  if(log_queue == NULL) // null pointer check
  {
    return LQ_NULL_PTR;
  }
  if(log_queue->size == log_queue->count)
  {
    return LQ_FULL;
  }
  else
  {
    return LQ_NO_ERROR;
  }
}

__STATIC_INLINE LQ_status LQ_is_empty(log_q * log_queue) // function to check whether circular buffer is empty
{
  if(log_queue==NULL||log_queue->buf==NULL) return LQ_NULL_PTR; // null pointer check
  if(log_queue->count == 0) return LQ_EMPTY;
  else return LQ_NO_ERROR;
}

LQ_status LQ_buffer_add_item(log_q * log_queue, log_t * log_struct) // function to add item to circular buffer
{
  if(log_queue==NULL||log_queue->buf==NULL|| log_queue->head==NULL) // null pointer check
  {
    return LQ_NULL_PTR;
  }
  if(LQ_is_full(log_queue)==LQ_FULL) // check if buffer full
  {
    return LQ_FULL;
  }
  (log_queue->head) = (log_struct); // else add data to buffer
  log_queue->count++;
  if(log_queue->head+1 == log_queue->buf+log_queue->size) // wrap around
  {
    log_queue->head = log_queue->buf;
  }
  else
  {
    log_queue->head++;
  }
  return LQ_NO_ERROR;
}

LQ_status LQ_buffer_remove_item(log_q * log_queue, log_t * log_struct) // function to remove data from circular buffer
{
  if(log_queue==NULL||log_queue->buf==NULL|| log_queue->tail==NULL) // null pointer check
  {
    return LQ_NULL_PTR;
  }
  if(LQ_is_empty(log_queue)==LQ_EMPTY) // check if empty
  {
    return LQ_EMPTY;
  }
  log_struct = (log_queue->tail); // else remove data
  log_queue->count--;
  if(log_queue->tail+1 == log_queue->buf+log_queue->size) // wrap around
  {
    log_queue->tail = log_queue->buf;
  }
  else
  {
    log_queue->tail++;
  }
  return LQ_NO_ERROR;
}

LQ_status LQ_peek(log_q * log_queue, int16_t location, log_t * log_struct)
{
  if(log_queue == NULL || log_struct == NULL || log_queue->buf == NULL)
  {
    return LQ_NULL_PTR;
  }
  if(LQ_is_empty(log_queue)==LQ_EMPTY)
  {
    return LQ_EMPTY;
  }
  if(location > log_queue->count)
  {
    return LQ_NO_LENGTH;
  }
  else if(location >= 0 && log_queue->head > log_queue->tail)
  {
    log_struct = (log_queue->head-1-location);
  }
  else if(location >= 0 && log_queue->head < log_queue->tail)
  {
    log_struct = (log_queue->head-1-location+log_queue->size);
  }
  return LQ_NO_ERROR;
}

void LQ_flush (log_q * log_queue)
{
	__disable_irq();
	while(LQ_is_empty(log_queue) != LQ_EMPTY)
	{
		LQ_status rv_LQ = LQ_buffer_remove_item(log_queue,log_ptr_2);
		print_log_item(log_ptr_2);
	}
	__enable_irq();
}

void log_item(log_t * log_ptr, log_q * log_queue)
{
	LQ_status rv = LQ_buffer_add_item(log_queue, log_ptr);
}
