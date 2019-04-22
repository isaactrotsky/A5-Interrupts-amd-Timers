
#ifndef LCD_H_
#define LCD_H_

#define FREQ FREQ_3_MHz

void nybble();
void lcd_char(int c);
void clearLCD();
void homeLCD();
void command(char c);
void initLCD();
//void adamSux();

#endif
