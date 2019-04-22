/*
 * keypad.c
 *
 *  Created on: Apr 16, 2019
 *      Author: trotta.isaac
 */
#include "msp.h"

void keypadInit() {
   P4->SEL1 &= ~(BIT0 | BIT1 | BIT2);  //Init Columns as inputs
   P4->SEL0 &= ~(BIT0 | BIT1 | BIT2);
   P4->DIR &= ~(BIT0 | BIT1 | BIT2);
   P4->REN |= (BIT0 | BIT1 | BIT2); //Set pull  resistors
   P4->OUT &= ~(BIT0 | BIT1 | BIT2); //Set pulldown resistor

   P2->SEL1 &= ~(BIT4 | BIT5 | BIT6 | BIT7);  //Init rows as outputs
   P2->SEL0 &= ~(BIT4 | BIT5 | BIT6 | BIT7);
   P2->DIR |= BIT4 | BIT5 | BIT6 | BIT7;

}

char seekKeypadPress() {

   P2->OUT &= 0x0f; //Clear top 4 bits
   P2->OUT |= BIT4; //Set Row 1
   if(P4->IN & BIT0) { //1
       return 0x31;
   }
   if(P4->IN & BIT1) { //2
       return 0x32;
   }
   if(P4->IN & BIT2) { //3
       return 0x33;
   }
   P2->OUT &= 0x0f; //Clear top 4 Bits
   P2->OUT |= BIT5; //Set row 2
   if(P4->IN & BIT0 ) { //4
       return 0x34;
   }
   if(P4->IN & BIT1) { //5
      return 0x35;
   }
   if(P4->IN & BIT2) { //6
      return 0x36;
   }
   P2->OUT &= 0x0f; //Clear top 4 Bits
   P2->OUT |= BIT6; //Set row 3
   if(P4->IN & BIT0 ) { //7
      return 0x37;
   }
   if(P4->IN & BIT1) { //8
      return 0x38;
   }
   if(P4->IN & BIT2) { //9
      return 0x39;
   }
   P2->OUT &= 0x0f; //Clear top 4 Bits
   P2->OUT |= BIT7; //Set row 4
   if(P4->IN & BIT0 ) { //*
      return 0x2A;
   }
   if(P4->IN & BIT1) { //0
      return 0x30;
   }
   if(P4->IN & BIT2) { //#
      return 0x23;
   }
   return 0x00;
}




