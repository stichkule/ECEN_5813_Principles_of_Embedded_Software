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
 * @file circular_buffer.c 
 * @brief Circular Buffer function definitions for project 2.
 * This file contains definitions for circular buffer functions listed in 
 * the header file circular_buffer.h.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 24, 2017
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include "circular_buffer.h"

CB_status CB_init(CB_t * circ_buff, uint16_t length) // function to initialize circular buffer
{
  if(circ_buff == NULL) // null pointer check
  {
    return CB_NULL_PTR;
  }
  if(length == 0) // no length check
  {
    return CB_NO_LENGTH;
  }
  circ_buff->buf = malloc(length*sizeof(circ_buff->buf)); // allocate memory for circular buffer
  if(circ_buff->buf == NULL)
  {
    return CB_BUFFER_ALLOCATION_FAILURE;
  }
  else
  {
    circ_buff->size = length;
    circ_buff->count = 0;
    circ_buff->head = circ_buff->buf;
    circ_buff->tail = circ_buff->head;
    return CB_NO_ERROR;
  }
}

CB_status CB_destroy(CB_t* circ_buff) // function to destroy circular buffer
{
  if(circ_buff == NULL) // null pointer check
  {
    return CB_NULL_PTR;
  }
  free(circ_buff->buf); // free memory
  free(circ_buff);
  circ_buff->buf = NULL;
  circ_buff->head = circ_buff->buf;
  circ_buff->tail = circ_buff->head;
  circ_buff = NULL;
  return CB_NO_ERROR;
}

CB_status CB_is_full(CB_t * circ_buff) // function to check whether circular buffer is full
{
  if(circ_buff == NULL) // null pointer check
  { 
    return CB_NULL_PTR;
  }
  if(circ_buff->size == circ_buff->count)
  {
    return CB_FULL;
  }
  else
  {
    return CB_NO_ERROR;
  }
}

CB_status CB_is_empty(CB_t * circ_buff) // function to check whether circular buffer is empty
{
  if(circ_buff==NULL||circ_buff->buf==NULL) return CB_NULL_PTR; // null pointer check
  if(circ_buff->count == 0) return CB_EMPTY;
  else return CB_NO_ERROR;
}

CB_status CB_buffer_add_item(CB_t * circ_buff, uint8_t data) // function to add item to circular buffer
{
  if(circ_buff==NULL||circ_buff->buf==NULL|| circ_buff->head==NULL) // null pointer check
  {
    return CB_NULL_PTR;
  }
  if(CB_is_full(circ_buff)==CB_FULL) // check if buffer full
  {
    return CB_FULL;
  }
  *(circ_buff->head) = data; // else add data to buffer
  circ_buff->count++;
  if(circ_buff->head+1 == circ_buff->buf+circ_buff->size) // wrap around
  {
    circ_buff->head = circ_buff->buf;
  }
  else
  {
    circ_buff->head++;
  }
  return CB_NO_ERROR;
}

CB_status CB_buffer_remove_item(CB_t * circ_buff, uint8_t* data_ptr) // function to remove data from circular buffer
{
  if(circ_buff==NULL||circ_buff->buf==NULL|| circ_buff->tail==NULL) // null pointer check
  {
    return CB_NULL_PTR;
  }
  if(CB_is_empty(circ_buff)==CB_EMPTY) // check if empty
  {
    return CB_EMPTY;
  }
  *(data_ptr) = *(circ_buff->tail); // else remove data
  circ_buff->count--;
  if(circ_buff->tail+1 == circ_buff->buf+circ_buff->size) // wrap around
  {
    circ_buff->tail = circ_buff->buf;
  }
  else
  {
    circ_buff->tail++;
  }
  return CB_NO_ERROR;
}

CB_status CB_peek(CB_t * circ_buff, uint16_t location, uint8_t * data_ptr)
{
  if(circ_buff == NULL || data_ptr == NULL || circ_buff->buf == NULL)
  {
    return CB_NULL_PTR;
  }
  if(CB_is_empty(circbuff)==CB_EMPTY)
  {
    return CB_EMPTY;
  }
  if(location > circ_buff->count)
  {
    return CB_NO_LENGTH;
  }
  else if(location >= 0 && circ_buff->head > circ_buff->tail)
  {
    *(data_ptr) = *(circ_buff->head-1-location);
  }
  else if(locaiton >= 0 && circ_buff->head < circ_buff->tail)
  {
    *(data_ptr) = *(circ_buff->head-1-location+circ_buff->size);
  }
  return CB_NO_ERROR;
}
