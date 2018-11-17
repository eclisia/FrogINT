/********************************************************************
	created:	2018/06/17
	created:	17:6:2018   13:50
	filename: 	H:\Mes Documents\Cloud-Station_Florelie\Cloud-Station_Florent\Electronique\Projet_FrogINT\FrogINT\MyProject0\MyProject0\main.c
	file path:	H:\Mes Documents\Cloud-Station_Florelie\Cloud-Station_Florent\Electronique\Projet_FrogINT\FrogINT\MyProject0\MyProject0
	file base:	main
	file ext:	c
	author:		Florent TAINTURIER
	
	purpose:	Main function for FrogINT USB device
*********************************************************************/




//Frequency of the CPU is defined as symbol into Project Properties.
// See Make sure F_CPU is correctly defined in your makefile or the project. 
// For AtmelStudio: Project->Properties->Toolchain->AVR/GNU C Compiler->Symbols. Add symbol F_CPU=xxxxx  without UL, on the contrari of #define declaration
//F_CPU=8000000  - 8MHz in this case.

//Penser � configurer le fuse CLK en externe sur Quartz 8MHz - le comportement de l'UART est bien meilleur !


//Macro definition
#define LED_NUMBER 12		//Total number of LED in the Neopixel
#define COLORLENGTH LED_NUMBER/2
#define F_CPU 8000000UL // 8 MHz
#define BAUD 9600
//#define MYUBRR F_CPU/16/BAUD-1
#define MYUBRR (((F_CPU / (BAUD * 16UL))) - 1)

#define TRUE 1
#define FALSE 0
//Macro for UART
#define CHAR_NEWLINE '\n'
#define CHAR_RETURN '\r'
#define RETURN_NEWLINE "\r\n"


//Vector definition
#define USART_RXC_vect			_VECTOR(11)


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"
#include "USART-all.h"
#include "LED_Operations.h"


//Definition for Colors & LedStrip
struct cRGB led[LED_NUMBER];	//Definition of the Structure
struct cRGB colors[8];			//Definition of Color structure

//String the header of USART communication with a PC
const char  line[] = "**************************\r\n";
const char	crlf[] = "\r\n";
const char  society_name[] = "****Florent Tainturier****\r\n";
const char	project_name[] = "****FrogINT****\r\n";
const char	project_version[] = "*******Version V0.1*******\r\n";
const char  backspace[] = "\b \b";
const char  prompt[] = "\r\n> ";

//String to inform user through the USART
const char	text_led[] = "LED PortB0 is switched ON!\r\n";
const char	text_ledoff[] = "LED PortB0 is switched OFF!\r\n";


// The inputted commands are never going to be
// more than 8 chars long. Volatile for the ISR.
volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile unsigned char command_ready;

// Variables to hold current settings
unsigned int sensitivity = 223;




/**
 * \brief	This function permit to set to OFF, all the Led of the Structure.
 *			This is not a Generic Function !
 * \param Led_Number
 * 
 * \return void
 */
void set_Led_OFF(uint8_t Led_Number)
{
	uint8_t i;
	for (i=Led_Number; i>0;i--)
	{
		led[i-1].r=0;
		led[i-1].g=0;
		led[i-1].b=0;
		ws2812_setleds(led,i);
	}
	_delay_ms(500);	// Short delay before next
}


/**
 * \brief	This function is only the LED color definition in RGB style 
 * 
 * 
 * \return void
 */
void Array_Definition(){
	led[0].r=150; led[0].g=150; led[0].b=150;
	led[1].r=255; led[1].g=000; led[1].b=000;//red
	led[2].r=255; led[2].g=100; led[2].b=000;//orange
	led[3].r=100; led[3].g=255; led[3].b=000;//yellow
	led[4].r=000; led[4].g=255; led[4].b=000;//green
	led[5].r=000; led[5].g=100; led[5].b=255;//light blue (t�rkis)
	led[6].r=000; led[6].g=000; led[6].b=255;//blue
	led[7].r=100; led[7].g=000; led[7].b=255;//violet
	led[8].r=100; led[8].g=000; led[8].b=000;
	led[9].r=100; led[9].g=150; led[9].b=000;
	led[10].r=0; led[10].g=23; led[10].b=125;
	led[11].r=0; led[11].g=255; led[11].b=000;
}


/**
 * \brief	This function is only the LED color definition in RGB style 
 * 
 * 
 * \return void
 */
void Custom_Definition(){
	
	uint8_t i;
	for (i=LED_NUMBER; i>0;i--)
	{
		led[i-1].r=255;
		led[i-1].g=0;
		led[i-1].b=00;
	}
	
}


/**
 * \brief	This function is only the LED color definition in RGB style 
 * 
 * 
 * \return void
 */
void Custom_Definition_GREEN(){
	
	uint8_t i;
	for (i=LED_NUMBER; i>0;i--)
	{
		led[i-1].r=0;
		led[i-1].g=60;
		led[i-1].b=0;
	}
	
}

void test_SendArray(){
	
	
	ws2812_setleds((uint8_t *)led,LED_NUMBER*3);
	
	//ws2812_sendarray((uint8_t *)led,LED_NUMBER*3);
	_delay_ms(1000);
		
}

/**
 * \brief 
 * 
 * \param RedINT
 * \param GreenINT
 * \param BlueINT
 * 
 * \return void
 */
void DefineColor(uint8_t RedINT, uint8_t GreenINT, uint8_t BlueINT){
		uint8_t i;
		for (i=LED_NUMBER; i>0;i--)
		{
			led[i-1].r=RedINT;
			led[i-1].g=GreenINT;
			led[i-1].b=BlueINT;
		}	
}







int main(void)
{

	//Variables
	int8_t i;
	
	//Enable Interrupt
	sei();

	
	//Initialize the Strip LED OFF
	set_Led_OFF(LED_NUMBER);
	
	//Initialize the Led color
	//Array_Definition();
	Custom_Definition();
	Custom_Definition_GREEN();
	
		
	//Initialization of USART interface
	USART_Init ( MYUBRR );	//USART initialization
	setup_led();	//Toggle led initialization

		
	//Initial message
	USART_putstring(line);	//Send Welcome message
	USART_putstring(society_name);
	USART_putstring(project_name);
	USART_putstring(project_version);
	USART_putstring(line);
	
	
	USART_putstring(prompt);	//Prompt
	
	char receivedData;	// Tmp variable to test loopback UART function
	
	/* Replace with your application code */
	while (1) {

		//if (command_ready == TRUE) {
			//copy_command();
			//process_command();
//
			//command_ready = FALSE;
			//USART_putstring("OK");
		//}
		

		
		
		
		
		test_SendArray();
		//
		////rendre le "prompt" dans le While semble une mauvaise id�e
		////USART_putstring(prompt);	//Prompt
		////data_received=getnextchar();
		//
//
		///* Wait for data to be received */
		//while ( !(UCSRA & (1<<RXC)) );
		///* Get and return received data from buffer */
		//data_received= UDR;		
//
		/////* Wait for empty transmit buffer */
		////while ( !( UCSRA & (1<<UDRE)) )	;
		/////* Put data into buffer, sends the data */
		////UDR = receivedData;


	
		
	
		
				
		//////Switch structure used to color LED		
		//switch (data_received)
		//{
			//case 'r':	//h
			//switchLed(1);
			//Custom_Definition();
			//test_SendArray();
			//USART_putstring(text_led);
			//break;
			//
			//case 'g': //o
			//switchLed(0);
			//Custom_Definition_GREEN();
			//test_SendArray();
			//USART_putstring(text_ledoff);
			//
			//default:
			//if (isgraph(data_received))
			//{
				//USART_putstring(backspace);	//Permit to erase invalid character
				//USART_putstring(data_received);
				//USART_putstring(": is NOT RECOGNISED\r\n");	//Permit to erase invalid character
			//}
			//break;
		//}
		

		

			
	}
}
ISR (USART_RXC_vect)
{
	//// Get data from the USART in register
	//data_in[data_count] = UDR0;
//
	//// End of line!
	//if (data_in[data_count] == '\n') {
		//command_ready = TRUE;
		//// Reset to 0, ready to go again
		//data_count = 0;
		//} else {
		//data_count++;
	//}
	
	

			
		
			
	char data_received;	//local variable to get the character received through the USART
	data_received= USART_Receive();
	USART_putstring(data_received);
			

	
	
	
	
	
	
	
	
	
}
