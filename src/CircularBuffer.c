#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  uint8_t * buf;
  uint8_t * head;
  uint8_t * tail;
  uint16_t size;
  uint16_t count;
}CB_t;

typedef enum
{
  CB_NO_ERROR,
  CB_FULL,
  CB_EMPTY, 
  CB_NULL_PTR,
  CB_NO_LENGTH,
  CB_BUFFER_ALLOCATION_FAILURE
}CB_status;

CB_status CB_init(CB_t * circ_buff, uint16_t length)
{
  if(circ_buff == NULL)
  {
    return CB_NULL_PTR;
  }
  if(length == 0)
  {
    return CB_NO_LENGTH;
  }
  circ_buff->buf = malloc(length*sizeof(circ_buff->buf));
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

CB_status CB_destroy(CB_t* circ_buff){
  if(circ_buff == NULL)
  {
    return CB_NULL_PTR;
  }
  free(circ_buff->buf);
  free(circ_buff);
  circ_buff->buf = NULL;
  circ_buff->head = circ_buff->buf;
  circ_buff->tail = circ_buff->head;
  circ_buff = NULL;
  return CB_NO_ERROR;
}

CB_status CB_is_full(CB_t * circ_buff){
  if(circ_buff == NULL)
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

CB_status CB_is_empty(CB_t * circ_buff){
  if(circ_buff==NULL||circ_buff->buf==NULL) return CB_NULL_PTR;
  if(circ_buff->count == 0) return CB_EMPTY;
  else return CB_NO_ERROR;
}

CB_status CB_buffer_add_item(CB_t * circ_buff, uint8_t data)
{
  if(circ_buff==NULL||circ_buff->buf==NULL|| circ_buff->head==NULL)
  {
    return CB_NULL_PTR;
  }
  if(CB_is_full(circ_buff)==CB_FULL)
  {
    return CB_FULL;
  }
  *(circ_buff->head) = data;
  circ_buff->count++;
  if(circ_buff->head+1 == circ_buff->buf+circ_buff->size){
    circ_buff->head = circ_buff->buf;
  }
  else
  {
    circ_buff->head++;
  }
  return CB_NO_ERROR;
}

CB_status CB_buffer_remove_item(CB_t * circ_buff, uint8_t* data_ptr)
{
  if(circ_buff==NULL||circ_buff->buf==NULL|| circ_buff->tail==NULL)
  {
    return CB_NULL_PTR;
  }
  if(CB_is_empty(circ_buff)==CB_EMPTY)
  {
    return CB_EMPTY;
  }
  *(data_ptr) = *(circ_buff->tail);
  circ_buff->count--;
  if(circ_buff->tail+1 == circ_buff->buf+circ_buff->size){
    circ_buff->tail = circ_buff->buf;
  }
  else
  {
    circ_buff->tail++;
  }
  return CB_NO_ERROR;
}


int main(void)
{
  CB_t * circ_buff = malloc(sizeof(CB_t));
  CB_status error = CB_init(circ_buff, 4);
  printf("This is the init error code %d\n", error);
  error = CB_buffer_add_item(circ_buff, 1);
  printf("This is the first add item error %d\n", error);
  error = CB_buffer_add_item(circ_buff, 1);
  error = CB_buffer_add_item(circ_buff, 1);
  error = CB_buffer_add_item(circ_buff, 1);
  error = CB_buffer_add_item(circ_buff, 1);
  printf("This is the full buffer add item error %d\n", error);
  error = CB_destroy(circ_buff);
  printf("This is the destroy error code %d\n", error);
  error = CB_buffer_add_item(circ_buff, 1);
  printf("This is the error adding to a null buffer %d\n", error);
  return 0;
}
