// Quick and dirty demo of how to get PWM on any pin with interrupts
// ------- Preamble -------- //

#define F_CPU 1200000UL  // 1.2 MHz (9.6MHz / 8)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinDefines.h"

#define DELAY 10

volatile uint8_t brightnessA;
volatile uint8_t brightnessB;
volatile uint8_t ledColor;
volatile uint8_t offCounter;

// -------- Functions --------- //
static inline void initTimer0(void) {
                                 /* must be /64 or more for ISR timing */
  TCCR0B |= (1 << CS01) | (1 << CS00);
                                     /* both output compare interrupts */
  TIMSK0 |= ((1 << OCIE0A) | (1 << OCIE0B));
  //TIMSK0 |= (1 << OCIE0A);
  TIMSK0 |= (1 << TOIE0);                 /* overflow interrupt enable */
  sei();
}

ISR(TIM0_OVF_vect) {
  LED_PORT = ledColor;					/* set color of RGB LED */
  OCR0A = brightnessA;
  offCounter++;
  OCR0B = 255;
}
ISR(TIM0_COMPA_vect ) {
	LED_PORT &= 0b00000000;               /* turn off low 0 and 1 */

}
ISR(TIM0_COMPB_vect ) {
	if (offCounter > 32000) {
		ledColor = offCounter%7;
		offCounter = 0;
	}
}

int main(void) {
  // -------- Inits --------- //

  uint8_t i;
  LED_DDR = 0b00000111;
  ledColor = 1;
  brightnessA = 50;
  initTimer0();

  // ------ Event loop ------ //
  while (1) {
//	i++;
//	ledColor = i % 7;
//    for (i = 0; i < 255; i++) {
//      _delay_ms(DELAY);
//      brightnessA = i;
//      ledColor = i % 7;
//    }

	
  }                                                  /* End event loop */
  return (0);                            /* This line is never reached */
}
