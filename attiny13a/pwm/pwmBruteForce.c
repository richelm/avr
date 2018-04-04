#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

#define LED_DELAY 3
#define MAX_BRIGHTNESS 175
#define msecsDelayPost 500

void pwm(uint8_t led) {
	uint8_t i;
	uint8_t brightness;
	
	// bright
	for (brightness = 1; i <= MAX_BRIGHTNESS; brightness++) {
		for (i = 0; i < 255; i++) {
			if (i < brightness) {
				PORTB ^= 1<<led;
			} else {
				PORTB = 0;
			}
			_delay_us(LED_DELAY);
		}
	}

	// dim
	for (brightness = MAX_BRIGHTNESS; i > 0 ; brightness--) {
		for (i = 0; i < 255; i++) {
			if (i < brightness) {
				PORTB ^= 1<<led;
			} else {
				PORTB = 0;
			}
			_delay_us(LED_DELAY);
		}
	}
}

int main(void) {
	
	// ***** inits ***** //
	
	// set LED[0-2] for output
	LED_DDR = 0x03;
	
	while (1) {
		pwm(LED0);
		//pwm(LED1);
		
		//PORTB ^= (1<<LED2)
	}

	return (0);
}
	
