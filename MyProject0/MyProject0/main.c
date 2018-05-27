# define F_CPU 8000000UL
//#include <atmel_start.h>
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	//atmel_start_init();
	
	DDRA |=(1<<DDA0);	//A0 as output
	DDRD |=(1<<DDD0);	//A0 as output
	DDRD |=(1<<DDD1);	//A0 as output

	/* Replace with your application code */
	while (1) {
		
		//PORTA |=(1<<PORTA0);
		////PINA |=(1<<PINA0);	//inverse bit
		////PIND |=(1<<PIND0);
		//_delay_ms(1000);
		//_delay_ms(1000);
		//PORTD |=(1<<PORTD0);
		//PORTD |=(1<<PORTD1);
		//_delay_ms(500);
		//PORTD = 0x00;        // Turn OFF diodes on PORTD
		
		PORTA |=(1<<PORTA0);
		_delay_ms(500);
		PORTA &=~(1<<PORTA0);
		_delay_ms(500);
			
	}
}
