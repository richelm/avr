/*
 * FILE: thermometer.c
 * 
 * C program targeted for the Atmel ATTINY13a (tiny13) microcontroller.
 * This project will interface the tiny13 to a TMP36 analog temperature
 * sensor and display the temperature in an RGB LED. The RGB LED will 
 * flash RED for tens and GREEN for ones digit of the number. If flashing
 * begins with BLUE, then the number represented by the flashing of RED
 * and GREEN is negative. Using this scheme we can represent any number
 * from -99 to +99. Since we will be measuring temperatures in degrees
 * Celsius, this will be satisfactory. A push button switch will also be
 * attached to one of the pins of the tiny13 to be used to initiate a
 * temperature reading.
 *
 */

#define F_CPU 600000  // 128kHz internal clock; lfuse = 0x73

#include <avr/io.h>
#include <util/delay.h>

// RGB LED pins
#define LED_RED PB2
#define LED_GREEN PB1
#define LED_BLUE PB0

// push button switch
#define PUSH_BUTTON PB3

#define FLASH_DURATION_MS 250

void flash_led(uint8_t LED, uint8_t times)
{
	uint8_t i;

	for (i=0; i<times; i++) {
		PORTB |= (1<<LED);
		_delay_ms (FLASH_DURATION_MS);
		PORTB &= ~(1<<LED);
		_delay_ms (FLASH_DURATION_MS);
	}

	// make sure PIN is low
	PORTB &= ~(1<<LED);
}


void displayTemperature(int temp)
{
	int ones;
	int tens;
	uint8_t i;

	ones = abs(temp) % 10;
	tens = abs(temp) / 10;

	// display the temperature 3 times
	for (i=0; i<3; i++) {  
		// flash LED_BLUE if negative temperature
		if (temp < 0) {
			flash_led(LED_BLUE,1);
		}

		// flash LED_RED (TENS digit)
		flash_led(LED_RED, tens);
		
		_delay_ms(500);
		
		// flash LED_GREEN (ONES digit)
		flash_led(LED_GREEN, ones);
		
		_delay_ms(500);
	}
}
 
void setup()
{
	// RGB LED pins as OUTPUT
	DDRB |= ((1<<LED_RED) | (1<<LED_GREEN) | (1<<LED_BLUE));

	// PUSH_BUTTON pin as INPUT
	DDRB &= ~(1<<PUSH_BUTTON);

	// setup ADC
	DIDR0 |= (1 << ADC2D);	// disable digital input on ADC2 (PB4) saves power
	ADMUX |= (1 << MUX1);	// read TMP36 on ADC2 (PB4)
	ADCSRA |= (1 << ADPS2);	// ADC clock prescaler /16
	ADCSRA |= (1 << ADEN);	// enable ADC
}


int main(void)
{
	setup();
	
	int adcValue = 0;
	int voltageInt = 0;
	float voltage = 0.0;
	
	// Initialize Port B data to be all low
	PORTB = 0;  

	while (1) {

		//ADCSRA |= (1 << ADSC);                /* start ADC conversion */
		//loop_until_bit_is_clear(ADCSRA, ADSC);     /* wait until done */

		//adcValue = ADC; 
		//voltage = adcValue * 5.0;
		//voltage /= 1024.0; 

		//voltageInt = (int)(voltage + 0.5);
		
		voltageInt = 23;
		// display the temperature on RGB LED
		displayTemperature(voltageInt);

		//PORTB |= (1<<LED_RED); 
		//_delay_ms(500);
		//PORTB &= ~(1<<LED_RED);
		
		//PORTB |= (1<<LED_GREEN); 
		//_delay_ms(500);
		//PORTB &= ~(1<<LED_GREEN);
			
		//PORTB |= (1<<LED_BLUE); 
		//_delay_ms(500);
		//PORTB &= ~(1<<LED_BLUE);
		
		
		_delay_ms(1000);
		
		voltageInt = -17;
		// display the temperature on RGB LED
		displayTemperature(voltageInt);
		_delay_ms(1000);
	}

	return 0;
}
