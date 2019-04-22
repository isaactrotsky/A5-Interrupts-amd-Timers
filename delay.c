/*
 * delay.c
 *
 *  Created on: Apr 8, 2019
 *      Author: Tristan
 */
#include "stdint.h"
#include "stdio.h"
#include "delay.h"
#include "msp.h"


void delay_ms(int count, int freq) {
    int i, j;
    //run the loop for the pulse length provided in count
    for (j = 0; j < count; j++) {
        for (i = freq/10000; i > 0; i--) { //freq/10000 calculates to about 1ms
        }
    }
}

void delay_us(int count, int freq) {
    int i, wait;
    if( freq == FREQ_15_MHz) {
            wait = count / 8;
        }
        else if( freq == FREQ_3_MHz) {
            wait = count / 4;
        }
        else if( freq == FREQ_6_MHz) {
                wait = count / 2;
        }
        else if( freq == FREQ_12_MHz) {
                wait = count;
        }
        else if( freq == FREQ_24_MHz) {
                wait = count * 2;
        }
        else if( freq == FREQ_48_MHz) {
                wait = count * 4;
        }
        else {
                wait = count / 8;
        }
    for (i=0; i<wait; i++);
}

void set_DCO(int freq) {
    CS->KEY = CS_KEY_VAL;   //unlock CS registers
    CS->CTL0 = 0;           //clears register CTL0
    //Set CTL0 to appropriate frequency
    if( freq == FREQ_15_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_0;
    }
    else if( freq == FREQ_3_MHz) {
        CS->CTL0 = CS_CTL0_DCORSEL_1;
    }
    else if( freq == FREQ_6_MHz) {
            CS->CTL0 = CS_CTL0_DCORSEL_2;
    }
    else if( freq == FREQ_12_MHz) {
            CS->CTL0 = CS_CTL0_DCORSEL_3;
    }
    else if( freq == FREQ_24_MHz) {
            CS->CTL0 = CS_CTL0_DCORSEL_4;
    }
    else if( freq == FREQ_48_MHz) {
        //Copy and pasted 48 MHz code
        /* Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */
            while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
                PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
            while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));

            /* Configure Flash wait-state to 1 for both banks 0 & 1 */
            FLCTL->BANK0_RDCTL = (FLCTL->BANK0_RDCTL &
             ~(FLCTL_BANK0_RDCTL_WAIT_MASK)) | FLCTL_BANK0_RDCTL_WAIT_1;
            FLCTL->BANK1_RDCTL = (FLCTL->BANK0_RDCTL &
             ~(FLCTL_BANK1_RDCTL_WAIT_MASK)) | FLCTL_BANK1_RDCTL_WAIT_1;

            /* Configure DCO to 48MHz, ensure MCLK uses DCO as source*/
            CS->KEY = CS_KEY_VAL ; // Unlock CS module for register access
            CS->CTL0 = 0; // Reset tuning parameters
            CS->CTL0 = CS_CTL0_DCORSEL_5; // Set DCO to 48MHz

            /* Select MCLK = DCO, no divider */
            CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK) |
             CS_CTL1_SELM_3;
            CS->KEY = 0; // Lock CS module from unintended accesses
    }
    else {
        CS->CTL0 = CS_CTL0_DCORSEL_0;
    }
}
