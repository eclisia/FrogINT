/*
 * USART_simple.c
 *
 * Created: 28/10/2015 11:33:01
 *  Author: ftainturier
 **********************************************************************************************************************************
 * This C and Header files contains some generic function for USART communication with a PC Terminal (for instance).
 * Global parameter of the USART speed, baudrate, etc... are defined thanks to #define macros into the "Main" program.
 * The transmit and received functions are for 5 to 8 bits communications - none parity check - with 2 bit stop.
 */ 
#include <avr/io.h>
#include "USART-all.h"

/**
 * \brief 
 *  The function to initialize the USART
 * \param ubrr
 * 
 * \return void
 */
void USART_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}



/**
 * \brief 
 *  This function come from the website : https://hekilledmywire.wordpress.com/2011/01/05/using-the-usartserial-tutorial-part-2/
 * Code has been modified to match with my own existing code.
 * It is based on the fact, that in C, each string is ended with a null character. This null character is used to determined the end of the string.
 * \param StringPtr
 * 
 * \return void
 */
void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00)			//Here we check if there is still more chars to send, this is done checking the actual char and see if it is different from the null char
	{    
		USART_Transmit(*StringPtr);	    //Using the simple send function we send one char at a time
		StringPtr++;					//We increment the pointer so we can read the next char
	}        
	
}


/**
 * \brief 
 *  Sending frames with  5 to 8 Data Bit
 * \param data
 * 
 * \return void
 */
void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}






/**
 * \brief 
 *  Receiving frames with 5 to 8 Data Bit
 * \param 
 * 
 * \return unsigned char
 */
unsigned char USART_Receive()
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
	
	
	//while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	//return(UDR);			/* Return the byte*/
	
	
}


char getnextchar(void)
{
	char tmp;
	
	tmp = USART_Receive();				// get next character
	//	tmp = toupper(tmp);					// force to upper case

	if (isgraph(tmp) || (tmp == ' '))
	{
		USART_Transmit(tmp); 			// Echo the received character
		USART_Transmit("\r\n");			//next line
	}
	return(tmp);
}



