# AVR-GCC Makefile for AVR tiny13 programs
# set PROJECT in environment
# ex: export PROJECT=myproject
#PROJECT=int0
SOURCES=$(PROJECT).c
CC=avr-gcc
OBJCOPY=avr-objcopy
ARCH=avr25
MMCU=attiny13
CFLAGS=-mmcu=$(MMCU) -O1


$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROJECT).out $(SOURCES)

flash: $(PROJECT).hex
	avrdude -p t13 -c usbtiny -e -F -U flash:w:$(PROJECT).hex
#	avrdude -p t13 -c stk500v2 -P /dev/ttyACM0 -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex
	rm *.c~
