
/*
RGB LED Color Mixer
target: attiny2313
design: www.avrprojects.net
last update: 31-1-2013
*/

#define F_CPU 1200000UL  // 1.2 MHz (9.6MHz / 8)

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define DELAY 4000
#define VERT 50

//Prototypes

//This function is called to switch on the LED at the 
//Required stage of PWM cycle
void abc(unsigned char a,unsigned char b,unsigned char c,unsigned char status);
void out(void);

//Global variables
volatile unsigned char e;
volatile unsigned char pwm[3]={255,255,255};
unsigned char blue;
unsigned char red;
unsigned char green;
//unsigned char vert;

int main(void)
{
	DDRB  &= ~((1<<3)|(1<<4)|(1<<5));//ADC inputs
	
	//Initially LEDs should be off
	DDRB |=  (1<<0|1<<1|1<<2);
	PORTB |= (1<<0)|(1<<1)|(1<<2);
	
	//init color
	blue = 0;
	green = 0;
	red = 255;
	
	//vert= 50;
	
	
	//Timer Initialisation
	//TCCR0A = 0x00;
	TCCR0B |= (1 << CS02); // No Prescaling
	//TCCR0B = 0x01;//
	TIMSK0 |= (1 << TOIE0);		//Overflow Interrupt Enabled
	sei();						//Global Interrupts Enabled
	
	while(1)
	{			
		
		for( blue = 0; blue < 255; blue++)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);
		}
		
		_delay_ms(DELAY);
		
		for( red = 255; red > 0; red--)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);
		}
		
		_delay_ms(DELAY);

		for( green = 0; green < 255; green++)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);
		}
		
		_delay_ms(DELAY);
		
		for( blue = 255; blue > 0; blue--)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);
		}

		_delay_ms(DELAY);		
		
		for( red = 0; red < 255; red++)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);
		}
		
		_delay_ms(DELAY);
		
		for( green = 255; green > 0; green--)
		{
		pwm[0]=blue; //blue
		pwm[1]=green; //green
		pwm[2]=red; //red
		_delay_ms(VERT);	
		}
		
		_delay_ms(DELAY);
	}	

}


//Overflow routine for Timer 0
ISR(TIM0_OVF_vect)
{
	
	//Value of e decides the no of levels of PWM.
	//This has 256 levels for e - 0 to 255
	//0 - complete on and 255 is complete off
	
	if(e==255)
	{
		e=0;
		PORTB |= (1<<0)|(1<<1)|(1<<2);
	}

	abc(pwm[0],pwm[1],pwm[2],e);
	
	e++;
	
}


//This function is called to switch on the LED at the 
//Required stage of PWM cycle
void abc(unsigned char a,unsigned char b,unsigned char c,unsigned char status)
{

	if((status==a))
	{
		PORTB&= ~(1<<0);
	}
	if((status==b))
	{
		PORTB&= ~(1<<1);
	}
	if((status==c))
	{
		PORTB&= ~(1<<2);
	}
	
}



