/*
 * led.c
 *
 *  Created on: Dec 1, 2017
 *      Author: windo
 */

#include "MKL25Z4.h"

void LED_configure(void){
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;//Enable Port B Clock
    PORTB_PCR18 |= PORT_PCR_MUX(1);//Configure Port B PIN 18 to GPIO
    PORTB_PCR19 |= PORT_PCR_MUX(1);//Configure Port B Pin 19 to GPIO
    GPIOB->PDDR |= (1<<18);//Set Pin 18 to Output
    GPIOB->PDDR |= (1<<19);//Set Pin 19 to Output
}
