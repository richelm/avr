/*
 * ATMEGA328 LED Flasher
 * File: blink328.c
 */


#define F_CPU 1000000  // 1.0 MHz (8MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

#define LED1	PB1
#define LED2	PB2

int main(void)
{
    const int msecsDelayPost = 500;
 
    // Set up Port B pins 1 and 2 mode to output
    DDRB |= ((1 << LED1) | (1 << LED2));

    // Initialize Port B data to be all low
    PORTB = 0;  
 
    while (1) {
        PORTB ^= (1 << LED1);	// LED1 on
        _delay_ms (msecsDelayPost);
        PORTB ^= (1 << LED1);	// LED1 off
        PORTB ^= (1 << LED2);	// LED2 on
        _delay_ms (msecsDelayPost);
        PORTB ^= (1 << LED2);	// LED2 off
    }
 
    return 0;
}
