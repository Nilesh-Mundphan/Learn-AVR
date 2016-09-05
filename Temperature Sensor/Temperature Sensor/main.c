/*
 * Temperature Sensor.c
 *
 * Created: 9/5/2016 5:06:32 PM
 * Author : Nilesh Mundphan
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCDDATADDR DDRD
#define LCDDATAPORT PORTD

#define LCDCNTDDR DDRB
#define LCDCNTPORT PORTB

#define RS PB0
#define RW PB1
#define EN PB2

void lcd_init(void);
void lcd_cmd(char cmd);
void lcd_data(char ldata);
void lcd_print(char* str);
uint16_t anologRead(uint8_t ch);

int main(void)
{
	char line1[16],line2[16];
	uint16_t temp=0;
	
	lcd_init();
	while (1)
	{
		temp=anologRead(0);
		temp=((temp/1023.00)*500.00);
		sprintf(line2,"Temperature : %d" ,temp);
		lcd_print("ADC Test");
		lcd_cmd(0xC0);
		lcd_print(line2);
		_delay_ms(500);
		lcd_cmd(0x01);
	}
}

uint16_t anologRead(uint8_t ch)
{
	ADMUX|=(1<<REFS0);
	ADCSRA=(1<<ADEN)|(7<<ADPS0);
	ch=ch&0b00000111;
	ADMUX&=0b11100000;
	ADMUX|=ch;
	ADCSRA|=(1<<ADSC);
	while(!(ADCSRA & (1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	return(ADC);
}
void lcd_init(void)
{
	LCDDATADDR = 0xFF;
	LCDCNTDDR |= (1<<RS);
	LCDCNTDDR |= (1<<RW);
	LCDCNTDDR |= (1<<EN);
	
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
	lcd_cmd(0x06);
	lcd_cmd(0x80);
}
void lcd_cmd(char cmd)
{
	_delay_ms(4);
	LCDDATAPORT = cmd;

	LCDCNTPORT &= ~(1<<RS);
	LCDCNTPORT &= ~(1<<RW);
	LCDCNTPORT |= (1<<EN);
	_delay_ms(4);
	LCDCNTPORT &= ~(1<<EN);
}
void lcd_data(char ldata)
{
	_delay_ms(4);
	LCDDATAPORT = ldata;

	LCDCNTPORT |= (1<<RS);
	LCDCNTPORT &= ~(1<<RW);
	LCDCNTPORT |= (1<<EN);
	_delay_ms(4);
	LCDCNTPORT &= ~(1<<EN);
}
void lcd_print(char* str)
{
	while(*str)
	lcd_data(*str++);
}
