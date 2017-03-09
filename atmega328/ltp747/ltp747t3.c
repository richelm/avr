/*
 * ATMEGA328 LTP747 Test 3
 * File: ltp747t3.c
 * Date: 3/4/2017
 * 
 * This test scrolls a letter A line across the matrix from right to 
 * left.
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

int main(void) {
	uint8_t i;       // general loop counter
	uint8_t colidx;  // used to loop through buffer columns
	uint8_t chridx;  // used to index character segments
	uint8_t r;
	uint8_t n;
	uint8_t rlc;
	unsigned char buffer[7];
	
    const int msecsDelayPost = 5;
    const int rowLoopCount = 7;
	const unsigned char letter[5] = {15,20,20,15,00};
	
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));

	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
	
	chridx = 0;
    while (1) {
		// load buffer
		for (i = 6; i < 255; i--) {
			buffer[i] = letter[chridx];
			chridx++;
			if (chridx > 4) {chridx = 0;}
		}
		// loop through the cathode columns
		for (i = 7; i > 0; i--) {
			colidx = i - 1;
			// clear 4051 CBA input address pins 
			PORTD &= ~((1 << A) | (1 << B) | (1 << C));
			// set 4051 CBA input address pins
			PORTD |= (i << 2); // shift 2 to skip PD0 and PD1
						
			// loop through anode rows
			for (rlc = 1; rlc < rowLoopCount; rlc++) {
				n = 1;
				for (r = 4; r < 255; r--) {
					// clear anode row pins
					PORTC &= ~((1 << AR1) | (1 << AR2)
							| (1 << AR3)| (1 << AR4)| (1 << AR5));
					// set anode row
					if ((buffer[colidx] & n) > 0) {
						PORTC |= (1 << n);
						_delay_ms (msecsDelayPost);
					}
					n = n * 2;
				}
			}
		}
    }
 
    return 0;
}
