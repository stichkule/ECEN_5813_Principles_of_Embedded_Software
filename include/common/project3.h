#ifndef __PROJECT3_H__
#define __PROJECT3_H__

#include <stdint.h>

#define TEST1_MEMMOVE_LENGTH (10)
#define TEST2_MEMMOVE_LENGTH (100)
#define TEST3_MEMMOVE_LENGTH (1000)
#define TEST4_MEMMOVE_LENGTH (5000)
#define TEST_MEM_SET_LENGTH (10000)


#define TEST_ERROR (1)
#define TEST_NO_ERROR (0)

#define TESTCOUNT (8)

void project3(void);

int8_t test_move1(uint8_t * src, uint8_t * dst);

int8_t test_move2(uint8_t * src, uint8_t * dst);

int8_t test_move3(uint8_t * src, uint8_t * dst);

int8_t test_move4(uint8_t * src, uint8_t * dst);

int8_t test_zero1(uint8_t * src);

int8_t test_zero2(uint8_t * src);

int8_t test_zero3(uint8_t * src);

int8_t test_zero4(uint8_t * src);

#endif /* __PROJECT3_H__ */
