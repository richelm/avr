/*
 * ATMEGA328 LTP747 Test 1
 * File: ltp747t1.c
 * Date: 3/4/2017
 * 
 * 328    4051
 * PD2 -- Pin 11 A
 * PD3 -- Pin 10 B
 * PD4 -- Pin  9 C
 * 
 */


#define F_CPU 1000000  // 1.0 MHz (8MHz / 8)

#include <avr/io.h>
#include <util/delay.h>

// 4051 CBA input address pins
#define A		PD2
#define B		PD3
#define C		PD4

int main(void)
{
	uint8_t i;
	
    const int msecsDelayPost = 500;
 
    // Set 4051 CBA input address pins as output
    DDRD |= ((1 << A) | (1 << B) | (1 << C));

    while (1) {
		for (i = 7; i > 0; i--) {
			// clear 4051 CBA input address pins 
			PORTD &= ~((1 << A) | (1 << B) | (1 << C));
			// set 4051 CBA input address pins
			PORTD |= (i << 2);
			_delay_ms (msecsDelayPost);
		}
    }
 
    return 0;
}
