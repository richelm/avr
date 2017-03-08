/*
 * ATMEGA328 LTP747 Sign
 * File: ltp747.c
 * Date: 3/4/2017
 * 
 * The LTP747R has anode columns and cathode rows in 5X7 orientation.
 * Here the LTP747R is being displayed sideways 7x5, we have anode rows
 * and cathode columns.
 * 
 * 328    4051
 * PD2 -- Pin 11 A
 * PD3 -- Pin 10 B
 * PD4 -- Pin  9 C
 * 
 * 328    LTP747R
 * PC1 -- AR1
 * PC2 -- AR2
 * PC3 -- AR3
 * PC4 -- AR4
 * PC5 -- AR5
 * 
 */


#define F_CPU 1000000  // 1.0 MHz (8MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

// 4051 CBA input address pins
#define A		PD2
#define B		PD3
#define C		PD4

// LTP747R anode row pins
#define AR1		PC1
#define AR2		PC2
#define AR3		PC3
#define AR4		PC4
#define AR5		PC5

// message to display; 15 character MAX; must be define as global constant
const char	mesg[] PROGMEM = "HELLO WORLD ";

// valid letters in message
const unsigned char  letters[27][5] PROGMEM = {
	{00,00,00,00,00,},  // space
	{15,20,20,15,00,},  // A
	{31,21,21,10,00,},  // B
	{14,17,17,17,00,},  // C
	{31,17,17,14,00,},  // D
	{31,21,21,17,00,},  // E
	{31,20,20,16,00,},  // F
	{14,17,21,06,00,},  // G
	{31,04,04,31,00,},  // H
	{17,31,17,00,00,},  // I
	{02,01,30,00,00,},  // J
	{31,04,10,17,00,},  // K
	{31,01,01,00,00,},  // L
	{31,08,04,08,31,},  // M
	{31,08,04,02,31,},  // N
	{14,17,17,17,14,},  // O
	{31,20,20,28,00,},  // P
	{14,17,17,14,01,},  // Q
	{31,20,20,11,00,},  // R
	{09,21,21,18,00,},  // S
	{16,31,16,00,00,},  // T
	{30,01,01,30,00,},  // U
	{28,02,01,02,28,},  // V
	{31,02,04,02,31,},  // W
	{17,10,04,10,17,},  // X
	{16,08,07,08,16,},  // Y
	{17,19,21,25,00,}   // Z
}

int main(void) {
	uint8_t i;    // general purpose loop counter
	unit8_t cidx; // index character column segments
	uint8_t r;
	uint8_t rlc;
	unsigned char segments[7];
	
    const int msecsDelayPost = 5;
    const int rowLoopCount = 15;
 
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));

	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
	
	// initialize columns[] to be off
	for	(i = 0; i < 7; ++i) {
		segments[i] = 0x00;
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
			for (j = 0; j < 5; ++j) {
				segments[0] = segments[1];
				segments[1] = segments[2];
				segments[2] = segments[3];
				segments[3] = segments[4];
				segments[4] = segments[5];
				segments[5] = segements[6];
				segments[6] = pgm_read_byte(&(letters[ltr][j]));
				
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










	
    while (1) {
		// loop through the cathode columns
		for (i = 7; i > 0; i--) {
			// clear 4051 CBA input address pins 
			PORTD &= ~((1 << A) | (1 << B) | (1 << C));
			// set 4051 CBA input address pins
			PORTD |= (i << 2); // shift 2 to skip PD0 and PD1
			
			// loop through anode rows
			for (rlc = 1; rlc < rowLoopCount; rlc++) {
				for (r = 5; r > 0; r--) {
					// clear anode row pins
					PORTC &= ~((1 << AR1) | (1 << AR2)
							| (1 << AR3)| (1 << AR4)| (1 << AR5));
					// set anode row
					PORTC |= (1 << r);
					_delay_ms (msecsDelayPost);
				}
			}
			

		}
    }
 
    return 0;
}
