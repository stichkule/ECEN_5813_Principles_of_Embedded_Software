#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "project3.h"
#include "memory.h"

void test_move1(uint8_t * src, uint8_t * dst){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  uint8_t * test_value;
  suseconds_t time_diff_usec = 0;
  gettimeofday(time_start_ptr, NULL);
  memmove(src, dst, TEST1_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memmove with length %d is : %ld:%ld\n", TEST1_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memmove(src, dst, TEST1_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memmove failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memmove with lenght %d is : %ld:%ld\n", TEST1_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_move2(uint8_t * src, uint8_t * dst){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memmove(src, dst, TEST2_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memmove with length %d is : %ld:%ld\n", TEST2_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memmove(src, dst, TEST2_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memmove failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memmove with lenght %d is : %ld:%ld\n", TEST2_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_move3(uint8_t * src, uint8_t * dst){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memmove(src, dst, TEST3_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memmove with length %d is : %ld:%ld\n", TEST3_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memmove(src, dst, TEST3_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memmove failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memmove with lenght %d is : %ld:%ld\n", TEST3_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_move4(uint8_t * src, uint8_t * dst){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memmove(src, dst, TEST4_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memmove with length %d is : %ld:%ld\n", TEST4_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memmove(src, dst, TEST4_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memmove failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memmove with lenght %d is : %ld:%ld\n", TEST4_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_zero1(uint8_t * src){ 
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memset(src, 0, TEST1_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);  
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memset with length %d is : %ld:%ld\n", TEST1_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memzero(src, TEST1_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memzero failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memzero with lenght %d is : %ld:%ld\n", TEST1_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_zero2(uint8_t * src){  
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memset(src, 0, TEST2_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);  
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memset with length %d is : %ld:%ld\n", TEST2_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memzero(src, TEST2_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memzero failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memzero with lenght %d is : %ld:%ld\n", TEST2_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);

}

void test_zero3(uint8_t * src){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memset(src, 0, TEST3_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);  
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memset with length %d is : %ld:%ld\n", TEST3_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memzero(src, TEST3_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memzero failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memzero with lenght %d is : %ld:%ld\n", TEST3_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void test_zero4(uint8_t * src){
  struct timeval start_time;
  struct timeval end_time;
  struct timeval * time_start_ptr = &start_time;
  struct timeval * time_stop_ptr = &end_time;
  time_t time_diff_sec = 0;
  suseconds_t time_diff_usec = 0;
  uint8_t * test_value;
  gettimeofday(time_start_ptr, NULL);
  memset(src, 0, TEST4_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);  
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for std memset with length %d is : %ld:%ld\n", TEST4_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
  gettimeofday(time_start_ptr, NULL);
  test_value = my_memzero(src, TEST4_MEMMOVE_LENGTH);
  gettimeofday(time_stop_ptr, NULL);
  if(!test_value) printf("My_Memzero failed\n");
  time_diff_sec = end_time.tv_sec - start_time.tv_sec;
  time_diff_usec = end_time.tv_usec - start_time.tv_usec;
  printf("Time for my_memzero with lenght %d is : %ld:%ld\n", TEST4_MEMMOVE_LENGTH, time_diff_sec, time_diff_usec);
}

void project3(void){
  uint8_t * test_mem = malloc(TEST_MEM_SET_LENGTH);
  if(! test_mem)
  {
    printf("Malloc %d failed\n", TEST_MEM_SET_LENGTH);
  }
  uint8_t * ptra = &test_mem[0];
  uint8_t * ptrb = &test_mem[TEST3_MEMMOVE_LENGTH];
  /* initialize test set to test values */
  for (int i = 0; i < TEST_MEM_SET_LENGTH; i++)
  {
    test_mem[i] = i;
  }
  test_move2(ptra, ptrb);
  test_move3(ptra, ptrb);
  test_move4(ptra, ptrb);
  test_zero1(ptra);
  test_zero2(ptra);
  test_zero3(ptra);
  test_zero4(ptra);
  printf("All tests complete");
}
