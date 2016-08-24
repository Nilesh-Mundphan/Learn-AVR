/*
 * DC Motor.c
 *
 * Created: 8/20/2016 11:45:46 AM
 * Author : Nilesh Mundpahn
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

#define MOTORDDR   DDRD
#define MOTORPORT  PORTD
#define M0		   PD6	
#define M1		   PD7

void setup_motor();
void forword_motor();
void revers_motor();
void stop_motor();

int main(void)
{
    setup_motor();
	
	while (1) 
    {
		forword_motor();
		_delay_ms(3000);
		stop_motor();
		_delay_ms(1000);
		revers_motor();
		_delay_ms(3000);
		stop_motor();
		_delay_ms(1000);
    }
}
void setup_motor()
{
	MOTORDDR |= (1<<M1);
	MOTORDDR |= (1<<M0);
}
void forword_motor()
{
	MOTORPORT |= (1<<M0);
	MOTORPORT &= ~(1<<M1);
}
void revers_motor()
{
	MOTORPORT &= ~(1<<M0);
	MOTORPORT |= (1<<M1);
}
void stop_motor()
{
	MOTORPORT &= ~(1<<M0);
	MOTORPORT &= ~(1<<M1);

}
