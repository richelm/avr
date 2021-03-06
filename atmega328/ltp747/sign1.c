/*
 * ATtiny4313 
 * File: tiny4313ltrA.c
 * 
 * This is part of the LTP747R 5x7 LED matrix test suit. Since
 * the LTP747R is Anode row we use negative logic to turn on
 * an LED at the column (cathode).
 *
 * This is the first attempt a generic message "sign". The
 * goal is to display any message up to 15 characters on
 * the LTP747R scroll right to left one character at a time.
 *
 */
 
#define F_CPU 1000000UL	// 1 MHz
#define MAXLEN	15		// max message length */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>


// message to display; 15 character MAX; must be define as global constant
const char	mesg[] PROGMEM = "HELLO WORLD ";

// valid letters in message
const unsigned char  letters[27][6] PROGMEM = {
	{0x7F,0x7F,0x7F,0x7F,0x7F,0x7F},	// space
	{0x03,0x75,0x76,0x75,0x03,0x7F}, //A
	{0x00,0x36,0x36,0x36,0x49,0x7F}, //B
	{0x41,0x3E,0x3E,0x3E,0x5D,0x7F}, //C
	{0x00,0x3E,0x3E,0x3E,0x41,0x7F}, //D
	{0x00,0x36,0x36,0x3E,0x3E,0x7F}, //E
	{0x00,0x76,0x76,0x7E,0x7E,0x7F}, //F
	{0x41,0x3E,0x2E,0x2E,0x4D,0x7F}, //G
	{0x00,0x77,0x77,0x77,0x00,0x7F}, //H
	{0x3E,0x3E,0x00,0x3E,0x3E,0x7F}, //I
	{0x5E,0x3E,0x00,0x7E,0x7E,0x7F}, //J
	{0x00,0x77,0x6B,0x5D,0x3E,0x7F}, //K
	{0x00,0x3F,0x3F,0x3F,0x3F,0x7F}, //L
	{0x00,0x7D,0x7B,0x7D,0x00,0x7F}, //M
	{0x00,0x7B,0x77,0x6F,0x00,0x7F}, //N
	{0x41,0x3E,0x3E,0x3E,0x41,0x7F}, //O
	{0x00,0x76,0x76,0x76,0x79,0x7F}, //P
	{0x41,0x3E,0x3E,0x5E,0x21,0x7F}, //Q
	{0x00,0x76,0x66,0x56,0x39,0x7F}, //R
	{0x59,0x36,0x36,0x36,0x4D,0x7F}, //S
	{0x7E,0x7E,0x00,0x7E,0x7E,0x7F}, //T
	{0x40,0x3F,0x3F,0x3F,0x40,0x7F}, //U
	{0x60,0x5F,0x3F,0x5F,0x60,0x7F}, //V
	{0x00,0x5F,0x6F,0x5F,0x00,0x7F}, //W
	{0x1C,0x6B,0x77,0x6B,0x1C,0x7F}, //X
	{0x7E,0x7D,0x03,0x7D,0x7E,0x7F}, //Y
	{0x1E,0x2E,0x36,0x3A,0x3C,0x7F}	//Z
};
	
int main (void)
{
	const int msecsDelay = 2;
	
	uint8_t	p = 0;
	uint8_t	i = 0;
	uint8_t	j = 0;
	uint8_t	k = 0;
	uint8_t n = 0;	
	uint8_t col = 0;
	uint8_t	ltr;
	unsigned char segments[5];

	// set PORTD pins 6:0 for output
	DDRD = 0x7F;
	
	// set PORTB pins 4:0 for output
	DDRB = 0x1F;
	
	// initialize segments[] to be off
	for	(i = 0; i < 5; ++i) {
		segments[i] = 0x7F;
	}
	
	while (1)
	{
		for (i = 0; (i < MAXLEN && pgm_read_byte(&(mesg[i])) != 0); ++i) {
			ltr = pgm_read_byte(&(mesg[i]));
			if (ltr == 32)
				ltr = 0;
			else
				ltr = ltr - 64;
			
			// loop through segments of the character
			for (j = 0; j < 6; ++j) {
				segments[0] = segments[1];
				segments[1] = segments[2];
				segments[2] = segments[3];
				segments[3] = segments[4];
				segments[4] = pgm_read_byte(&(letters[ltr][j]));
				
				for (p = 0; p < 10; ++p) {
					n = 0;
					col = 1;
					while (n < 5) {
						PORTB = col;
						PORTD = segments[n];
						_delay_ms (msecsDelay);
						col = col * 2;
						n++;
					}
				}
			} // end loop through segments of character
		}
	}
	return 1;
}
