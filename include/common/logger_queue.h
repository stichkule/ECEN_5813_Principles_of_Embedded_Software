/******************************************************************************
 * Copyright (C) 2017 by Kyle Harlow and Shiril Tichkule - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material.
 *
 *****************************************************************************/
/**
 * @file logger_queue.h
 * @brief This file is to be used with ECEN 5813 -- Project 3.
 *
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date December 05, 2017
 *
 */

#ifndef __LOGGER_QUEUE_H__
#define __LOGGER_QUEUE_H__

#include "logger.h"

/** This typedef defines a data type logger_q, to represent a struct corresponding to
 * the logger queue. The elements of the struct are:
 * buf -- pointer to log_t data contained within the buffer
 * head -- log_t pointer to the 'write' location
 * tail -- log_t pointer to the 'read' location
 * size -- int16_t type size of log queue
 * count -- int16_t type number of data elements in the buffer
 */
typedef struct
{
  log_t * buf;
  log_t * head;
  log_t * tail;
  int16_t size;
  int16_t count;
}log_q;

/** This typedef defines a data type LQ_status, to represent an enum corresponding
 * to the state of the logger queue, after operations have been performed on it.
 * The status codes contained in the enum are:
 * LQ_NO_ERROR -- successful operation
 * LQ_FULL -- buffer full
 * LQ_EMPTY -- buffer empty
 * LQ_NULL_PTR -- null pointer argument
 * LQ_NO_LENGTH -- insufficient storage capacity
 * LQ_BUFFER_ALLOCATION_FAILURE -- failed memory allocation
 */
typedef enum
{
  LQ_NO_ERROR,
  LQ_FULL,
  LQ_EMPTY,
  LQ_NULL_PTR,
  LQ_NO_LENGTH,
  LQ_BUFFER_ALLOCATION_FAILURE
}LQ_status;

/**
 * @brief function to initialize logger_queue
 *
 * This function takes in a ptr to a log queue, and a size_t length parameter,
 * and initializes members of the log queue struct.
 *
 * @param pointer to log queue, length
 * @return operation status of log queue
 */
LQ_status LQ_init(log_q * log_queue, size_t length);

/**
 * @brief function to destroy log queue
 *
 * This function takes in a pointer to a log queue, and deallocates memory
 * assigned to the log queue struct.
 *
 * @param pointer to log queue
 * @return operation status of log queue
 */
LQ_status LQ_destroy(log_q* log_queue);

/**
 * @brief function to check if log queue is full
 *
 * This function takes in a pointer to a log queue, and checks whether it
 * is full.
 *
 * @param pointer to log queue
 * @return operation status of log queue
 */
LQ_status LQ_is_full(log_q * log_queue);

/**
 * @brief function to check if log queue is empty
 *
 * This function takes in a pointer to a log queue, and checks whether it
 * is empty.
 *
 * @param pointer to log queue
 * @return operation status of log queue
 */
LQ_status LQ_is_empty(log_q * log_queue);

/**
 * @brief function to add item to log queue
 *
 * This function takes in a pointer to a log queue, a data element, and
 * given enough space is available, adds it to the log queue.
 *
 * @param pointer to log queue, ptr to data item (log struct) to be added
 * @return operation status of log queue
 */
LQ_status LQ_buffer_add_item(log_q * log_queue, log_t * log_struct);

/**
 * @brief function to remove item from log queue
 *
 * This function takes in a pointer to a log queue, a data pointer, and
 * given a non-empty buffer, removes the element corresponding to the 'read'
 * pointer.
 *
 * @param pointer to log queue, pointer to data (log struct) removed
 * @return operation status of log queue
 */
LQ_status LQ_buffer_remove_item(log_q * log_queue, log_t * log_struct);

/**
 * @brief function to peak into a log queue
 *
 * This function takes in a pointer to a log queue, a desired buffer
 * location, and a data pointer and fills the data pointer with the element
 * at head-location in the buffer, without changing the buffer.
 *
 * @param pointer to log queue, location in log queue, pointer to
 * data (log struct)
 * @return operation status of log queue
 */
LQ_status LQ_peek(log_q * log_queue, int16_t location, log_t * log_struct);

/**
 * @brief function to block until empty
 *
 * This function blocks until the current logger buffer is empty.
 *
 * @param pointer to log queue
 * @return none
 */
void LQ_flush (log_q * log_queue);

/**
 * @brief function to log a log item
 *
 * This function logs a log item into the logger queue.
 *
 * @param log pointer, logger queue pointer
 * @return none
 */
void log_item(log_t * log_ptr, log_q * log_queue);

#endif /* __LOGGER_QUEUE_H__ */
