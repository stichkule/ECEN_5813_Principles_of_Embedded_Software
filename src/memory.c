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
 * @file memory.c 
 * @brief Memory manipulation function definitions for project 1.
 *
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date September 29, 2017
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"

uint8_t* my_memmove(uint8_t* src, uint8_t* dst, size_t length)
{
  int32_t distance = dst - src; // get distance of destination from source
  int32_t i;
  if (distance == 0) // if destination and source addresses overlap excatly, no need to move data
    return src;
  else if (distance > 0 && distance < length) // if distance is positive, but less than length, we have overlap
  {
    for(i=length-1;i>=0;i--) // only move non-overlapping memory locations (no data corruption)
    {
      *(dst+i) = *(src+i);
    }
  }
  else if (distance < 0 && abs(distance) < length) // overlap occurs, but distance is negative (dst < src)
  {
    for(i=0;i<=length-1;i++) // only move non-overlapping memory locations
    {  
      *(dst+i) = *(src+i);
    }
  }
  else
    for(i=0; i<=length-1; i++) // finite distance, but no overlap
    {
      *(dst+i) = *(src+i);
    }
  return dst;
}

uint8_t* my_memcpy(uint8_t* src, uint8_t* dst, size_t length)
{
  int32_t i;
  if (src == dst) // if destination and source addresses overlap excatly, no need to copy data
    return src;
  else if (dst > src) // if destination occurs after source in memory
  {
    for(i=0; i<=length-1; i++) // copy memory locations without checking for overlap (data corruption may occur)
    {
      *(dst+i) = *(src+i);
    }
  }
  else if (dst < src) // if destination occurs before source in memory
  {
    for(i=0;i<=length-1;i++) 
    {  
      *(dst+i) = *(src+i);
    }
  }
  return dst;
}

uint8_t* my_memset(uint8_t* src, size_t length, uint8_t value)
{
  uint32_t i;
  for(i=0;i<=length-1;i++) // set memory location contents to value
    {
      *(src+i) = value;
    }
  return src;
}

uint8_t* my_memzero(uint8_t* src, size_t length)
{
  uint32_t i;
  for(i=0;i<=length-1;i++) // set memory location contents to zero
    {
      *(src+i) = 0;
    }
  return src;
}

uint8_t* my_reverse(uint8_t* src, size_t length)
{
  uint8_t* start = src; // create pointers to start and end of memory segment to be reversed
  uint8_t* end = src+length-1;
  uint8_t temp;
  while(start < end) // swap memory locations until start and end pointers meet
    {
      temp = *start;
      *start = *end;
      *end = temp;
      start++; // increment start pointer
      end--; // decrement end pointer
    }
  return src;
}

uint32_t* reserve_words(size_t length)
{
  uint32_t* src; // pointer to reserved memory space
  src = malloc(length*sizeof(uint32_t*)); // allocate memory big enough to hold 'length' number of uint32_t data
  return (src==NULL)?NULL:src; // return NULL if allocations fails, else return pointer to memory
}

void free_words(uint32_t* src)
{
  free(src); // free memory allocated by a previous malloc() operation
}
