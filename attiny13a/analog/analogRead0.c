 /* -----------------------------------------------------------------------
 * Title: Analog read example (Analog input change led brightness)
 * Hardware: ATtiny13v
 * Software: WinAVR 20060421
 * -----------------------------------------------------------------------*/
 
 #define F_CPU 9600000 // Define software reference clock for delay duration
 
 #include <avr/io.h>
 #include <util/delay.h>
 
 #define LED PB2 // Define led ext output pin on PB2
 
 int i; // 8 bits integer
 
 
 int main(void)
 
 {
 
	 DDRB |= (1 << LED); // Set output direction on LED
	 ADCSRA |= (1 << ADEN)| // Analog-Digital enable bit
	 (1 << ADPS1)| // set prescaler to 8 (clock / 8)
	 (1 << ADPS0); // set prescaler to 8 (clock / 8)
	 
	 ADMUX |= (1 << ADLAR)| // AD result store in (more significant bit in ADCH)
	 (1 << MUX1); // Choose AD input AD2 (PB4)
 
	 for (;;)
	 {
	 
		 ADCSRA |= (1 << ADEN); // Analog-Digital enable bit
		 ADCSRA |= (1 << ADSC); // Discarte first conversion
		 
		 while (ADCSRA & (1 << ADSC)); // wait until conversion is done
		 
		 ADCSRA |= (1 << ADSC); // start single conversion
		 
		 while (ADCSRA & (1 << ADSC)) // wait until conversion is done
		 
		 ADCSRA &= ~(1<<ADEN); // shut down the ADC
		 
		 //----------Show ADCH Byte in Led variable brightness indicator---------
		 
		 for (i = 0 ; i < ADCH ; i++) // Loop x time until i reach ADCH value
		 {
		 	_delay_ms (10); // Loop delay
		 }
		 
		 PORTB ^= (1 << LED); // Inverte led bit and show it
	 }
	 return 0;
 }
