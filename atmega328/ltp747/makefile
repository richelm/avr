# AVR-GCC Makefile for AVR ATMEGA328 programs
PROJECT=test1
SOURCES=$(PROJECT).c
CC=avr-gcc
OBJCOPY=avr-objcopy
ARCH=avr5
MMCU=atmega328p
CFLAGS=-mmcu=$(ARCH) -mmcu=$(MMCU) -O1

# AVRDUDE settings
PROGRAMMER=usbasp
PARTNO=m328p
#PROGRAMMER=usbtiny

$(PROJECT).hex: $(PROJECT).out
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).out $(PROJECT).hex

$(PROJECT).out: $(SOURCES)
	$(CC) $(CFLAGS) -o $(PROJECT).out $(SOURCES)

flash: $(PROJECT).hex
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -e -U flash:w:$(PROJECT).hex

clean:
	rm -f $(PROJECT).out
	rm -f $(PROJECT).hex

# UTILITY Targets

# enter terminal mode
term:
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -t
	
# read device signature
rsig:
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U signature:r:sig_$(MMCU):h
	
# read fuse bytes; not all AVR have each of the fuse bytes; fail normal
# Online fuse calculator: http://www.engbedded.com/fusecalc

# low fuse byte; default 0x62
rlfuse:
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U lfuse:r:lfuse_$(MMCU):h

# high fuse byte; default 0xD9
rhfuse:
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U hfuse:r:hfuse_$(MMCU):h

# extended fuse byte; default 0xFF
refuse:
	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U efuse:r:efuse_$(MMCU):h

wfuse:
	echo "***\nYou have edit file and double check settings first\n***"
#	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U efuse:w:0xFF:m
#	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U lfuse:w:0x62:m
#	avrdude -p $(PARTNO) -c $(PROGRAMMER) -U hfuse:w:0x69:m
