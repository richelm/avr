/***********************************************************************
 * File: bcm1.c
 * uC: attiny13a
 *
 * Simple example of binary coded modulation.
 *
 *
 * Available interupt vectors for the ATTINY13(a)
 * ADC_vect           ADC Conversion Complete
 * ANA_COMP_vect      Analog Comparator
 * EE_RDY_vect        EEPROM Ready
 * INT0_vect          External Interrupt 0
 * PCINT0_vect Pin    Change Interrupt Request 0
 * TIM0_COMPA_vect    Timer/Counter Compare Match A
 * TIM0_COMPB_vect    Timer/Counter Compare Match B
 * TIM0_OVF_vect      Timer/Counter0 Overflow
 * WDT_vect Watchdog  Timeout Interrupt
 * 
 */

#define F_CPU 1000000  // 1.0 MHz

// attiny13a has brown-out detector control register
//#define BODSE 0
//#define BODS 1

#define LED			PB2

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t g_bitpos = 0; // which bit position is currently being shown
volatile uint8_t g_brightness = 0; // brightness
volatile uint8_t g_tick = 0;  

void setup() {
	// setup LEDs
	DDRB |= (1 << LED);
	PORTB &= ~(1 << LED);
	
	// setup timer0
	TCCR0A |= (1<<WGM01) ; // set the timer to CTC mode.
	TCCR0B |= ((1<<CS01)|(1<<CS00)) ; // use clock/64 tickrate
	TIMSK0 |= (1 << OCIE0A) ; // Enable the Compare Match A interrupt
	//TIMSK0 |= (1 << OCIE0B) ; // Enable the Compare Match B interrupt
	
	sei();
	
	// initializations
	g_bitpos = 0;
	g_brightness = 0;
	g_tick = 0;
	OCR0A = 1;
	OCR0B = 200;
}

int main(void) {
	int8_t direction;
		
	setup();
	direction = 1;
	
	while(1) {
		if (g_tick == 1) {
			g_tick = 0;
			g_brightness = g_brightness + direction;
			if (g_brightness == 128) {
				direction = -1;
			}
			if (g_brightness == 1) {
				direction = 1;
			}
		}
	}
}

ISR(TIM0_COMPA_vect) {
	g_bitpos++;
	g_bitpos &= 7;

	if (0 == (g_brightness & (1 << g_bitpos))) {
		PORTB &= ~(1 << LED);
	}
	else {
		PORTB |= (1 << LED);
	}
	
	//TCNT0 = 0;
	OCR0A <<= 1 ;
	if (g_bitpos == 0) OCR0A = 1 ; // reset the compare match value.
	if (g_bitpos == 7) g_tick = 1 ; // give the main loop a kick.
}

