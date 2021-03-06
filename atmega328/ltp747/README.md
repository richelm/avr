# LTP747 5X7 LED Dot Matrix

Goal is to make a simple scrolling message display using the LTP747 in a
horizonal mode. The anode columns will be the rows and the cathode rows will
be the columns.

An Atmel AVR ATMEGA328 will be used to drive the display. To reduce the number
of I/O pins used on the 328, a CD4051BE will be used to drive the columns of the
display. Initially the rows will be driven by 5 I/O pins on the 328.

## Pins

### ATMEGA328

         (PCINT14/RESET) PC6 --  1    28 -- PC5 (ADC5/SCL/PCINT13)
           (PCINT16/RXD) PD0 --  2    27 -- PC4 (ADC4/SDA/PCINT12)
           (PCINT17/TXD) PD1 --  3    26 -- PC3 (ADC3/PCINT11)
          (PCINT18/INT0) PD2 --  4    25 -- PC2 (ADC2/PCINT10)
      PCINT19/OC2B/INT1) PD3 --  5    24 -- PC1 (ADC1/PCINT9)
        (PCINT20/XCK/T0) PD4 --  6    23 -- PC0 (ADC0/PCINT8)
                         VCC --  7    22 -- GND
                         GND --  8    21 -- AREF
    (PCINT6/XTAL1/TOSC1) PB6 --  9    20 -- AVCC
    (PCINT7/XTAL2/TOSC2) PB7 -- 10    19 -- PB5 (SCK/PCINT5)
       (PCINT21/OC0B/T1) PD5 -- 11    18 -- PB4 (MISO/PCINT4)
     (PCINT22/OC0A/AIN0) PD6 -- 12    17 -- PB3 (MOSI/OC2A/PCINT3)
          (PCINT23/AIN1) PD7 -- 13    16 -- PB2 (SS/OC1B/PCINT2)
      (PCINT0/CLKO/ICP1) PB0 -- 14    15 -- PB1 (OC1A/PCINT1)

### CD4051BE

    CH 4 IN/OUT -- 1    16 -- VDD
    CH 6 IN/OUT -- 2    15 -- CH 2 IN/OUT
     COM OUT/IN -- 3    14 -- CH 1 IN/OUT
    CH 7 IN/OUT -- 4    13 -- CH 0 IN/OUT
    CH 5 IN/OUT -- 5    12 -- CH 3 IN/OUT
            INH -- 6    11 -- A
            VEE -- 7    10 -- B
      VSS (GND) -- 8     9 -- C


### LTP747R (pin one is opposite of tab side)

    AC1 -- 1    12 -- CR1
    CR3 -- 2    11 -- CR2
    AC2 -- 3    10 -- AC3 (tab side)
    CR5 -- 4     9 -- CR4
    CR6 -- 5     8 -- AC5
    CR7 -- 6     7 -- AC4

## 74HC595

     Q1 -- 1    16 -- VCC
     Q2 -- 2    15 -- Q0
     Q3 -- 3    14 -- DS
     Q4 -- 4    13 -- OE
     Q5 -- 5    12 -- ST_CP
     Q6 -- 6    11 -- SH_CP
     Q7 -- 7    10 -- MR
    GND -- 8     9 -- Q7”

    PINS 1-7, 15 	Q0 - Q7 	Output Pins
    PIN 8 	GND 	Ground, Vss
    PIN 9 	Q7" 	Serial Out
    PIN 10 	MR 	Master Reclear, active low
    PIN 11 	SH_CP 	Shift register clock pin
    PIN 12 	ST_CP 	Storage register clock pin (latch pin)
    PIN 13 	OE 	Output enable, active low
    PIN 14 	DS 	Serial data input
    PIN 16 	Vcc 	Positive supply voltage
