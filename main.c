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

uint8_t count;

void main(void)
{
    int freq = FREQ_24_MHz;
    uint8_t i;
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //assign P2 for output
    P2->DIR |= BIT0 | BIT1 | BIT2;
    P2->OUT |= BIT0 | BIT1 | BIT2;
    //set the frequency
    set_DCO(freq);
    //enable interrupts
    __enable_irq();
    //TACCR0 interrupt enabled
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;
    TIMER_A0->CCR[0] = 240;
    //SMCLK and Continuous Mode
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP;
    //Enable sleep on exit from ISR
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
    //Enable Timer_A Interrupts
    NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);

    while(1) {

    }

}

void TA0_0_IRQHandler(void) {
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
    if (count == 0) {
        P2->OUT |= BIT0 | BIT1 | BIT2; //turns LED on
    }
    else {
        P2->OUT &= ~(BIT0 | BIT1 | BIT2); //turns LED off
    }
    count++;
    if (count == 4) {
        count = 0;
    }
}
