#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* Zmienne globalne */
uint8_t licznik = 0;
uint8_t tablica[3][24];
uint8_t bufor[6];

/* Funkcje */
void USB_Send (unsigned char dana)							// Funkcja wysy³aj¹ca znak przez UART
{
	while ( !( UCSRA & (1<<UDRE)) );						// Oczekiwanie na gotowosc rejestru nadawania
	UDR = dana;
}

/* Main */
int main()
{
	/* Konfiguracja portów IO */
	DDRA = 0xFF;
	PORTA = 0;
	DDRB = 0x1F;
	PORTB = 0;
	DDRC = 0xFF;
	PORTC = 0;
	DDRD = 0xFC;
	PORTD = 0;

	/* Konfiguracja licznika */
	TCCR0 = 0x01;
	TIMSK = 0x02;
	OCR0 = 128;

	/* Kofiguracja UART */
	UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
	UBRRL = 3;

	sei();													// Globalne odmaskowanie przerwañ

	tablica[0][0]=0;
	tablica[1][0]=0;
	tablica[2][0]=0;
	tablica[0][1]=0;
	tablica[1][1]=0;
	tablica[2][1]=0;
	tablica[0][2]=0;
	tablica[1][2]=0;
	tablica[2][2]=0;
	tablica[0][3]=0;
	tablica[1][3]=0;
	tablica[2][3]=0;
	tablica[0][4]=0;
	tablica[1][4]=0;
	tablica[2][4]=0;
	tablica[0][5]=0;
	tablica[1][5]=0;
	tablica[2][5]=0;
	tablica[0][6]=0;
	tablica[1][6]=0;
	tablica[2][6]=0;
	tablica[0][7]=0;
	tablica[1][7]=0;
	tablica[2][7]=0;
	tablica[0][8]=0;
	tablica[1][8]=0;
	tablica[2][8]=0;
	tablica[0][9]=0;
	tablica[1][9]=0;
	tablica[2][9]=0;
	tablica[0][10]=0;
	tablica[1][10]=0;

	tablica[2][10]=0;
	tablica[0][11]=0;
	tablica[1][11]=0;
	tablica[2][11]=0;
	tablica[0][12]=0;
	tablica[1][12]=0;
	tablica[2][12]=0;
	tablica[0][13]=0;
	tablica[1][13]=0;
	tablica[2][13]=0;
	tablica[0][14]=0;
	tablica[1][14]=0;
	tablica[2][14]=0;
	tablica[0][15]=0;
	tablica[1][15]=0;
	tablica[2][15]=0;
	tablica[0][16]=0;
	tablica[1][16]=0;
	tablica[2][16]=0;
	tablica[0][17]=0;
	tablica[1][17]=0;
	tablica[2][17]=0;
	tablica[0][18]=0;
	tablica[1][18]=0;
	tablica[2][18]=0;
	tablica[0][19]=0;
	tablica[1][19]=0;
	tablica[2][19]=0;
	tablica[0][20]=0;
	tablica[1][20]=0;
	tablica[2][20]=0;
	tablica[0][21]=0;
	tablica[1][21]=0;
	tablica[2][21]=0;
	tablica[0][22]=0;
	tablica[1][22]=0;
	tablica[2][22]=0;
	tablica[0][23]=0;
	tablica[1][23]=0;
	tablica[2][23]=0;

	/* G³ówna pêtla programu */
	while (1);
}

/* Obs³uga przerwañ */
ISR(USART_RXC_vect)											// Obs³uga przerwania "zakoñczono otrzymywanie danych"
{
	for (int k = 0; k < 5; k++)
	{
		bufor[k] = bufor[k + 1];
	}
	bufor[5] = UDR;
	if ((bufor[4] == 0xAA) && (bufor[5] == 0xAA))
	{
		for (int k = 0; k < 3; k++)
		{
			tablica[k][bufor[0]] =  bufor[k + 1];
		}
	}											// Echo
}

ISR(TIMER0_COMP_vect)
{
	licznik++;
	if (licznik == 255) licznik = 0;

	if (tablica[0][1] > licznik) PORTA |= (1 << PA0);
	if (tablica[2][1] > licznik) PORTA |= (1 << PA1);
	if (tablica[1][2] > licznik) PORTA |= (1 << PA2);
	if (tablica[0][2] > licznik) PORTA |= (1 << PA3);
	if (tablica[2][2] > licznik) PORTA |= (1 << PA4);
	if (tablica[1][3] > licznik) PORTA |= (1 << PA5);
	if (tablica[0][3] > licznik) PORTA |= (1 << PA6);
	if (tablica[2][3] > licznik) PORTA |= (1 << PA7);

	if (tablica[0][10] > licznik) PORTC |= (1 << PC0);
	if (tablica[1][10] > licznik) PORTC |= (1 << PC1);
	if (tablica[2][9] > licznik) PORTC |= (1 << PC2);
	if (tablica[0][9] > licznik) PORTC |= (1 << PC3);
	if (tablica[1][9] > licznik) PORTC |= (1 << PC4);
	if (tablica[2][8] > licznik) PORTC |= (1 << PC5);
	if (tablica[0][8] > licznik) PORTC |= (1 << PC6);
	if (tablica[1][8] > licznik) PORTC |= (1 << PC7);

	if (tablica[0][18] > licznik) PORTB |= (1 << PB0);
	if (tablica[1][18] > licznik) PORTB |= (1 << PB1);
	if (tablica[2][17] > licznik) PORTB |= (1 << PB2);
	if (tablica[0][17] > licznik) PORTD |= (1 << PD3);
	if (tablica[1][17] > licznik) PORTD |= (1 << PD4);
	if (tablica[2][16] > licznik) PORTD |= (1 << PD5);
	if (tablica[0][16] > licznik) PORTD |= (1 << PD6);
	if (tablica[1][16] > licznik) PORTD |= (1 << PD7);

	PORTB |= (1<<PB3);
	PORTB &= ~(1<<PB3);
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;

	if (tablica[2][6] > licznik) PORTA |= (1 << PA0);
	if (tablica[1][7] > licznik) PORTA |= (1 << PA1);
	if (tablica[0][7] > licznik) PORTA |= (1 << PA2);
	if (tablica[2][7] > licznik) PORTA |= (1 << PA3);
	if (tablica[1][0] > licznik) PORTA |= (1 << PA4);
	if (tablica[0][0] > licznik) PORTA |= (1 << PA5);
	if (tablica[2][0] > licznik) PORTA |= (1 << PA6);
	if (tablica[1][1] > licznik) PORTA |= (1 << PA7);

	if (tablica[1][13] > licznik) PORTC |= (1 << PC0);
	if (tablica[2][12] > licznik) PORTC |= (1 << PC1);
	if (tablica[0][12] > licznik) PORTC |= (1 << PC2);
	if (tablica[1][12] > licznik) PORTC |= (1 << PC3);
	if (tablica[2][11] > licznik) PORTC |= (1 << PC4);
	if (tablica[0][11] > licznik) PORTC |= (1 << PC5);
	if (tablica[1][11] > licznik) PORTC |= (1 << PC6);
	if (tablica[2][10] > licznik) PORTC |= (1 << PC7);

	if (tablica[1][21] > licznik) PORTB |= (1 << PB0);
	if (tablica[2][20] > licznik) PORTB |= (1 << PB1);
	if (tablica[0][20] > licznik) PORTB |= (1 << PB2);
	if (tablica[1][20] > licznik) PORTD |= (1 << PD3);
	if (tablica[2][19] > licznik) PORTD |= (1 << PD4);
	if (tablica[0][19] > licznik) PORTD |= (1 << PD5);
	if (tablica[1][19] > licznik) PORTD |= (1 << PD6);
	if (tablica[2][18] > licznik) PORTD |= (1 << PD7);

	PORTB |= (1<<PB4);
	PORTB &= ~(1<<PB4);
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;

	if (tablica[1][4] > licznik) PORTA |= (1 << PA0);
	if (tablica[0][4] > licznik) PORTA |= (1 << PA1);
	if (tablica[2][4] > licznik) PORTA |= (1 << PA2);
	if (tablica[1][5] > licznik) PORTA |= (1 << PA3);
	if (tablica[0][5] > licznik) PORTA |= (1 << PA4);
	if (tablica[2][5] > licznik) PORTA |= (1 << PA5);
	if (tablica[1][6] > licznik) PORTA |= (1 << PA6);
	if (tablica[0][6] > licznik) PORTA |= (1 << PA7);

	if (tablica[2][15] > licznik) PORTC |= (1 << PC0);
	if (tablica[0][15] > licznik) PORTC |= (1 << PC1);
	if (tablica[1][15] > licznik) PORTC |= (1 << PC2);
	if (tablica[2][14] > licznik) PORTC |= (1 << PC3);
	if (tablica[0][14] > licznik) PORTC |= (1 << PC4);
	if (tablica[1][14] > licznik) PORTC |= (1 << PC5);
	if (tablica[2][13] > licznik) PORTC |= (1 << PC6);
	if (tablica[0][13] > licznik) PORTC |= (1 << PC7);

	if (tablica[2][23] > licznik) PORTB |= (1 << PB0);
	if (tablica[0][23] > licznik) PORTB |= (1 << PB1);
	if (tablica[1][23] > licznik) PORTB |= (1 << PB2);
	if (tablica[2][22] > licznik) PORTD |= (1 << PD3);
	if (tablica[0][22] > licznik) PORTD |= (1 << PD4);
	if (tablica[1][22] > licznik) PORTD |= (1 << PD5);
	if (tablica[2][21] > licznik) PORTD |= (1 << PD6);
	if (tablica[0][21] > licznik) PORTD |= (1 << PD7);

	PORTD |= (1<<PD2);
	PORTD &= ~(1<<PD2);
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
}
