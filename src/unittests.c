#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdint.h>
#include <stdlib.h>
#include "memory.h"
#include "conversion.h"
#include "circular_buffer.h"

static void test_my_memmove(void **state)
{
  (void) state;
  uint8_t * rv;
  uint8_t * src = NULL;
  uint8_t * dst = NULL;
  uint8_t offset = 8;
  size_t length = 16;
  size_t array_len = 16;
  uint8_t * mem = (uint8_t *)malloc(length*sizeof(uint8_t*));
  uint8_t i = 0;
  
  /* create memory to test */
  for(i=0;i<length;i++)
    {
      *(mem+i) = i;
    }

  /* test for src, dst = NULL */
  rv = my_memmove(src,dst,length);
  assert_null(rv);
  
  /* test for dst = NULL */
  src = mem;
  rv = my_memmove(src,dst,length);
  assert_null(rv);

  /* test for no overlap between src and dst */
  dst = src + offset;
  length = offset;
  rv = my_memmove(src,dst,length);
  for(i=0;i<length;i++)
    {
      assert_int_equal(*(src+i),*(dst+i));
    }

  /* test for src in dst overlap */
  offset = 4;
  length = 8;
  for(i=0;i<array_len;i++)
    {
      *(mem+i) = i;
    }
  dst = mem;
  src = dst + offset;
  rv = my_memmove(src,dst,length);
  for(i=0;i<length;i++)
    {
      assert_int_equal(*(dst+i),(i+offset));
    }

  /* test for dst in src overlap */
  for(i=0;i<array_len;i++)
    {
      *(mem+i) = i;
    }
  src = mem;
  dst = src + offset;
  rv = my_memmove(src,dst,length);
  for(i=0;i<length;i++)
    {
      assert_int_equal(*(dst+i),i);
    }
  free(mem);
}

static void test_my_memset(void **state)
{
  (void) state;
  uint8_t * rv;
  uint8_t * src = NULL;
  size_t length = 16;
  uint8_t value = 1;
  uint8_t * mem = (uint8_t *)malloc(length*sizeof(uint8_t*));
  uint8_t i = 0;
  
  /* create memory to test */
  for(i=0;i<length;i++)
    {
      *(mem+i) = i;
    }

  /* test for src = NULL */
  rv = my_memset(src,length,value);
  assert_null(rv);
  
  /* test for mem values */
  src = mem;
  rv = my_memset(src,length,value);
  for(i=0;i<length;i++)
    {
      assert_int_equal(*(src+i),value);
    }
  free(mem);
}

static void test_my_memzero(void **state)
{
  (void) state;
  uint8_t * rv;
  uint8_t * src = NULL;
  size_t length = 16;
  uint8_t * mem = (uint8_t *)malloc(length*sizeof(uint8_t*));
  uint8_t i = 0;

  /* test for src = NULL */
  rv = my_memzero(src,length);
  assert_null(rv);
  
  /* test for zero mem values */
  src = mem;
  rv = my_memzero(src,length);
  for(i=0;i<length;i++)
    {
      assert_int_equal(*(src+i),0);
    }
  free(mem);
}

static void test_my_reverse(void **state)
{
  (void) state;
  uint8_t * rv;
  uint8_t * src = NULL;
  size_t length_1 = 9;
  size_t length_2 = 16;
  size_t length_3 = 256;
  uint16_t i = 0;

  /* test for src = NULL */
  rv = my_reverse(src,length_1);
  assert_null(rv);
  
  /* test for odd length */
  uint8_t * mem = (uint8_t *)malloc(length_1*sizeof(uint8_t*));

  /* create memory to test */
  for(i=0;i<length_1;i++)
    {
      *(mem+i) = i;
    }
  
  src = mem;
  rv = my_reverse(src,length_1);
  for(i=0;i<length_1;i++)
    {
      assert_int_equal(*(src+length_1-1-i),i);
    }
  free(mem);

  /* test for even length */
  mem = (uint8_t *)malloc(length_2*sizeof(uint8_t*));

  /* create memory to test */
  for(i=0;i<length_2;i++)
    {
      *(mem+i) = i;
    }
  
  src = mem;
  rv = my_reverse(src,length_2);
  for(i=0;i<length_2;i++)
    {
      assert_int_equal(*(src+length_2-1-i),i);
    }
  free(mem);

  /* test for max length */
  mem = (uint8_t *)malloc(length_3*sizeof(uint8_t*));

  /* create memory to test */
  for(i=0;i<length_3;i++)
    {
      *(mem+i) = i;
    }
  
  src = mem;
  rv = my_reverse(src,length_3);
  for(i=0;i<length_3;i++)
    {
      assert_int_equal(*(src+length_3-1-i),i);
    }
  free(mem);
}

static void test_big_to_little32(void **state)
{
  (void) state;
  int8_t rv;
  uint32_t length = 2;
  uint32_t data[length];
  uint32_t * src = NULL;
  uint8_t i;

  /* test for src = NULL */
  rv = big_to_little32(src,length);
  assert_int_equal(rv,-1);

  /* create memory to test */
  data[0] = 0x11223344;
  data[1] = 0x55667788;
  uint8_t seed = 0x11;
  uint8_t * ptr = (uint8_t *)data;
  rv = big_to_little32(data,length);
  for(i=0;i<length*sizeof(uint32_t)/sizeof(uint8_t);i++)
  {
    assert_int_equal(*(ptr+i),seed*(i+1));
  }
}

static void test_little_to_big32(void **state)
{
  (void) state;
  int8_t rv;
  uint32_t length = 2;
  uint32_t data[length];
  uint32_t * src = NULL;
  uint8_t i;

  /* test for src = NULL */
  rv = little_to_big32(src,length);
  assert_int_equal(rv,-1);

  /* create memory to test */
  data[0] = 0x11223344;
  data[1] = 0x55667788;
  uint8_t seed = 0x11;
  uint8_t * ptr = (uint8_t *)data;
  rv = little_to_big32(data,length);
  for(i=0;i<length*sizeof(uint32_t)/sizeof(uint8_t);i++)
  {
    assert_int_equal(*(ptr+i),seed*(i+1));
  }
}

static void test_CB_init_destroy(void **state)
{
  (void) state;
  CB_t * circ_buff = NULL;
  uint16_t length = 8;
  int8_t rv;

  /* test for circ_buff = NULL */
  rv = CB_init(circ_buff,length);
  assert_int_equal(rv,3);

  /* check for initialization of circ_buff */
  circ_buff = malloc(sizeof(CB_t));
  rv = CB_init(circ_buff,length);
  assert_int_equal(rv,0);

  /* check for circ_buff destroy*/  
  rv = CB_destroy(circ_buff);
  assert_int_equal(rv,0);
}

static void test_CB_add_remove(void **state)
{
  (void) state;
  CB_t * circ_buff = NULL;
  uint16_t length = 8;
  int8_t rv;
  uint8_t data = 0x26;
  uint8_t temp;
  uint8_t * removed_data = &temp;

  /* Initialize and add data to circular buffer */
  circ_buff = malloc(sizeof(CB_t));
  rv = CB_init(circ_buff,length);
  rv = CB_buffer_add_item(circ_buff,data);
  assert_int_equal(rv,0);

  /* Remove added data and check if they match */
  rv = CB_buffer_remove_item(circ_buff, removed_data);
  assert_int_equal(data,*(removed_data));
}
  
static void test_CB_empty_full_wrap(void **state)
{
  (void) state;
  CB_t * circ_buff = NULL;
  uint16_t length = 8;
  int8_t rv;
  uint8_t data;
  uint8_t temp;
  uint8_t * removed_data = &temp; 
  uint8_t i;

  /* Create the buffer */
  circ_buff = malloc(sizeof(CB_t));
  rv = CB_init(circ_buff,length);
  rv = CB_is_empty(circ_buff);
  assert_int_equal(rv,2);

  /* Check read from empty buffer */
  rv = CB_buffer_remove_item(circ_buff, removed_data);
  assert_int_equal(rv,2);

  /* Populate the buffer */
  for(i=0;i<length;i++)
  {
    rv = CB_buffer_add_item(circ_buff,i);
  }

  /* Check for full buffer */
  rv = CB_is_full(circ_buff);
  assert_int_equal(rv,1);

  /* Add item to full buffer */
  rv = CB_buffer_add_item(circ_buff,i+1);
  assert_int_equal(rv,1);

  /* Remove 2 items to check for wrap add */
  rv = CB_buffer_remove_item(circ_buff, removed_data);
  rv = CB_buffer_remove_item(circ_buff, removed_data);

  /* Add 1 item back */
  rv = CB_buffer_add_item(circ_buff,42);
  assert_int_equal(rv,0);
  assert_int_equal(*(circ_buff->head-1),42);

  /* Remove 3 items */
  for(i=0;i<length-1;i++)
  {
    rv = CB_buffer_remove_item(circ_buff,removed_data);
  }
  assert_int_equal(*(removed_data),42);
}

int main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_my_memmove),
    cmocka_unit_test(test_my_memset),
    cmocka_unit_test(test_my_memzero),
    cmocka_unit_test(test_my_reverse),
    cmocka_unit_test(test_big_to_little32),
    cmocka_unit_test(test_little_to_big32),
    cmocka_unit_test(test_CB_init_destroy),
    cmocka_unit_test(test_CB_add_remove),
    cmocka_unit_test(test_CB_empty_full_wrap)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
