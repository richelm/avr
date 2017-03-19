/*
 * FILE: test1.c
 * 
 * Testing array of letter segments
 * 
 * PORTC PC0 - PC4 used to drive LEDs
 * 328    LTP747R
 * PC0 -- AR1
 * PC1 -- AR2
 * PC2 -- AR3
 * PC3 -- AR4
 * PC4 -- AR5
 * 
 */
 
#define F_CPU 1000000	// 1 MHz

// LTP747R anode row pins
#define AR1		PC0
#define AR2		PC1
#define AR3		PC2
#define AR4		PC3
#define AR5		PC4

#define msecsDelayPost 500

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>

const unsigned char segments[4] = {0x15,0x0A,0x15,0x0A};
	
void setup() {
	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
		
	// set them all low
	PORTC &= ~((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
}

int main (void) {
	unsigned char seg;
	uint8_t i = 0;

	setup();
	while(1) {
		for (i = 0; i < 4; i++) {
			seg = pgm_read_byte(&(segments[i]));
			PORTC ^= (seg << 0);
			_delay_ms (msecsDelayPost);
			PORTC ^= (seg << 0);
			_delay_ms (msecsDelayPost);
		}
	}
}
