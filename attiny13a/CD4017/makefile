# AVR-GCC Makefile for AVR tiny13 programs

# change PROJECT name to project's main C program filename.
PROJECT=cd4017
SOURCES=$(PROJECT).c
CC=avr-gcc
OBJCOPY=avr-objcopy
ARCH=avr25
MMCU=attiny13a
CFLAGS=-mmcu=$(MMCU) -O1


$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROJECT).out $(SOURCES)

flash: $(PROJECT).hex
	avrdude -p t13 -c usbasp -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
