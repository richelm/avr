/*
 * Target AVR: ATtiny13a
 * Flash RGB LED on PORTB[0-2]
 * 
 * File: sonobe_light.c
 *
 *
 * Reference/acknowledgement:
 *  1. http://www.fourwalledcubicle.com/  See timer article.
 *  2. Make AVR Programming by Elliot Williams
 *
 * NOTE: 
 * Add PWM effects by un-commenting OCROA setting in TIM0_OVR_vect and
 * the FOR loop in main event loop.
 * 
 */

#define F_CPU 1200000UL  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DELAY 2

volatile uint8_t brightnessA;
volatile uint8_t rgb;
volatile uint8_t cycles = 0;

// -------- Functions --------- //
static inline void initTimer0(void) {
	TCCR0B |= (1 << CS01) | (1 << CS00);                   // F_CPU / 64
	TIMSK0 |= (1 << OCIE0A);                           // COMP A enabled
	TIMSK0 |= (1 << TOIE0);                 // overflow interrupt enable
	OCR0A = 55;
	sei();
}

ISR(TIM0_OVF_vect) {
	PORTB = rgb;                    // change the color; TURN ON RGB LED
	// un-comment for PWM effects
	//OCR0A = brightnessA;                               // set brightness
}

ISR(TIM0_COMPA_vect ) {
	PORTB = 0;						                 // TURN OFF RGB LED
	cycles++;
	if (cycles == 251) {
		rgb = (++rgb % 7) + 1;
		cycles = 0;
	}	
}

int main(void) {
	// -------- Inits --------- //
	uint8_t i;
	uint8_t min = 25;
	uint8_t max = 200;
	
	DDRB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));	// enable PB[0-2] as output
	PORTB = 0;
	
	initTimer0();
	rgb = 1;
	
	while (1) {
	// un-comment for PWM effects
/** 
		for (i = min; i <= max; i++) {
		  _delay_ms(DELAY);
		  brightnessA = i;
		}

		for (i = max; i >= min; i--) {
		  _delay_ms(DELAY);
		  brightnessA = i;
		}
*/
	}												/* End event loop */
	
	return (0);                         /* This line is never reached */
}
