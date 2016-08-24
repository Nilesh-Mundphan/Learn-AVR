/*
 * Seven Segment Display.c
 *
 * Created: 8/20/2016 11:20:14 AM
 * Author : Nilesh Mundphan
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


#define DISPDATADDR  DDRD
#define DISPDATAPORT PORTD

#define DISPENDDR	 DDRB
#define DISPENPORT	 PORTB	
#define DISPENPIN    PB0
	 
int main(void)
{
    unsigned char Code[]={0xC0,0xF9,0xA4,0xb0,0x99,0x92,0x82,0xF8,0x80,0x90};
    int i;
	DISPDATADDR =0xFF;
	DISPENDDR |= (1<<DISPENPIN);
	DISPENPORT |= (1<<DISPENPIN);
	while (1)
	{
		for(i=0;i<10;i++)
		{
			DISPDATAPORT=Code[i];
			_delay_ms(1000);
		}
	
	}
}

