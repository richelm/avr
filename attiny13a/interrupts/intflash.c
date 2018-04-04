/*
 * ATtiny13 LED Flasher and PCINT0 external enterupt
 * File: tiny13int1.c
 *
 * NOTE: 
 * Code is written assuming that circuit is wire with pins
 * driving LEDs are sinking not sourcing to turn on LED.
 *
 * Reference/acknowledgement:
 *  http://brownsofa.org/blog/archives/215
 *
 */// FILE: int1.c
// Look for interrupt on PCINT4 (pin 3; PB4)

#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

// attiny13a has brown-out detector control register
#define BODSE 0
#define BODS 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

const int msecsDelay450 = 450;
const int msecsDelay250 = 250;


ISR(INT0_vect)
{
	
	// toggle LED at PB2
	PORTB ^= _BV(PB2);
}


int main(void) {
    // Set up PB2
    DDRB = _BV(DDB2);
    
    // Initialize Port B data to be all low
    // and toggle pin 2 turning it off
   	PORTB = 0;  
   	PORTB ^= _BV(PB2);	
	
	// PCIE enabled
	GIMSK = _BV(PCIE);
	
	// set pin change interrupt for PCINT3 (pin 2)
	PCMSK = _BV(PCINT3);
	
	sei(); // Enable global interrupts 

	for (;;) {
	  // Waiting for interrupt...
	}
	
}
