// FILE: sleep.c
// ATTiny13A
// Put tiny13 to sleep and wake up from an interrupt 
// on INT0 (pin 6/PB1)


#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>

int i = 0;
//register unsigned char counter asm("r0");
//volatile unsigneed char counter;
int ones = 0;
int tens = 0;
int clickCnt = 0;

// define ISR for INT0
ISR(INT0_vect)
{
    asm("nop");
}

void setup(void) {
    // set PB2, PB3, and PB4 as OUTPUT; PB0, PB1 and PB5 as INPUT
    DDRB = 0b00011100;

    // enable external interrupt on INT0 (pin 6/PB1)
    GIMSK = (1<<INT0);  // Enable External Interrupt Request 0 
    //MCUCR = (1<<ISC01); // Falling edge of INT0 generates the interupt
    // bit 1:0 of MCUCR define the INT0 sense control
    // we want to wake from SLEEP_MODE_PWR_DOWN we need to set
    // interupt at low level. Both OSC01 and ISC00 need to be zero
    MCUCR &= 0b11111100;

    // turn on status LED
    PORTB = (1<<PB2);
}

void sleepNow(void) {
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);
   //set_sleep_mode(SLEEP_MODE_IDLE);
   sleep_enable();
   PORTB ^= (1<<PB2); //OFF

   sei();      // Enable Global enable interrupts (Set SE bit)
   sleep_cpu();
   sleep_disable();
   
   PORTB ^= (1<<PB2); //ON
   cli();      // Clear SE bit
}

void blinkLEDS(void) {
	_delay_ms (1000);

	clickCnt++; 	
	ones = clickCnt % 10;
	tens = clickCnt / 10;

   // flash PB4 (tens)
   for (i = 1; i <= tens; i++) {
		PORTB |= (1<<PB4);  // set bit 4
		_delay_ms (250);
		PORTB &= ~(1<<PB4); // clear bit 4    
		_delay_ms (250);
   }

	_delay_ms (250);
   // flash PB3 (ones)
   for (i = 1; i <= ones; i++) {
		PORTB |= (1<<PB3);  // set bit 3
		_delay_ms (250);
		PORTB &= ~(1<<PB3); // clear bit 3
		_delay_ms (250);
   }
}        

int main(void) {
    setup();

    while (1) {
        blinkLEDS();
        sleepNow();
    }

}

