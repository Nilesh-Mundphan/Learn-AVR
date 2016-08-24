/*
 * UART.c
 *
 * Created: 8/20/2016 1:09:32 PM
 * Author : Nilesh
 */ 
#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

void uart_init(uint16_t baud);
void uart_send(char ch);
char uart_read();
void uart_print(char* str);

int main(void)
{
    uart_init(9600);
	uart_print("Hello World \r\n");
	while (1) 
    {
		uart_send(uart_read());
    }
}

void uart_init(uint16_t baud)
{
	unsigned int BAUD=F_CPU/16/baud-1;
	UBRR0H = (unsigned char)(BAUD>>8);
	UBRR0L = (unsigned char)BAUD;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0);
	UCSR0C = (3<<UCSZ00);
}

void uart_send(char ch)
{
	while ( !( UCSR0A & (1<<UDRE0)));
	UDR0 = ch;
}

char uart_read()
{
	while ( !(UCSR0A & (1<<RXC0)) );
		return UDR0;
}

void uart_print(char* str)
{
	while(*str)
		uart_send(*str++);
}
