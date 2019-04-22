#include "delay.h"
#include "msp.h"
#include "lcd.h"

#define E BIT2
#define RW BIT1
#define RS BIT0

void nybble() {
    P5->OUT |= E; //Set E high
    //delay_us(5, freq);
    delay_ms(5, FREQ);
    P5->OUT &= ~E; //Set E low
}

void lcd_char(int c) {
    int i = c;
    P4->OUT = i;
    P5->OUT |= RS; //Set RS high for Data Send
    P5->OUT &= ~RW; //Set RW Low
    delay_us(40, FREQ);
    nybble(); //Send 4 msb to LCD
    delay_ms(1, FREQ);
    i = c<<4;
    P4->OUT = i;
    delay_us(40, FREQ);
    nybble(); //Send 4 lsb to LCD
    delay_ms(1, FREQ);
}

void command(char c) {
    char i = c;
    P4->OUT = i;
    P5->OUT &= ~RS;  //set R/S low for Command Send
    delay_us(1, FREQ);
    nybble(); //Send 4 msb to LCD
    delay_us(40, FREQ);
    i = c<<4;
    P4->OUT = i;
    delay_us(1, FREQ);
    nybble(); //Send 4 lsb to LCD
    delay_us(40, FREQ);
}

void clearLCD() {
    command(0x01);
}

void homeLCD() {
    command(0x02);
}

void initLCD() {
    P4->SEL1 &= ~(BIT4 | BIT5 | BIT6 | BIT7);  //Select Four Bit data bus to be P4.4-P4.7
    P4->SEL0 &= ~(BIT4 | BIT5 | BIT6 | BIT7);
    P4->DIR |= BIT4 | BIT5 | BIT6 | BIT7;
    P5->SEL1 &= ~(BIT0 | BIT1 | BIT2);  //Select RS, RW, E to ge P5.0-P5.2
    P5->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P5->DIR |= BIT0 | BIT1 | BIT2;
    delay_ms(100, FREQ); //Delay after Power Starup

    //LCD Initilization sequence
    P4->OUT = 0x30;  //Function set instruction was 0x30
    P5->OUT &= ~(RS | RW);  //set RS and RW Low
    delay_ms(2, FREQ);
    nybble();
    delay_ms(2, FREQ);
    command(0x20);  //set 4 bit mode, was 0x28
    delay_ms(2, FREQ);
    command(0x20); //was 0x28
    delay_ms(2, FREQ);
    command(0x0F);
    delay_ms(2, FREQ);
    command(0x01);
    delay_ms(5, FREQ);
    command(0x06);
    delay_ms(500, FREQ);
}

/*void adamSux() {
    data(0x41);
    data(0x44);
    data(0x41);
    data(0x4D);
    data(0x20);
    data(0x53);
    data(0x55);
    data(0x58);
}*/
