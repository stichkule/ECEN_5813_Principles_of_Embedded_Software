/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file circular_buffer.h 
 * @brief This file is to be used with ECEN 5813 -- Project 2.
 *
 * This header file contains definitions for the circular buffer structure, as
 * well as an enum typedef for errors associated with various operations on the
 * circular buffer. Also, contained are prototypes for functions associated
 * with the circular buffer, as listed under the Project 2 guide. The corresponding
 * function definitions are contained in the file "CircularBuffer.c".
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 *
 * @date October 22, 2017
 *
 */

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

/** This typedef defines a data type CB_t, to represent a struct corresponding to
 * the circular buffer. The elements of the struct are:
 * buf -- pointer to uint8_t data contained within the buffer
 * head -- uint8_t pointer to the 'write' location
 * tail -- uint8_t pointer to the 'read' location
 * size -- uint16_t type size of circular buffer 
 * count -- uint16_t type number of data elements in the buffer
 */
typedef struct
{
  uint8_t * buf;
  uint8_t * head;
  uint8_t * tail;
  uint16_t size;
  uint16_t count;
}CB_t;

/** This typedef defines a data type CB_status, to represent an enum corresponding
 * to the state of the circular buffer, after operations have been performed on it.
 * The status codes contained in the enum are:
 * CB_NO_ERROR -- successful operation
 * CB_FULL -- buffer full
 * CB_EMPTY -- buffer empty
 * CB_NULL_PTR -- null pointer argument
 * CB_NO_LENGTH -- insufficient storage capacity
 * CB_BUFFER_ALLOCATION_FAILURE -- failed memory allocation
 */
typedef enum
{
  CB_NO_ERROR,
  CB_FULL,
  CB_EMPTY, 
  CB_NULL_PTR,
  CB_NO_LENGTH,
  CB_BUFFER_ALLOCATION_FAILURE
}CB_status;

/**
 * @brief function to initialize circular buffer
 * 
 * This function takes in a pointer to a circular buffer, and a length parameter, 
 * and initializes members of the circular buffer struct.
 *
 * @param pointer to circular buffer, length
 * @return operation status of circular buffer
 */
CB_status CB_init(CB_t * circ_buff, uint16_t length);

/**
 * @brief function to destroy circular buffer
 * 
 * This function takes in a pointer to a circular buffer, and deallocates memory
 * assigned to the circular buffer struct.
 *
 * @param pointer to circular buffer
 * @return operation status of circular buffer
 */
CB_status CB_destroy(CB_t* circ_buff);

/**
 * @brief function to check if circular buffer is full
 * 
 * This function takes in a pointer to a circular buffer, and checks whether it
 * is full.
 *
 * @param pointer to circular buffer
 * @return operation status of circular buffer
 */
CB_status CB_is_full(CB_t * circ_buff);

/**
 * @brief function to check if circular buffer is empty
 * 
 * This function takes in a pointer to a circular buffer, and checks whether it
 * is empty.
 *
 * @param pointer to circular buffer
 * @return operation status of circular buffer
 */
CB_status CB_is_empty(CB_t * circ_buff);

/**
 * @brief function to add item to circular buffer
 * 
 * This function takes in a pointer to a circular buffer, a data element, and 
 * given enough space is available, adds it to the circular buffer.
 *
 * @param pointer to circular buffer, data item to be added
 * @return operation status of circular buffer
 */
CB_status CB_buffer_add_item(CB_t * circ_buff, uint8_t data);

/**
 * @brief function to remove item from circular buffer
 * 
 * This function takes in a pointer to a circular buffer, a data pointer, and 
 * given a non-empty buffer, removes the element corresponding to the 'read'
 * pointer.
 *
 * @param pointer to circular buffer, pointer to data removed 
 * @return operation status of circular buffer
 */
CB_status CB_buffer_remove_item(CB_t * circ_buff, uint8_t* data_ptr);

#endif /* __CIRCULAR_BUFFER_H__ */
