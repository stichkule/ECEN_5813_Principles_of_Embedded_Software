#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "platform.h"
#include "project3.h"
#include "memory.h"

int8_t test_move1(uint8_t * src, uint8_t * dst);
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memmove(src, dst, TEST1_MEMMOVE_LENGTH);
  end_time = gettimeofday();
  time_diff = end_time - start_time;
  printf("Time for std memmove with length %d is : %d\n", TEST1_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, dst, TEST1_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memmove with lenght %d is : %d\n", TEST1_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

int8_t test_move2(uint8_t * src, uint8_t * dst){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memmove(src, dst, TEST2_MEMMOVE_LENGTH);
  end_time = gettimeofday();
  time_diff = end_time - start_time;
  printf("Time for std memmove with length %d is : %d\n", TEST2_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, dst, TEST2_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memmove with lenght %d is : %d\n", TEST2_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

int8_t test_move3(uint8_t * src, uint8_t * dst){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memmove(src, dst, TEST3_MEMMOVE_LENGTH);
  end_time = gettimeofday();
  time_diff = end_time - start_time;
  printf("Time for std memmove with length %d is : %d\n", TEST3_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, dst, TEST3_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memmove with lenght %d is : %d\n", TEST3_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

int8_t test_move4(uint8_t * src, uint8_t * dst){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memmove(src, dst, TEST4_MEMMOVE_LENGTH);
  end_time = gettimeofday();
  time_diff = end_time - start_time;
  printf("Time for std memmove with length %d is : %d\n", TEST4_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, dst, TEST4_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memmove with lenght %d is : %d\n", TEST4_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

int8_t test_zero1(uint8_t * src){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memset(src, 0, TEST1_MEMMOVE_LENGTH);
  end_time = gettimeofday();  
  time_diff = end_time - start_time;
  printf("Time for std memset with length %d is : %d\n", TEST1_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, TEST1_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memzero with lenght %d is : %d\n", TEST1_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

int8_t test_zero2(uint8_t * src){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memset(src, 0, TEST2_MEMMOVE_LENGTH);
  end_time = gettimeofday();  
  time_diff = end_time - start_time;
  printf("Time for std memset with length %d is : %d\n", TEST2_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, TEST2_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memzero with lenght %d is : %d\n", TEST2_MEMMOVE_LENGTH, time_diff);
  return test_value;

}

int8_t test_zero3(uint8_t * src){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memset(src, 0, TEST3_MEMMOVE_LENGTH);
  end_time = gettimeofday();  
  time_diff = end_time - start_time;
  printf("Time for std memset with length %d is : %d\n", TEST3_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, TEST3_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memzero with lenght %d is : %d\n", TEST3_MEMMOVE_LENGTH, time_diff);
  return test_value; 
}

int8_t test_zero4(uint8_t * src){
  int start_time = 0;
  int end_time = 0;
  int time_diff = 0;
  int8_t test_value = 0;
  start_time = gettimeofday();
  memset(src, 0, TEST4_MEMMOVE_LENGTH);
  end_time = gettimeofday();  
  time_diff = end_time - start_time;
  printf("Time for std memset with length %d is : %d\n", TEST4_MEMMOVE_LENGTH, time_diff);
  start_time = gettimeofday();
  test_value = my_memmove(src, TEST4_MEMMOVE_LENGTH);
  time_diff = end_time - start_time;
  printf("Time for my_memzero with lenght %d is : %d\n", TEST4_MEMMOVE_LENGTH, time_diff);
  return test_value;
}

void project3(void){
  int8_t test[TESTCOUNT];
  int8_t test_errors = 0;

  uint8_t * test_mem = malloc(TEST_MEM_SET_LENGTH);
  if(! test_mem)
  {
    printf("Malloc 10000 failed")
    return TEST_ERROR;
  }
  uint8_t * ptra = &test_mem[0];
  uint8_t * ptrb = &test_mem[TEST3_MEMMOVE_LENGTH];
  /* initialize test set to test values */
  for (int i = 0; i < TEST_MEM_SET_LENGTH; i++)
  {
    test_mem[i] = i;
  }
  test[0] = test_move1(ptra, ptrb);
  test[1] = test_move2(ptra, ptrb);
  test[2] = test_move3(ptra, ptrb);
  test[3] = test_move4(ptra, ptrb);
  test[4] = test_zero1(ptra);
  test[5] = test_zero2(ptra);
  test[6] = test_zero3(ptra);
  test[7] = test_zero4(ptra);
  for (uint8_t i = 0; i<TESTCOUNT; i++){
    test_errors += test[i];
  }
  if(test_errors != 0){
    printf("%d tests failed", test_errors);
  } else {
    printf("All tests succeeded");
  }
}
