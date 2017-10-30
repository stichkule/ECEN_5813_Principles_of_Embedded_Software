#include <stdint.h>
#include <stdlib.h>
#include "circular_buffer.h"
#include "uart.h"

extern uint8_t temp_rx;
extern uint8_t * data_rx;
extern uint8_t temp_tx;
extern uint8_t * data_tx;
extern CB_t * rx_buffer;
extern CB_t * tx_buffer;
extern uint8_t rx_rv_IRQ;
extern uint8_t tx_rv_IRQ;

void calc_statistics(int32_t * ptr, uint8_t * data_ptr);
UART_status dump_statistics(void);
