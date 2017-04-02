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

#define MAXLEN			26		// max message length */
#define MSECSDELAYPOST	 1
#define ROWLOOPCOUNT	10

// inlcudes
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/pgmspace.h>

// message to display; 15 character MAX; must be define as global constant
const char	mesg[] PROGMEM = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// valid letters in message
const unsigned char font[27][5] PROGMEM = {
	{0x00,0x00,0x00,0x00,0x00},  // space
	{0x0F,0x14,0x14,0x0F,0x00},  // A
	{0x1F,0x15,0x15,0x0A,0x00},  // B
	{0x0E,0x11,0x11,0x11,0x00},  // C
	{0x1F,0x11,0x11,0x0E,0x00},  // D
	{0x1F,0x15,0x15,0x11,0x00},  // E
	{0x1F,0x14,0x14,0x10,0x00},  // F
	{0x0E,0x11,0x15,0x06,0x00},  // G
	{0x1F,0x04,0x04,0x1F,0x00},  // H
	{0x11,0x1F,0x11,0x00,0x00},  // I
	{0x02,0x01,0x1E,0x00,0x00},  // J
	{0x1F,0x04,0x0A,0x11,0x00},  // K
	{0x1F,0x01,0x01,0x00,0x00},  // L
	{0x1F,0x08,0x04,0x08,0x1F},  // M
	{0x1F,0x08,0x04,0x02,0x1F},  // N
	{0x0E,0x11,0x11,0x11,0x0E},  // O
	{0x1F,0x14,0x14,0x1C,0x00},  // P
	{0x0E,0x11,0x11,0x0E,0x01},  // Q
	{0x1F,0x14,0x14,0x0B,0x00},  // R
	{0x09,0x15,0x15,0x12,0x00},  // S
	{0x10,0x1F,0x10,0x00,0x00},  // T
	{0x1E,0x01,0x01,0x1E,0x00},  // U
	{0x1C,0x02,0x01,0x02,0x1C},  // V
	{0x1F,0x02,0x04,0x02,0x1F},  // W
	{0x11,0x0A,0x04,0x0A,0x11},  // X
	{0x10,0x08,0x07,0x08,0x10},  // Y
	{0x11,0x13,0x15,0x19,0x00}   // Z
};

void setup(void) {
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));
	// clear 4051 CBA input address pins 
	PORTD &= ~((1 << A) | (1 << B) | (1 << C));
	
	// Set PORTC pins for anode rows as output
	DDRC |= ((1 << AR1) | (1 << AR2) | (1 << AR3)
			| (1 << AR4)| (1 << AR5));
	// set anode row pins low
	PORTC &= ~((1 << AR1) | (1 << AR2)
			| (1 << AR3)| (1 << AR4)| (1 << AR5));
}

// read the next character from the message
uint8_t readNextChar(uint8_t idx) {
	uint8_t l;
	l = pgm_read_byte(&(mesg[idx]));
	if (l == 32)
		l = 0;
	else
		l = l - 64;
	return l;
}

int main(void) {
	uint8_t i;
	uint8_t r;
	uint8_t seg;
	uint8_t mi;    // message index
	uint8_t bi;    // buffer index
	uint8_t ltr;
	uint8_t b;
	
	unsigned char buffer[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
	setup();
	
	// test: put first letter of message in buffer

	mi = 0;
	ltr = readNextChar(mi);
	
	// main event loop
    while (1) {
		// load charater into buffer
		for (bi = 0; bi < 5; bi++) {
			buffer[bi] = pgm_read_byte(&(font[ltr][bi]));
		}
		
		// display the buffer
		for (b = 1; b < 30; b++) {
			// loop through the cathode columns
			for (i = 7; i > 0; i--) {
				// set 4051 CBA input address pins
				PORTD |= (i << 2); // shift 2 to skip PD0 and PD1

				seg = buffer[i-1];
				for (r = 0; r < 5; r++) {
					if (seg & (1 << r)) {
						// toggle anode bit
						PORTC ^= (1 << r); 
						_delay_ms (MSECSDELAYPOST);
						PORTC ^= (1 << r); 
					}
				}
				
				// clear 4051 CBA input address pins
				PORTD &= ~(i << 2); // shift 2 to skip PD0 and PD1
			}
		}
		
		// get next letter
		mi = (mi+1) % MAXLEN;
		ltr = readNextChar(mi);
    }
 
    return 0;
}
