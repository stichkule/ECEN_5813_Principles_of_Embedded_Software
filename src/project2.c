#include "core_cm0plus.h"
#include "core_m4_simd.h"
#include "core_cmInstr.h"
#include "core_cm4.h"
#include "core_cmFunc.h"
#include <stdint.h>



uint32_t project2(void)
{
  /* Enable interupts and set priority at NVIC */
  NVIC_EnableIRQ(UART0_IRQn);
  NVIC_SetPriority(UART0_IRQn, PRIORITY);
  /* Enable interupts at GLOBAL */
  CPSIE i;

  /* more code here */

  return 0;
}
