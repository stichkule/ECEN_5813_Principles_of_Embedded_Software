#include <stdint.h>
#include <stdlib.h>
#include "memory.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base){
	uint8_t i = 0;
	uint8_t mod;
	uint8_t sign = 0;
	if(data < 0) sign = 1;
	while(data > 0)
	{
		mod = data % base;
		data = data/base;
		if(mod > 9)
		{
			*(ptr+i)=char(65+mod-10);
		} else {
			*(ptr+i)=char(48+mod);
		}
		i++;
	}
	if(sign)
	{
		*(ptr+i+1)='-';
		i++
	}
	ptr = my_reverse(ptr,i*sizeof(uint8_t));
	*(ptr+i+1) = '\0';
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base){
	int32_t sum = 0;
	uint8_t i;
	for(i = 0; i < digits; i++){
		if(*(ptr+digits-i)>=48 && *(ptr+digits-i)<=57)
		{
			sum += (*(ptr+digits-i)-48) * base**i;
		}
		else if(*(ptr+digits-i)>=65 && *(ptr+digits-i)<=70)
		{
			sum += (*(ptr+digits-i)-55) * base**i;
		}
		else if(*(ptr+digits-i)==45)
		{
			sum*=-1;
		}
	}
	return sum;
}

int8_t big_to_little32(uint32_t * data, uint32_t length)
{
	if(legnth <= 0) return -1;
	uint8_t temp; 
	uint8_t i,k;
	uint8_t * temp_ptr;
	for(k = 0; k< length, k++)
	{
		temp_ptr == data;
		if(temp_ptr == NULL) return -2;
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
	if(legnth <= 0) return -1;
	uint8_t temp; 
	uint8_t i,k;
	uint8_t * temp_ptr;
	for(k = 0; k< length, k++)
	{
		temp_ptr == data;
		if(temp_ptr == NULL) return -2;
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

