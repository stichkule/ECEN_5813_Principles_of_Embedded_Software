#include "core_cm0plus.h"
#include "core_cm4_simd.h"
#include "core_cmInstr.h"
#include "core_cm4.h"
#include "core_cmFunc.h"
#include "MKL25Z4.h"
#include "system_MKL25Z4.h"

#include <stdint.h>
#include "circular_buffer.h"
#include "uart.h"


#define PRIORITY 1

extern CB_t* circ_buff;

uint32_t project2(void)
{
  /* Setup return value and length for circular buffer */
  CB_status rv;
  uint16_t length = 16;
  /* Setup return value for UART */
  UART_status rv2;
  
  /* initialize circular buffer */
  rv = CB_init(circ_buff, length);
  /* if initialization fails return */
  if(rv)
  {
    return rv;
  }
  
  
  /* Enable interupts and set priority at NVIC */
  /*NVIC_EnableIRQ(UART0_IRQn);
  NVIC_SetPriority(UART0_IRQn, PRIORITY);*/
  /* Enable interupts at GLOBAL */
  //CPSIE i;
  

  uint16_t str_length = 13;
  uint8_t string[] = {"Hello World!"};
  for(uint16_t i = 0; i<length; i++){
    rv = CB_buffer_add_item(circ_buff, *(string+i));
  }
  rv2 = UART_send_n(string, str_length);
  if(rv2) return UART_FAILED;
  else return UART_SUCCESS;
}
