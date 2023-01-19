/*
 * labb1.cpp
 *
 * Created: 2023-01-18 12:58:25
 * Author : rallo
 */ 

#include <avr/io.h>


void LCD_Init(void) {
    // Use external asynchronous clock source 
    // 1/3 Bias and 1/4 duty, 25 segments enabled 
    LCDCRB = (1<<LCDCS) | (1<<LCDMUX1)| (1<<LCDMUX0)| (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	// 
    // Using 16 as prescaler selection and 8 as LCD Clock Divide 
    LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
    // Set segment drive time to 300 us and output voltage to 3.35 V
    LCDCCR = (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1)| (1<<LCDCC0);
    // Enable LCD, low power waveform, no frame interrupt, no blanking 
    LCDCRA = (1<<LCDEN) | (1<<LCDAB) |  (0<<LCDBL);
}


void LCD_update(unsigned char data1 ,char data2);
{
	/* LCD Blanking and Low power waveform are unchanged. */
	/* Update Display memory. */
	LCDDR0 = data1;
	LCDDR6 = data2;
}

void LCD_disable(void);
{
	/* Wait until a new frame is started. */
	while ( !(LCDCRA & (1<<LCDIF)) )
	;
	/* Set LCD Blanking and clear interrupt flag */
	/* by writing a logical one to the flag. */
	LCDCRA = (1<<LCDEN)|(1<<LCDIF)|(1<<LCDBL);
	/* Wait until LCD Blanking is effective. */
	while ( !(LCDCRA & (1<<LCDIF)) )
	;
	/* Disable LCD */
	LCDCRA = (0<<LCDEN);
}

void writeChar(char ch, int pos) {
	if (pos < 0 || pos > 5) {
		return; // do nothing if pos is outside the supported range
	}
	if (ch < '0' || ch > '9') {
		ch = ' '; // display a blank for anything outside 0 - 9
	}
	
int main(void)
{
	CLKPR = 1000000000000000;
	// probably same as doing
	//CLKPR = (1 << CLKPCE); 
	//CLKPR = 0x00;

