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


//Macro definition
#define LED_NUMBER 12		//Total number of LED in the Neopixel
#define COLORLENGTH LED_NUMBER/2
#define F_CPU 8000000UL // 8 MHz
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"
#include "USART-simple.h"
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
	led[5].r=000; led[5].g=100; led[5].b=255;//light blue (türkis)
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
		led[i-1].g=255;
		led[i-1].b=0;
	}
	
}

void test_SendArray(){
	
	
	ws2812_setleds((uint8_t *)led,LED_NUMBER*3);
	
	//ws2812_sendarray((uint8_t *)led,LED_NUMBER*3);
	_delay_ms(1000);
		
}


int main(void)
{

	//Variables
	int8_t i;
	char data_received;	//local variable to get the character received through the USART


	
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
	
	
	
	
	/* Replace with your application code */
	while (1) {
		
		
		test_SendArray();

		USART_putstring(prompt);	//Prompt
		data_received=getnextchar();
				
		switch (data_received)
		{
			case 'h':
			switchLed(1);
			Custom_Definition();
			test_SendArray();
			USART_putstring(text_led);
			break;
			
			case 'o':
			switchLed(0);
			Custom_Definition_GREEN();
			test_SendArray();
			USART_putstring(text_ledoff);
			
			default:
			if (isgraph(data_received))
			{
				USART_putstring(backspace);	//Permit to erase invalid character
			}
			break;
		}
		

		

			
	}
}
