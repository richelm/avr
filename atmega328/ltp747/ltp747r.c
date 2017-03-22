/*
 * ATMEGA328 LTP747 Test 3
 * File: ltp747r.c
 * Date: 3/18/2017
 * 
 * Display a character.
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
 * PC0 -- AR1
 * PC1 -- AR2
 * PC2 -- AR3
 * PC3 -- AR4
 * PC4 -- AR5
 * 
 */


#define F_CPU 1000000UL // 1.0 MHz (8MHz / 8)

// 4051 CBA input address pins
#define A		PD2
#define B		PD3
#define C		PD4

// LTP747R anode row pins
#define AR1		PC0
#define AR2		PC1
#define AR3		PC2
#define AR4		PC3
#define AR5		PC4

#define MAXLEN			31
#define MSECSDELAYPOST	 1
#define ROWLOOPCOUNT	25

// inlcudes
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>

const unsigned char buffer[7] = {0x0F,0x14,0x14,0x0F,0x1D,0x00,0x00};
	
int main(void) {
	uint8_t i;
	uint8_t r;
	uint8_t s;
	uint8_t rlc;
	int8_t seg;
	int8_t dummy;
	
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));
	// clear 4051 CBA input address pins 
	PORTD &= ~((1 << A) | (1 << B) | (1 << C));
	
	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
	// clear anode row pins
	PORTC &= ~((1 << AR1) | (1 << AR2)
			| (1 << AR3)| (1 << AR4)| (1 << AR5));

	dummy = 0;
	// main event loop
    while (1) {
		// loop through the cathode columns
		for (i = 7; i > 0; i--) {
			// set 4051 CBA input address pins
			PORTD |= (i << 2); // shift 2 to skip PD0 and PD1

			seg = buffer[i-1];
			
			for (rlc = 1; rlc < ROWLOOPCOUNT; rlc++) {
				for (r = 0; r < 5; r++) {
					PORTC |= (seg & (1 << r));
					//_delay_ms (MSECSDELAYPOST);
					PORTC &= ~(seg & (1 << r));
					//~ if (seg & (1 << r)) {
						//~ PORTC ^= (1 << r);
						//~ dummy = (dummy+1) % 7;
						//~ PORTC ^= (1 << r);
					//~ } else {
						//~ //_delay_ms (MSECSDELAYPOST);
					//~ }
				}
			}
			// clear 4051 CBA input address pins
			PORTD &= ~(i << 2); // shift 2 to skip PD0 and PD1
		}
    }
 
    return 0;
}
