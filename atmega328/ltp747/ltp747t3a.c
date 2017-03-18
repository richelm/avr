/*
 * ATMEGA328 LTP747 Test 3
 * File: ltp747t3.c
 * Date: 3/4/2017
 * 
 * Test displaying character segments on the anode rows of the LTP747.
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
#define AR0		PC0
#define AR1		PC1
#define AR2		PC2
#define AR3		PC3
#define AR4		PC4

#define MAXSIZE 5
const unsigned char bitmap[MAXSIZE] = {0x0F,0x14,0x14,0x0F,0x00};

void displaySegment(uint8_t seg) {
	int msecsDelayPost = 250;
	uint8_t s;
	
	for (s = 0; s < 5; s++) {
		if (seg & (1 << s)) {
			PORTC ^= (1 << s);
			_delay_ms(msecsDelayPost);
			PORTC ^= (1 << s);
		}
	}
	
	return;
}

int main(void) {
	uint8_t i;       // general loop counter
	uint8_t j;       // general loop counter
	uint8_t bmapidx; // index to bitmap
	uint8_t segment; // bitmap segment to be displayed in buffer
	
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));

	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR0) | (1 << AR1) | (1 << AR2)
			| (1 << AR3)| (1 << AR4));

	// Set PB0 as output
	DDRB |= (1 << PB0);
	PORTB &= ~(1 << PB0);
	
	// clear the anode rows
	PORTC &= ~((1 << AR0) | (1 << AR1)
		| (1 << AR2)| (1 << AR3)| (1 << AR4));
		
    while (1) {
		bmapidx = 0;
		while (bmapidx < 4) {
			segment = bitmap[bmapidx];

			// clear 4051 CBA input address pins 
			PORTD &= ~((1 << A) | (1 << B) | (1 << C));
			// set 4051 CBA input address pins
			PORTD |= (bmapidx+1 << 2); // shift 2 to skip PD0 and PD1
			
			if (segment > 30) {
				for (j = 0; j < 3; j++) {
					PORTB ^= (1 << PB0);
					_delay_ms(500);
					PORTB ^= (1 << PB0);
					_delay_ms(500);
				}
			}
			displaySegment(segment);

			bmapidx++;
			
		}
    }
 
    return 0;
}
