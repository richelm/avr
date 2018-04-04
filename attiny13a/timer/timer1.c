/*
 * Code for ATTINY13A example using timer
 * Toggle LED on PB2 about 1 per second
 * 
 */
 
#define F_CPU 1000000UL // 1 MHz

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED			PB2
#define MAX_DELAY	60

// global variables
volatile uint8_t g_counter = 0;

void setup() {
	// setup LED
	DDRB |= (1 << LED);
	PORTB &= ~(1 << LED);
	
	// setup timer0
	TCCR0A |= (1<<WGM01) ; // set the timer to CTC mode.
	TCCR0B |= ((1<<CS01)|(1<<CS00)) ; // use Fcpu/64 tickrate
	//TIMSK0 |= (1 << TOIE0) ; // Enable the overflow interrupt
	TIMSK0 |= (1 << OCIE0A) ; // Enable the compare match A interrupt
	
	sei();
	
	// initializations
	g_counter = 0;
	OCR0A = 254;
}

ISR(TIM0_COMPA_vect) {
	g_counter++;
}

int main(void) {
	
	setup();
	
	while(1) {
		if (g_counter >= MAX_DELAY) {
			g_counter = 0;
			PORTB ^= (1 << LED); // toggle LED
		}
	}
	
	return 0;
}
	
