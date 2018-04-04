/***********************************************************************
 * File: bcm1.c
 * uC: attiny13a
 *
 * Simple example of binary coded modulation.
 *
 *
 * Available interupt vectors for the ATTINY13(a)
 * ADC_vect           ADC Conversion Complete
 * ANA_COMP_vect      Analog Comparator
 * EE_RDY_vect        EEPROM Ready
 * INT0_vect          External Interrupt 0
 * PCINT0_vect Pin    Change Interrupt Request 0
 * TIM0_COMPA_vect    Timer/Counter Compare Match A
 * TIM0_COMPB_vect    Timer/Counter Compare Match B
 * TIM0_OVF_vect      Timer/Counter0 Overflow
 * WDT_vect Watchdog  Timeout Interrupt
 * 
 */

#define F_CPU 1000000  // 1.0 MHz

// attiny13a has brown-out detector control register
//#define BODSE 0
//#define BODS 1

#define LED0			PB0 // blue
#define LED1			PB1 // green
#define LED2			PB2 // red
#define MIN_INTENSITY	21
#define MAX_INTENSITY	100
#define MAX_TICKS		10

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t g_bitpos = 0; // which bit position is currently being shown
volatile uint8_t g_timeslice[8] ; // one byte for each bit-position being displayed on a port.
volatile uint8_t g_tick = 0; 


void setup() {
	// setup LEDs
	DDRB |= ((1 << LED0)|(1 << LED1)|(1 << LED2));
	PORTB &= ~((1 << LED0)|(1 << LED1)|(1 << LED2));
	
	// setup timer0
	TCCR0A |= (1<<WGM01) ; // set the timer to CTC mode.
	TCCR0B |= ((1<<CS01)|(1<<CS00)) ; // use clock/64 tickrate
	TIMSK0 |= (1 << OCIE0A) ; // Enable the Compare Match A interrupt
	//TIMSK0 |= (1 << OCIE0B) ; // Enable the Compare Match B interrupt
	
	sei();
	
	// initializations
	g_bitpos = 0;
	g_tick = 0;
	OCR0A = 1;
	OCR0B = 200;
}


void led_encode_timeslices(uint8_t intensity[]) {
	uint8_t portbits = 0;
	uint8_t bitvalue;
	uint8_t bitpos;
	uint8_t ledpos;
	
	for (bitpos = 0 ; bitpos < 8 ; bitpos++ )
	{
		portbits = 0;
		bitvalue = 1 ;
		for (ledpos = 0 ; ledpos < 3 ; ledpos++ )
		{
			if (intensity[ ledpos ] & (1 << bitpos)) portbits |= bitvalue ;
			bitvalue = bitvalue << 1 ;
		}
		g_timeslice[ bitpos ] = portbits ;
	}
}


int main(void) {
	uint8_t brightness[3];
	uint8_t blue, green, red;
	int8_t direction;
	
	setup();
	
	brightness[0] = MIN_INTENSITY;  // blue
	brightness[1] = MIN_INTENSITY;  // green
	brightness[2] = MIN_INTENSITY;  // red

	led_encode_timeslices(brightness);

	direction = 1;
	while(1) {
		if (g_tick == MAX_TICKS) {
			g_tick = 0;

			blue = blue + direction;
			if (blue == MIN_INTENSITY | blue == MAX_INTENSITY) {
				green = green + direction;
				blue = blue - direction;
			}
			
			if (green == MIN_INTENSITY | green == MAX_INTENSITY) {
				red = red + direction;
				green = green - direction;
			}

			if (red == MAX_INTENSITY) {
				direction = -1;
			}

			if (red == MIN_INTENSITY) {
				direction = 1;
			}
			
			brightness[0] = blue;
			brightness[1] = green;
			brightness[2] = red;
			
			led_encode_timeslices(brightness);
		}
	}
}

ISR(TIM0_COMPA_vect) {
	g_bitpos++;
	g_bitpos &= 7;

	PORTB = g_timeslice[ g_bitpos ] ;
	
	//TCNT0 = 0;
	OCR0A <<= 1 ;
	if (g_bitpos == 0) OCR0A = 1 ; // reset the compare match value.
	if (g_bitpos == 7) g_tick++; // give the main loop a kick.
}

