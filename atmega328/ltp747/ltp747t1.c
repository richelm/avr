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

#define INA		PD2
#define INB		PD3
#define INC		PD4

int main(void)
{
	uint8_t i;
	
    const int msecsDelayPost = 500;
 
    // Set up Port D pins 2, 3, and 4 as output
    DDRD |= ((1 << INA) | (1 << INB) | (1 << INC));

    // Initialize A, B, C on 4051 to low
    PORTD &= 0b11100011;  
 
    while (1) {
		for (i = 1; i < 8; i++) {
			PORTD ^= (1 << INA);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			PORTD ^= (1 << INB);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			PORTD ^= (1 << INB);
			PORTD ^= (1 << INC);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			PORTD ^= (1 << INB);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			_delay_ms (msecsDelayPost);
			PORTD ^= (1 << INA);
			PORTD ^= (1 << INB);
			PORTD ^= (1 << INC);
			_delay_ms (msecsDelayPost);
		}
    }
 
    return 0;
}
