/*
 * delay.h
 *
 *  Created on: Apr 8, 2019
 *      Author: Tristan
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "stdint.h"

#define FREQ_15_MHz 1500000
#define FREQ_3_MHz 3000000
#define FREQ_6_MHz 6000000
#define FREQ_12_MHz 12000000
#define FREQ_24_MHz 24000000
#define FREQ_48_MHz 48000000

void delay_ms(int count, int freq);
void delay_us(int count, int freq);
void set_DCO(int freq);


#endif /* DELAY_H_ */
