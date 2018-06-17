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

#define LED_NUMBER 12		//Total number of LED in the Neopixel
#define COLORLENGTH LED_NUMBER/2

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"



struct cRGB led[LED_NUMBER];	//Definition of the Structure
struct cRGB colors[8];			//Definition of Color structure


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


void test_SendArray(){
	
	ws2812_sendarray((uint8_t *)led,LED_NUMBER*3);
	_delay_ms(1000);
		
}


int main(void)
{

	//Variables
	uint8_t i, j,k;	//Local Variable for loop


	//Color definition as RGB color and record of the color setting into the cRGB Color Struct
	colors[0].r=150; colors[0].g=150; colors[0].b=150;
	colors[1].r=255; colors[1].g=000; colors[1].b=000;//red
	colors[2].r=255; colors[2].g=100; colors[2].b=000;//orange
	colors[3].r=100; colors[3].g=255; colors[3].b=000;//yellow
	colors[4].r=000; colors[4].g=255; colors[4].b=000;//green
	colors[5].r=000; colors[5].g=100; colors[5].b=255;//light blue (türkis)
	colors[6].r=000; colors[6].g=000; colors[6].b=255;//blue
	colors[7].r=100; colors[7].g=000; colors[7].b=255;//violet
	
	//Initialize the LED OFF
	set_Led_OFF(LED_NUMBER);
	
	Array_Definition();
	
	

	
	//DDRA |=(1<<DDA0);	//A0 as output
	//DDRD |=(1<<DDD0);	//A0 as output
	//DDRD |=(1<<DDD1);	//A0 as output

	/* Replace with your application code */
	while (1) {
		
		
		test_SendArray();

		

			
	}
}
