/*
 * ATtiny13 LED Flasher
 * File: tiny13f1.c
 */

//#define F_CPU 8000000UL  // 1 MHz
#define F_CPU 1000000  // 1.0 MHz (8MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

#define LED		PB4

int main(void)
{
    const int msecsDelayPost = 500;
 
    // Set up Port B pin 0 mode to output
    DDRB = (1 << LED);

    // Initialize Port B data to be all low
    PORTB = 0;  
 
    while (1) {
        // Toggle Port B pin 0 output state
        PORTB ^= (1 << LED);
        _delay_ms (msecsDelayPost);
    }
 
    return 0;
}
