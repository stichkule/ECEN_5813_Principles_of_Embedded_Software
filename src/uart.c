#include <stdint.h>

#define CLOCK_SETUP (0)

#include "system_MKL25Z4.h"
#include "MKL25Z4.h"
#include "project2.h"
#include "circular_buffer.h"
#include "uart.h"

/* Clock and Baud calculation macros */
#define BAUD_RATE 38400
#define OSR 0x0F
#define BUS_CLK ((DEFAULT_SYSTEM_CLOCK)/(((SYSTEM_SIM_CLKDIV1_VALUE&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+0x1))
#define BAUD_RATE_DIV ((BUS_CLK)/((OSR+1)*BAUD_RATE))
#define BAUD_RATE_DIV_H ((BAUD_RATE_DIV>>8)&UART0_BDH_SBR_MASK)
#define BAUD_RATE_DIV_L ((BAUD_RATE_DIV&UART0_BDL_SBR_MASK))

UART_status UART_configure(void)
{
  /* Set clock source */
  SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0x1);

  SIM->SCGC4 |= SIM_SCGC4_UART0(1);

  /* Enable Port A clock */
  SIM->SCGC5 |= SIM_SCGC5_PORTA(1);

  /* Enable UART0 pins to Alternative Pin 2 */
  PORTA->PCR[1] = PORT_PCR_MUX(0x2);
  PORTA->PCR[2] = PORT_PCR_MUX(0x2);

  /* Disable Transmit and Receive during configuration */
  UART0->C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

  /* Set high and low bits of the SBR (Baud rate clock divider) */
  UART0->BDH |= UART0_BDH_SBR(BAUD_RATE_DIV_H);
  UART0->BDL = UART0_BDL_SBR(BAUD_RATE_DIV_L);

  /* Set 1 stop bit */
  UART0->BDH &= ~(UART0_BDH_SBNS_MASK);
  
  /* Set 8 Bit Transmit and No Parity Bit */
  UART0->C1 &= ~(UART0_C1_M_MASK | UART0_C1_PE_MASK);

  /* Set the oversampling ratio */
  UART0->C4 |= (UART0_C4_OSR(OSR));
  
  /* Re-enable transmit and receive */
  UART0->C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);
  
  /* Enable receive interrupt */
  UART0->C2 |= (UART0_C2_RIE_MASK);

  return UART_SUCCESS;
}

UART_status UART_send(uint8_t * data_tx)
{
  CB_status rv3=0;
  while(!(UART0->S1&UART0_S1_TC_MASK)) //while transmit not complete
  {
    //NOP
  }
  rv3 = CB_buffer_remove_item(tx_buffer, data_tx);

  if(rv3) // if buffer empty, disable tx interrupt
  {
    /* Disable transmit interrupt */
	UART0->C2 &= ~(UART0_C2_TCIE_MASK);

    return UART_FAILED;
  }
  UART0->D = *data_tx; // write buffer data to UART tx register
  return UART_SUCCESS;
}
UART_status UART_send_n(uint8_t * data_tx, uint16_t length)
{
  for(uint16_t i=0; i<length; i++)
  {
    if(UART_send(data_tx+i)==UART_FAILED)
    {
       return UART_FAILED;
    }
  }
  return UART_SUCCESS;
}

UART_status UART_receive(uint8_t * data_rx)
{
  CB_status rv;
  while(!(UART0->S1&UART0_S1_RDRF_MASK)) // while receive buffer not full
  {
    //NOP
  }
  *data_rx = UART0->D; // put UART data into buffer
  rv = CB_buffer_add_item(rx_buffer, *data_rx);
  if(rv)
  {
    return UART_FAILED;
  }
  return UART_SUCCESS;
}

UART_status UART_receive_n(uint8_t * data_rx, uint16_t length)
{ 
  for(uint16_t i=0; i<length; i++)
  {
    if(UART_receive(data_rx)==UART_FAILED)
    {
      return UART_FAILED;
    }
  }
  return UART_SUCCESS;
}

void UART0_IRQHandler(void)
{
  if(UART0->S1 & UART0_S1_RDRF_MASK) // if data to be received present in UART register
	{
	  rx_rv_IRQ = UART_receive(data_rx);
	}
  if(UART0->S1 & UART0_S1_TC_MASK)
  {
     tx_rv_IRQ = UART_send(data_tx); // if data to transmit present in UART register
  }
}
