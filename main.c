#include "msp.h"
#include "delay.h"
#include "lcd.h"
#include "keypad.h"
#include "stdint.h"

#define CYCLES_HIGH 239
#define CYCLES_LOW 719
/**
 * main.c
 */

uint16_t count = 0;
int freq = FREQ_15_MHz;

void init() {

    //Set P4.3
    P4->SEL0 |= BIT3;
    P4->SEL1 &= ~BIT3; //Set I/O mode to be MCLK
    P4->DIR |= BIT3; //Set high for output

   //assign P6.0 for Output
    P6->DIR |= BIT0;
   //assign P2 for output
   P2->DIR |= BIT0 | BIT1 | BIT2;
   P2->OUT |= BIT0 | BIT1 | BIT2;
   //set the frequency
   set_DCO(freq);
   //enable interrupts
   __enable_irq();
   //TACCR0 interrupt enabled
   TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;
   TIMER_A0->CCR[0] = 37500;
   //SMCLK and Up Mode
   TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;
   //Enable sleep on exit from ISR
   SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
   //Enable Timer_A Interrupts
   NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
}

void main(void)
{

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	init();

    while(1) {

    }

}

void TA0_0_IRQHandler(void) {
    P6->OUT |= BIT0; //Set high to indicate entered the routine
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    if (count <= 399 ) {
        P2->OUT |= BIT0 | BIT1 | BIT2; //turns LED on
    }
    else {
        P2->OUT &= ~(BIT0 | BIT1 | BIT2); //turns LED off
    }
    count++;
    if (count == 800) {
        count = 0;
    }
    P6->OUT &= ~BIT0; //Clear low to indicate exited the routine
}
