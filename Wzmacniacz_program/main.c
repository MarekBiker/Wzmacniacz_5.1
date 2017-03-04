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
#include <util/delay.h>


int main(void)
{
    // USTAWIENIE WYJŒÆ //
	DDRD |= 0b00111111;  // PD0-PD5

	// USTAWIENIE WEJŒÆ //
	PORTB |= 0b0000110; // ustawienie podciagania do VCC - porty domyœlnie jako wejœcia

	// DEKLARACJE ZMIENNYCH
	short PRZYCISK_ON_OLD = 0;
	short PRZYCISK_MUTE_OLD = 0;
	short PRZYCISK_ON = 0;
	short PRZYCISK_MUTE = 0;
	short WZMACNIACZ_WLACZONY = 0;
	short WZMACNIACZ_WYCISZONY = 0;

	// ustawianie bitow na poczatku
	PORTD &= 0<<5;
	PORTD &= 0<<3;
	PORTD &= 0<<4;
	PORTD &= 0<<2;
	_delay_ms(200);
	PORTD &= 0<<0;
	PORTD &= 0<<1;

    while (1) 
    {
	PRZYCISK_ON = !(PINB &(1<<PB1));
	PRZYCISK_MUTE = !(PINB &(1<<PB2));
	//PRZYCISK_ON = PINB & 0b00000010;
	//PRZYCISK_MUTE = PINB & 0b00000100;
	
	if(PRZYCISK_ON && !PRZYCISK_ON_OLD && WZMACNIACZ_WLACZONY) {
		//wylaczenie przekaznikow
		PORTD &= 0<<5;
		//wylaczenie diody
		PORTD &= 0<<3;
		//wylaczenie glosnikow
		PORTD &= 0<<2;
		_delay_ms(200);
		PORTD &= 0<<0;
		PORTD &= 0<<1;

		WZMACNIACZ_WLACZONY = 0;
		PRZYCISK_ON_OLD = 1;
			}
	if(PRZYCISK_ON && !PRZYCISK_ON_OLD && !WZMACNIACZ_WLACZONY) {
			
			//wlaczenie przekaznikow
			PORTD |= 1<<5;
			//wlaczenie diody
			PORTD |= 1<<3;
			//wlaczenie glosnikow
			_delay_ms(500);
			PORTD |= 1<<0;
			PORTD |= 1<<1;
			_delay_ms(200);
			PORTD |= 1<<2;

			WZMACNIACZ_WLACZONY = 1;
			PRZYCISK_ON_OLD = 1;
	}

	if(PRZYCISK_MUTE && !PRZYCISK_MUTE_OLD && WZMACNIACZ_WYCISZONY && WZMACNIACZ_WLACZONY) {
		// wlaczanie glosnikow
		PORTD |= 1<<0;
		PORTD |= 1<<2;
		// gaszenie diody
		PORTD &= 0<<4;
		PORTD |= 1<<3;

		PORTD |= 1<<1;
		PORTD |= 1<<5;
		PORTD |= 1<<2;
		PORTD |= 1<<0;

		WZMACNIACZ_WYCISZONY = 0;
		PRZYCISK_MUTE_OLD = 1;
	}
	if(PRZYCISK_MUTE && !PRZYCISK_MUTE_OLD && !WZMACNIACZ_WYCISZONY && WZMACNIACZ_WLACZONY) {
		
		//wyciszenie glosnikow
		PORTD &= 0<<2;
		PORTD &= 0<<0;
		// zapalenie diody
		PORTD |= 1<<4;
		PORTD |= 1<<3;

		PORTD |= 1<<1;
		PORTD |= 1<<5;

		WZMACNIACZ_WYCISZONY = 1;
		PRZYCISK_MUTE_OLD = 1;
	}

	PRZYCISK_MUTE_OLD = PRZYCISK_MUTE;
	PRZYCISK_ON_OLD = PRZYCISK_ON;
    }
}

