#include <avr/io.h>

/**
 * FILE: ds1620.c
 * 
 * This program will get temperature readings from the DDS1620 and send
 * to a PC via the USART on the TINY4313.
 * 
 * Connection to the PC is via the Sparkfun FTDI Cable DEV-09717. Pinout
 * is:
 * 
 *  1 GND/BLACK
 *  2 CTS/BROWN
 *  3 VCC/RED
 *  4 TXD/ORANGE
 *  5 RXD/YELLOW
 *  6 RTS/GREEN
 * 
 * Connection to the TINY4313:
 * 
 *  1 -- GND
 *  4 -- PIN 2
 *  5 -- PIN 3
 * 
 * 
 * References:
 * 1. Using the USART in AVR-GCC by Dean Camera, May 5, 2013
 * 
 */

#define F_CPU 1000000	// 1 MHz

#define USART_BAUDRATE 2400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define CR 0x0D
#define LF 0x0A

void transmitByte(uint8_t data) {
	while ((UCSRA & (1 << UDRE)) == 0) {}; // wait until ready to write data
	UDR = data;                    // send data
}

void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
  }
}

void printByte(uint8_t byte) {
              /* Converts a byte to a string of decimal text, sends it */
  transmitByte('0' + (byte / 100));                        /* Hundreds */
  transmitByte('0' + ((byte / 10) % 10));                      /* Tens */
  transmitByte('0' + (byte % 10));                             /* Ones */
}

void setup() {
	UCSRB |= (1 << RXEN) | (1 << TXEN);  // turn on transmit and recieve circuitry
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1); // use 8-bit character sizes
	
	UBRRH = (BAUD_PRESCALE >> 8); // load upper 8-bits of baud rate value
	UBRRL = BAUD_PRESCALE; // load lower 8-bits of the baud rate value
}
int main (void) {
	
	setup();
	
	char ReceivedByte;
	uint8_t temperature;
	temperature = 10;
	// main control loop
	while (1) {
		while ((UCSRA & (1 << RXC)) == 0) {}; // do nothing until data ready to be read
		ReceivedByte = UDR; // read the byte value
		
		temperature--;
		printByte(temperature);
		
		// echo the received byte back to the computer
		transmitByte(ReceivedByte);
		transmitByte(CR);
		transmitByte(LF);
	}
	
	return 0;
}


