/*
 * ATtiny13 LED Flasher using WDT
 * File: tiny13f3.c
 *
 * Reference/acknowledgement:
 *  http://brownsofa.org/blog/archives/215
 *
 */

#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

const int msecsDelayPost = 1000;

ISR(WDT_vect) {
	int j = 0;
	for (j = 16; j > 1; j = j/2)
	{
		PORTB = j;
		_delay_ms (msecsDelayPost);
	}	
}
 
int main(void) {
	
	int i = 0;
	
    // Set up PB2
    DDRB = _BV(DDB2);
    
   	// set PORTB off
	PORTB = 0x00;
   	
	// prescale timer to ~2.0s
	//WDTCR |= (1<<WDP2) | (1<<WDP1) | (1<<WDP0);

	// prescale timer to ~4.0s
	//WDTCR |= (1<<WDP3);
	
	// prescale timer to ~8.0s
	//WDTCR |= (1<<WDP3) | (1<<WDP0);
	
	// Enable watchdog timer interrupts
	//WDTCR |= (1<<WDTIE);

	//sei(); // Enable global interrupts 


	while (1)
	{
		for (i = 1; i < 16; i = i*2)
		{
			PORTB = i;
			_delay_ms (msecsDelayPost);
		}

	}
	return 1;
}
