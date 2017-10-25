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
 * @file conversion.c
 * @brief Conversion function definitions for project 1.
 * These are functions that convert from an integer to ASCII, and ASCII to an integer and switches from big-little and little-big endian.
 * @author Kyle Harlow
 * @author Shiril Tichkule
 * @date October 1, 2017
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "conversion.h"
#include "memory.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
	uint8_t i = 0;
	uint8_t mod;
	uint8_t sign = 0;

	/* Check if data is less than 0 to set sign */
	if(data < 0)
	{
		sign = 1;
		data *= -1;
	}
	/* Fill pointer with remainder of division from LSB */
	while(data > 0)
  {
		mod = data % base;
		data = data/base;
		if(mod > 9)
		{
			*(ptr+i)=65+mod-10;
		} else {
			*(ptr+i)=48+mod;
		}
		i++;
	}
	/* add sign if value is negative */
	if(sign)
	{
		*(ptr+i)=45;
		i++;
	}
	/* Reverse so LSB is at end of string instead of start */
	ptr = my_reverse(ptr,i*sizeof(uint8_t));
	*(ptr+i) = '\0';
	return i;
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
  {
  int32_t sum = 0;
  uint8_t i;
	/* Sum values of digit * power(Base, i) */
  for(i = 0; i < digits; i++)
	{
  if(*(ptr+digits-1-i)>=48 && *(ptr+digits-1-i)<=57)
	  {
      sum += (*(ptr+digits-1-i)-48) * pow(base,i);
		}
		else if(*(ptr+digits-1-i)>=65 && *(ptr+digits-1-i)<=70)
		{
			sum += (*(ptr+digits-1-i)-55) * pow(base,i);
		}
		else if(*(ptr+digits-1-i)=='-')
		/* if value has a negative sign out front, make value negative */
		{
			sum = -1*sum;
		}
	}
	return sum;
}

int8_t big_to_little32(uint32_t * data, uint32_t length)
{
	if(data == NULL) return -1;
	if(length <= 0) return -2;
	uint8_t temp;
	uint8_t i,k;
	uint32_t * temp_ptr;
	for(k = 0; k< length; k++)
	{
		temp_ptr = data;
		if(temp_ptr == NULL) return -3;
    /* Swap bytes of 32 bit value 1 at a time */
		for(i = 0; i < 2; i++)
		{
			temp = (*temp_ptr+i);
			*(temp_ptr+i)=(*temp_ptr+3-i);
			*(temp_ptr+3-i)=temp;
		}
		data += 1;
	}
	return 0;
}


int8_t little_to_big32(uint32_t * data, uint32_t length)
{
	if(data == NULL) return -1;
	if(length <= 0) return -2;
	uint8_t temp;
	uint8_t i,k;
	uint32_t * temp_ptr;
	for(k = 0; k< length; k++)
	{
		temp_ptr = data;
		if(temp_ptr == NULL) return -3;
		/* Swap bytes of 32 bit value 1 at a time */
		for(i = 0; i < 2; i++)
		{
			temp = (*temp_ptr+i);
			*(temp_ptr+i)=(*temp_ptr+3-i);
			*(temp_ptr+3-i)=temp;
		}
		data += 1;
	}
	return 0;
}
