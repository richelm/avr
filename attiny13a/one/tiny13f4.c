/*
 * ATtiny13 LED Flasher using WDT and power save mode
 * File: tiny13f4.c
 *
 * Reference/acknowledgement:
 *  http://brownsofa.org/blog/archives/215
 *
 */

#define F_CPU 8000000UL  // 1 MHz

// attiny13a has brown-out detector control register
#define BODSE 0
#define BODS 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>


ISR(WDT_vect) {
   // Toggle Port B pin 4 output state
   PORTB ^= 1<<PB4;
}
 
int main(void) {
	// Set up Port B pin 4 mode to output
	DDRB = 1<<DDB4;

	// prescale timer to 0.5s
	//WDTCR |= (1<<WDP2) | (1<<WDP0);

	// prescale timer to 4s
	WDTCR |= (1<<WDP3);

	// Enable watchdog timer interrupts
	WDTCR |= (1<<WDTIE);

	//sei(); // Enable global interrupts 

	// Use the Power Down sleep mode
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();

	for (;;) {
		sleep_enable();
		sleep_bod_disable();
		sei();
		sleep_cpu();
		sleep_disable();
	}
	sei();
}

