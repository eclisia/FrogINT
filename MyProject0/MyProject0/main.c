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

	/* Replace with your application code */
	while (1) {
		PINA |=(1<<PINA0);	//inverse bit
		PIND |=(1<<PIND0);
		_delay_ms(5000);
		
			
	}
}
