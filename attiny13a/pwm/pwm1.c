/*
 * FILE: pwm1.c
 * 2014.08.05
 * 
 * PWM demo to control one LED on an attiny13.
 * 
 * /
                      /* PWM Demo with serial control over three LEDs */


// ------- Preamble -------- //
#define F_CPU 1200000  // 1.2 MHz (9.6MHz / 8)

#define LED_DELAY 200                    /* LED delay in milliseconds */

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"


static inline void initTimers(void) {
	// Timer 0 A
	TCCR0A |= (1 << WGM00);                   /* Fast PWM mode, 8-bit */
	TCCR0A |= (1 << WGM01);                    /* Fast PWM mode, pt.2 */
	//TCCR0B |= (1 << CS11);                  /* PWM Freq = F_CPU/8/256 */
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TCCR0A |= (1 << COM0A1);                   /* PWM output on OCR0A */


}

int main(void) {

  uint8_t brightness;
  
  // -------- Inits --------- //

  initTimers();

              /* enable output on LED pins, triggered by PWM hardware */
  LED_DDR |= (1 << LED0);

  // ------ Event loop ------ //
  while (1) {
  
	for (brightness = 10; brightness < 250; brightness = brightness + 10) { 
		OCR0A = brightness;
		_delay_ms (LED_DELAY);
	}
	
	for (brightness = 250; brightness > 10; brightness = brightness - 10) { 
		OCR0A = brightness;
		_delay_ms (LED_DELAY);
	}
  }                                                 /* End event loop */
  
  return (0);                           /* This line is never reached */
}
