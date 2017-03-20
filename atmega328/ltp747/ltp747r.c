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
#define MSECSDELAYPOST	 5
#define ROWLOOPCOUNT	15

// inlcudes
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>

const unsigned char bitmap[MAXLEN] = {
	0x01,
	0x02,
	0x03,
	0x04,
	0x05,
	0x06,
	0x07,
	0x08,
	0x09,
	0x0A,
	0x0B,
	0x0C,
	0x0D,
	0x0E,
	0x0F,
	0x10,
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x1C,
	0x1D,
	0x1E,
	0x1F};
	
int main(void) {
	uint8_t i;
	uint8_t r;
	uint8_t s;
	uint8_t rlc;
	int8_t seg;
	
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

	// main event loop
    while (1) {
		// loop through the cathode columns
		for (i = 7; i > 0; i--) {
			// set 4051 CBA input address pins
			PORTD |= (i << 2); // shift 2 to skip PD0 and PD1

			// loop through bitmap
			for (s = 0; s < MAXLEN; s++) {
				seg = bitmap[s];
				
				// loop through anode rows
				for (rlc = 1; rlc < ROWLOOPCOUNT; rlc++) {
					for (r = 0; r < 5; r++) {
						if (seg & (1 << r)) {
							PORTC ^= (1 << r);
							_delay_ms (MSECSDELAYPOST);
							PORTC ^= (1 << r);
						} else {
							_delay_ms (MSECSDELAYPOST);
						}
					}
				}
			}
			// clear 4051 CBA input address pins
			PORTD &= ~(i << 2); // shift 2 to skip PD0 and PD1
		}
    }
 
    return 0;
}
