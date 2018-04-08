/*
 * ATtiny13 and 4017 LED Flasher
 * File: d4017.c
 * 
 * Use a ATtiny13a to drive a 4017 IC to sequential light
 * 20 LEDs.
 * 
 *  
 *  ATtiny13a pin connections
 *   pin 3 (PB4) clock connected to pin 14 of 4017
 *   pin 6 (PB1) connected to transistor one
 *   pin 7 (PB2) connected to transistor two
 * 
 * The transistor will turn off/on each bank of 10 LEDs by pulling
 * their common grounds to board ground. 
 *  
 */

//#define F_CPU 8000000UL  // 1 MHz
#define F_CPU 1000000  // 1.0 MHz (8MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

#define T1		PB1
#define T2		PB2
#define CLK		PB4

int main(void)
{
    const int msecsDelayPost = 100;
 
	int	i;
	
    // Set up Port B pins for output mode
    DDRB = ((1 << CLK) | (1 << T1) | (1 << T2));

    // Initialize Port B data to be all low
    PORTB = 0;  
	// turn on T1
	PORTB = (1 << T1);
	
    while (1) {
        // send 10 clock pulses to 4017
        for (i = 0; i < 3; ++i) {
			PORTB ^= (1 << CLK);
			_delay_ms (msecsDelayPost);
			PORTB ^= (1 << CLK);
			_delay_ms (msecsDelayPost);
		}
		// toggle the transistors
		PORTB ^= ((1 << T1) | (1 << T2));
    }
 
    return 0;
}
