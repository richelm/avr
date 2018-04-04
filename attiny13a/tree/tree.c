/*
 * ATtiny13 LED Flasher
 * File: tree.c
 */

//#define F_CPU 8000000UL  // 1 MHz
#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	uint8_t c = 0;
	uint8_t p = 0;
	uint8_t i = 0;
	
	const int msecsDelayPost = 200;
	
	// set PORTB pins PB0 - PB4 for output; 
	// not using PB5/RESET due to ISP programming issue
	DDRB = 0x1F;
	
	// set PORTB off
	PORTB = 0x1F;
	while (1)
	{
		p = 16;
		for (c = 1; c <= 16; c = c*2)
		{
			PORTB = ~c;
			_delay_ms (msecsDelayPost);
			PORTB = ~p;
			_delay_ms (msecsDelayPost);
			
			i++;
			if (i == 127) {
				p = 8;
			}
			else if (i == 173) {
				p = 4;
				i = 0;
			}
			else {
				p = c;
			}
		}
	}
	return 1;
}
