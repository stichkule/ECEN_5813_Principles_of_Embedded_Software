#include <stdint.h>
#include "system_MLK25Z4.h"
#include "MKL25Z4.h"
#include "circular_buffer.h"

#define BAUD_RATE 115200
#define OSR 0x0F
#define BUS_CLK ((DEFAULT_SYSTEM_CLOCK)/(((SYSTEM_SIM_CLKDIV1_VALUE&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+0x1))
#define BAUD_RATE_DIV ((BUS_CLK)/((OSR+1)*BAUD_RATE))
#define BAUD_RATE_DIV_H ((BAUD_RATE_DIV>>UART0_BDL_SBR_WIDTH)&UART0_BDH_SBR_MASK)
#define BAUD_RATE_DIV_L ((BAUD_RATE_DIV&UART0_BDL_SBR_MASK))

extern uint8_t * data;

UART_status UART_configure(void)
{
  /* Disable Transmit and Recieve during configuration */
  UART0->C2 &= ~(UART0_C2_TE_MASK & UART0_C2_RE_MASK);

  /* Set high and low bits of the SBR (Baud rate clock divider) */
  UART0->BDH |= UART0_BDH_SBR(BAUD_RATE_DIV_H);
  UART0->BDL |= UART0_BDL_SBR(BAUD_RATE_DIV_L);

  /* Set 1 stop bit */
  UART0->BDH &= ~(UART0_C2_SBNS_MASK);
  
  /* Set 8 Bit Transmit and No Parity Bit */
  UART0->C1 &= ~(UART0_C1_M_MASK & UART0_PE_MASK);

  /* Set the oversampling ratio */
  UART0->C4 |= (UART0_C4_OSR(OSR));
  
  /* Re-enable transmit and receive */
  UART0->C2 |= (UART0_C2_TE_MASK & UART0_C2_RE_MASK);
  
  /* Enable transmit and receive interupts */
  UART0->C2 |= (UART0_C2_TIE_MASK & UART0_C2_RIE_MASK);

  return UART_SUCCESS
}

UART_status UART_send(uint8_t * data)
{
  CB_status rv;
  while(!(UART0->S1&UART0_S1_TDRE_MASK))
  {
    //NOP
  }
  rv = CB_buffer_remove_item(circ_buff, data);
  if(rv)
  {
    return UART_FAILED;
  }
  UART->D = *data;
  return UART_SUCCESS;
}

UART_status UART_send_n(uint8_t * data, uint16_t length)
{
  for(uint16_t i=0; i<length; i++)
  {
    if(UART_send(data+i)==UART_FAILED)
    {
       return UART_FAILED;
    }
    /*
    else if(UART_send(data)==UART_SUCCESS)
    {
      //NOP
    }*/
  }
  return UART_SUCCESS;
}

UART_status UART_receive(uint8_t * data)
{
  CB_status rv;
  while(!(UART0->S1&UART0_S1_RDRF_MASK))
  {
    //NOP
  }
  *data = UART->D;
  rv = CB_buffer_add_item(circ_buff, data);
  if(rv)
  {
    return UART_FAILED;
  }
  return UART_SUCCESS;
}

UART_status UART_receive_n(uint8_t * data, uint16_t length)
{ 
  for(uint16_t i; i<length; i++)
  {
    if(UART_receive(data)==UART_FAILED)
    {
      return UART_FAILED;
    }
  }
  return UART_SUCCESS;
}

void UART0_IRQHandler(void){
  if(UART0->S1 & UART0_S1_TDRE_MASK)
  {
     UART_send(data);
  }
  if(UART0->S1 & UART0_S1_RDRF_MASK)
  {    
    UART_receive(data);
  }
}
