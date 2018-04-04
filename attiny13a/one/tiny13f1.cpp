/*
 * ATtiny13 LED Flasher
 * File: tiny13f1.c
 */

//#define F_CPU 8000000UL  // 1 MHz
#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>
 
int main(void)
{
    const int msecsDelay = 500;
 
    // Set up Port B pin 2
    DDRB = (1<<DDB2);

    // Set up Port B pin 4
    DDRB = (1<<DDB4);
    
    // Initialize Port B data to be all low
    PORTB = 0;  
 
    while (1) {
        // Toggle Port B pin 2 output state
        PORTB ^= 1<<PB2;
		_delay_ms (msecsDelay);
		
        // Toggle Port B pin 4 output state
        PORTB ^= 1<<PB4;
		_delay_ms (msecsDelay);
    }
 
    return 0;
}
