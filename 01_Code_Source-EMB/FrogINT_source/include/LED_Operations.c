/*
 * LED_Operations.c
 *
 * Created: 28/10/2015 16:43:03
 *  Author: ftainturier
  ***********************************************************************************************************************************
  * Basic set of functions to control LED
  * Port B led are used.
 */ 

#include <avr/io.h>

#define LedB0_ON	PORTB |= (1<<PB0)	// Set PA0 bit in 1 Logic state
#define LedB0_OFF	PORTB &= ~(1<<PB0)	// Set PA0 bit in  0 Logic state
#define LedB0_Toggle	PORTB ^=(1<<PB0);	//Exclusive OR on the Bit to Toggle its state.

void	setup_led()
{
	DDRB = 0xFF;	//All IO of Port A as output
}

void switchLed(unsigned int onoff)
{
	switch (onoff)
	{
		case 1: //Light the Led
			LedB0_ON;
			break;
		case 0:
			LedB0_OFF;
			break;
		default:
			LedB0_OFF;
			break;
	}
			
}