/*
 * Led Blink.c
 *
 * Created: 8/20/2016 11:10:31 AM
 * Author : Nilesh
 */ 

#define F_CPU 16000000				//Define Clock frequency 
#include <avr/io.h>
#include <util/delay.h>

#define LEDDDR	DDRB				//LED micros
#define LEDPORT PORTB
#define LEDPIN	PB5

int main(void)
{
    /* Replace with your application code */
    LEDDDR |= (1<< LEDPIN);				//Configure PIN as Output
	while (1) 
    {
		LEDPORT |= (1<< LEDPIN);		//Make PIN HIGH
		_delay_ms(1000);
		LEDPORT &= ~(1<< LEDPIN);		//Make PIN LOW
		_delay_ms(1000);
    }
}

