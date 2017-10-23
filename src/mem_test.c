#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <stdbool.h>

#include "memory.h"


uint8_t * __wrap_my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
  uint8_t * invalid_ptr;
  check_expected_ptr(src);
  check_expected_ptr(dst);
  check_expected(length);
  invalid_ptr = mock_ptr_type(uint8_t *);
  if(invalid_ptr == NULL) return NULL;
  return mock_type(uint8_t *); 
}

static void test_my_memmove(void **state)
{
  uint8_t * rv;
  uint8_t * ptr;
  uint8_t * src_test = NULL;
  uint8_t * dst_test = NULL;
  uint8_t * src;
  uint8_t * dst;
  size_t length = 2;
  (void) state;

  //check_expected_ptr(__wrap_my_memmove, src, dst, length);
  //will_return(__wrap_my_memmove, true);
  //will_return(__wrap_my_memmove, true);
  //will_return(__wrap_my_memmove, true);
  expect_any_count(__wrap_my_memmove, ptr, 2);
  expect_any(__wrap_my_memmove, length);

  will_return(__wrap_my_memmove, src);

  rv = my_memmove(src_test, dst_test, length);
  assert_ptr_equal(rv, NULL);
}
  
int main(void)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_my_memmove)
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
