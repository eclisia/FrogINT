/*
 * USART_simple.h
 *
 * Created: 28/10/2015 11:29:38
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
unsigned char * UART1_Rx_Str();
unsigned char uartreceive(unsigned char *x, unsigned char size);
void ReadStringData(char *str);

#endif /* USART-SIMPLE_H_ */

