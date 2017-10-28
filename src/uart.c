#include <stdint.h>
#include <system_MLK25Z4.h>
#include <MKL25Z4.h>

#define BAUD_RATE 115200
#define OSR 0x0F
#define BUS_CLK ((DEFAULT_SYSTEM_CLOCK)/(((SYSTEM_SIM_CLKDIV1_VALUE&SIM_CLKDIV1_OUTDIV4_MASK)>>SIM_CLKDIV1_OUTDIV4_SHIFT)+0x1))
#define BAUD_RATE_DIV ((BUS_CLK)/((OSR+1)*BAUD_RATE))
#define BAUD_RATE_DIV_H ((BAUD_RATE_DIV>>UART0_BDL_SBR_WIDTH)&UART0_BDH_SBR_MASK)
#define BAUD_RATE_DIV_L ((BAUD_RATE_DIV&UART0_BDL_SBR_MASK))


UART_status UART_configure(void)
{
  /* Disable Transmit and Recieve during configuration */
  UART0->C2 &= ~(UART0_C2_TE_MASK & UART0_C2_RE_MASK);

  /* Set high and low bits of the SBR (Baud rate clock divider */
  UART0->BDH |= UART0_BDH_SBR(BAUD_RATE_DIV_H);
  UART0->BDL |= UART0_BDL_SBR(BAUD_RATE_DIV_L);

  /* Set 1 stop bit */
  UART0->BDH &= ~(UART0_C2_SBNS_MASK);
  
  /* Set 8 Bit Transmit and No Parity Bit */
  UART0->C1 &= ~(UART0_C1_M_MASK & UART0_PE_MASK);

  /* Set the oversampling ration */
  UART0->C4 |= (UART0_C4_OSR(OSR));
  
  /* Re-enable transmit and recieve */
  UART0->C2 |= (UART0_C2_TE_MASK & UART0_C2_RE_MASK);
  
  /* Enable transmit and recieve interupts */
  UART0->C2 |= (UART0_C2_TIE_MASK & UART0_C2_RIE_MASK);

  return UART_SUCCESS
}

UART_status UART_send(uint8_t * data)
{
  return UART_SUCCESS;
}

UART_status UART_send_n(uint8_t * data, uint16_t length)
{
  UART_status rv;
  for(uint16_t i; i<length; i++)
  {
    rv = UART_send(data);
    if(rv == UART_FAIL)
    {
      return UART_FAIL;
    }
  }
  return UART_SUCCESS;
}

UART_status UART_receive(uint8_t * data)
{
  return UART_SUCCESS;
}

UART_status UART_receive_n(uint8_t * data, uint16_t length)
{ 
   UART_status rv;
  for(uint16_t i; i<length; i++)
  {
    rv = UART_recieve(data);
    if(rv == UART_FAIL)
    {
      return UART_FAIL;
    }
  }
  return UART_SUCCESS;
}

void UART0_IRQHandler(void){
}
