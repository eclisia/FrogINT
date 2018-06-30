/*
 * USART-All.h
 *
 * Created: 30/06/2018
 *  Author: ftainturier
 */ 


#ifndef USART-SIMPLE_H_
#define USART-SIMPLE_H_

//Prototypes
void USART_Init( unsigned int ubrr);
void USART_putstring(char* StringPtr);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
char getnextchar(void);

unsigned char * UART1_Rx_Str()

#endif /* USART-SIMPLE_H_ */

