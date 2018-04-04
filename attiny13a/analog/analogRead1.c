/*
 * ATtiny13 Analog Read ADC3 (PB3, Pin2)
 * File: tiny13f1.c
 */

//#define F_CPU 8000000UL  // 1 MHz
#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

 
int main(void)
{
	const int msecsDelayPost = 250;
	unsigned char result;


}


	// Choose AREF pin for the comparison voltage
	//   (it is assumed AREF is connected to the +5V supply)
	// Choose channel 3 in the multiplexer
	// Left align the result
	ADMUX = (1 << REFS0) | (1 << ADLAR) | (3);

	// Start the ADC unit,
	// set the conversion cycle 16 times slower than the duty cycle
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADSC);

	// Wait for the measuring process to finish
	while (ADCSRA & (1 << ADSC)) continue;

	// Read the 8-bit value
	result = ADCH;
 
int main(void)
{
    const int msecsDelayPost = 250;
 
    // Set up Port B pin 0 mode to output
    DDRB = (1<<DDB5);

    // Initialize Port B data to be all low
    PORTB = 0;  
 
    while (1) {
        // Toggle Port B pin 0 output state
        PORTB ^= 1<<PB5;
        _delay_ms (msecsDelayPost);
    }
 
    return 0;
}
