#include <stdint.h>
#include <stdlib.h>
#include "logger_queue.h"
#include "dma.h"

/*
extern uint8_t temp_rx;
extern uint8_t * data_rx;
extern uint8_t temp_tx;
extern uint8_t * data_tx;
extern CB_t * rx_buffer;
extern CB_t * tx_buffer;
*/
extern uint8_t rv_DMA_IRQ;
extern log_q * logger_queue;
extern log_t * log_ptr_1;
extern log_t * log_ptr_2;
extern prof_t * prof_ptr;
extern uint32_t start_count;
extern uint32_t end_count;
extern uint32_t count_diff;
//extern uint8_t tx_rv_IRQ;


#ifdef KL25Z
#define START_CIRITICAL() (__disable_irq())
#define END_CRITICAL() (__enable_irq())
#endif /* KL25Z */

#ifdef BBB
#define START_CRITICAL() ()
#define END_CRITICAL() ()
#define __STATIC_INLINE
#define __INLINE
#endif /* BBB */

#ifdef HOST
#define START_CRITICAL() ()
#define END_CRITICAL() ()
#define __STATIC_INLINE
#define __INLINE
#endif /* HOST */


