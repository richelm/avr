# LTP747 5X7 LED Dot Matrix

Goal is to make a simple scrolling message display using the LTP747 in a
horizonal mode. The anode columns will be the rows and the cathode rows will
be the columns.

An Atmel AVR ATMEGA328 will be used to drive the display. To reduce the number
of I/O pins used on the 328, a CD4051BE will be used to drive the columns of the
display. Initially the rows will be driven by 5 I/O pins on the 328.

## Pins
