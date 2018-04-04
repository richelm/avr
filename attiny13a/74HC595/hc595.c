/*
 * Code for ATTINY13A interfacing to the 74HC595 shift register.
 * 
 * Connections [pin # (function)]
 * 	 ATTINY13A      74HC595
 *    1 (reset)       16 (VCC)
 *    2 (PB3) -----   11 (SRCLK)          DATA_CLOCK_PIN
 *    3 (PB4) -----   14 (SER)            DATA_PIN
 *    4 (GND)         13 (OE)    --- GND
 *    5 (PB0)         10 (SRCLR) --- VCC
 *    6 (PB1) 
 *    7 (PB2) -----   12 (RCLK)           LATCH_PIN
 *    8 (VCC)          8 (GND)
 * 
 */
 
#define F_CPU 1000000UL // 1 MHz

#include <avr/io.h>
#include <util/delay.h>


// define pins
#define HC595_DDR		DDRB
#define HC595_PORT		PORTB
#define DATA_PIN 		PB4
#define DATA_CLOCK_PIN	PB3
#define LATCH_PIN		PB2

void toggleDataClockPin() {
	HC595_PORT |= (1 << DATA_CLOCK_PIN);  // set high
	HC595_PORT &= ~(1 << DATA_CLOCK_PIN); // set low
}

void toggleLatchkPin() {
	HC595_PORT |= (1 << LATCH_PIN);  // set high
	_delay_ms(3);
	HC595_PORT &= ~(1 << LATCH_PIN); // set low
	_delay_ms(3);
}
	
void writeData(uint8_t data) {
	uint8_t i;
	// shifting LSB first; found this works QA to QH wired 
	// left to right
	for(i = 0; i < 8; i++) {
		/* Write bit to data port. */
		if (0 == (data & (1 << i))) {
//		if (0 == (data & _BV(7 - i))) {  // MSB first
			HC595_PORT &= ~(1 << DATA_PIN);  // set low
		} else {
			HC595_PORT |= (1 << DATA_PIN);  // set high
		}

		/* Pulse data clock pin to write next bit. */
		toggleDataClockPin();
	}
	
	// toggle latch pin (RCLK) to write data to storage register
	toggleLatchkPin();
}

void setup() {
	// setup communication pins to HC595 for output
	HC595_DDR |= (1 << DATA_PIN);
	HC595_DDR |= (1 << DATA_CLOCK_PIN);
	HC595_DDR |= (1 << LATCH_PIN);
	
	// set all communication pins low
	HC595_PORT &= ~(1 << DATA_PIN); 
	HC595_PORT &= ~(1 << DATA_CLOCK_PIN); 
	HC595_PORT &= ~(1 << LATCH_PIN);
}

int main(void) {
	uint8_t dataOut;
	
	setup();

	while(1) {
/*
		dataOut = 0b01010101;
		writeData(dataOut);
		_delay_ms(750);
		
		//writeData(0x00);
		
		dataOut = 0b10101010;
		writeData(dataOut);
		_delay_ms(750);
*/
		for (dataOut = 0; dataOut < 256; dataOut++) {
			writeData(dataOut);
			_delay_ms(500);
		}
		
		writeData(0x00);
		_delay_ms(500);
	}
	
	return 0;
}
