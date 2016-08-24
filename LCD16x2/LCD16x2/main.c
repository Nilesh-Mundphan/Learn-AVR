/*
 * LCD16x2.c
 *
 * Created: 8/20/2016 11:37:25 AM
 * Author : Nilesh
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

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

int main(void)
{
    lcd_init();
	lcd_print("Hello Word !!!");
    while (1) 
    {
    }
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
