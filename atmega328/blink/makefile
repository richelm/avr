# AVR-GCC Makefile for AVR ATMEGA328 programs
PROJECT=blink328
SOURCES=$(PROJECT).c
CC=avr-gcc
OBJCOPY=avr-objcopy
ARCH=avr5
MMCU=atmega328p
CFLAGS=-mmcu=$(MMCU) -O1
PROGRAMMER=usbasp
#PROGRAMMER=usbtiny

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROJECT).out $(SOURCES)

flash: $(PROJECT).hex
	avrdude -p m328 -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
