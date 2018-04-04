// FILE: int0.c
// ATTiny13A
// Look for interrupt on on INT0 (pin 6/PB1)


#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// define ISR for INT0
ISR(INT0_vect)
{
   	// toggle LED at PB2
	PORTB ^= (1<<PB2);
}

int main(void) {
    // set PB2, PB3, and PB4 as OUTPUT; PB0, PB1 and PB5 as INPUT
    DDRB = 0b00011100;

    // enable external interrupt on INT0 (pin 6/PB1)
    GIMSK = (1<<INT0);  //_BV(INT0);   // Enable External Interrupt Request 0 
    MCUCR = (1<<ISC01); //_BV(ISC01);    // Falling edge of INT0 generates the interupt

    // enable external interrupt on PCINT4
    // NOTE: the ISR vector is still PCINT0_vect. Need to check, if need to know
    //GIMSK = _BV (PCIE);
    //PCMSK = _BV (PCINT4);

    sei();                  // int - Global enable interrupts

    while (1) {
        // Toggle PB3
        PORTB |= (1<<PB3);  // set bit 3
        _delay_ms (500);
        PORTB &= ~(1<<PB3); // clear bit 3
        _delay_ms (500);
    }

}

