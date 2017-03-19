PROJECT=test1
SOURCES=$(PROJECT).c
MMCU=atmega328p

# AVRDUDE settings
PROGRAMMER=usbasp
PARTNO=m328p


$(PROJECT).hex: $(PROJECT).elf
	avr-objcopy -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(PROJECT).o
	avr-gcc -g -mmcu=$(MMCU) -o $(PROJECT).elf $(PROJECT).o
		
$(PROJECT).o: $(SOURCES)	
	avr-gcc -g -Os -mmcu=$(MMCU) -c $(PROJECT).c

flash: $(PROJECT).hex
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).o
	rm -f $(PROJECT).elf
	rm -f $(PROJECT).hex
