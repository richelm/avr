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
