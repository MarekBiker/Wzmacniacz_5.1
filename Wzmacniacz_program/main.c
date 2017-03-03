/*
 * Wzmacniacz_program.c
 *
 * Created: 02.03.2017 21:08:25
 * Author : Marek
 */ 

 /////////////  HELP  //////////////

 //WARTOSC<<BIT
 //PORTB |= 1<<0;
 //PORTB &= 0<<0;

#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
    // USTAWIENIE WYJŒÆ //

	DDRB |= 0b11000000; // PB6, PB7
	DDRD |= 0b00011111;  // PD0-PD4

	// USTAWIENIE WEJŒÆ //
	// porty sa domyslnie jako wejscia
	PORTB |= 0b0000110; // ustawienie podciagania do VCC

    while (1) 
    {
    }
}

