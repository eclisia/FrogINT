/*
 * Tuto-WS2812-LED_160210-1051.c
 *
 * Created: 10/02/2016 10:51:59
 * Author : ftainturier
 */ 


//Frequency of the CPU is defined as symbol into Project Properties.
// See Make sure F_CPU is correctly defined in your makefile or the project. 
// For AtmelStudio: Project->Properties->Toolchain->AVR/GNU C Compiler->Symbols. Add symbol F_CPU=xxxxx  without UL, on the contrari of #define declaration
//F_CPU=8000000  - 8MHz in this case.
//#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

#define LED_NUMBER 12		//Total number of LED in the Neopixel
#define COLORLENGTH LED_NUMBER/2

struct cRGB led[LED_NUMBER];	//Definition of the Structure
struct cRGB colors[8];			//Definition of Color structure

/**
 * \brief	This function permit to set to OFF, all the Led of the Structure.
*		This is not a Generic Function !
 * 
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


void	set_Led_Color(uint8_t Led_Row){
	
}


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
	
	////Shift of LED of the LED Structure to have an effect of propagation
	//uint8_t i=0;
	//for(i=LED_NUMBER; i>1; i--){
		//led[i-1]=led[i-2];
	//}
	
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
	
	
    while (1) 
    {
		
		//*******************************
		//Uncomment the only hereafter line to use "text_SendArray" feature (and let all other line commented)
		test_SendArray();
		
		
		
		
		//*******************************
		//Uncomment all hereafter line to use the "Propagation" feature
		
		
		
		////Shift of LED of the LED Structure to have an effect of propagation
        //uint8_t i=0;
        //for(i=LED_NUMBER; i>1; i--){
			//led[i-1]=led[i-2];				
		//}
//
		////Loop to change the j indice at each loop of the Neopixel
		//if(k>COLORLENGTH)
		//{
			//j++;
			//if(j>7)
			//{
				//j=0;
			//}
//
			//k=0;
		//}
		//k++;
		////loop colouers
//
		////Change of Color given to j indice
		//if (led[0].r!=colors[j].r)
		//{
			//led[0].r=colors[j].r;
		//}
		//if (led[0].g!=colors[j].g)
		//{
			//led[0].g=colors[j].g;
		//}
		//if (led[0].b!=colors[j].b)
		//{
			//led[0].b=colors[j].b;
		//}
		//
		//
		//
		////Send all the structur of LED
		//ws2812_sendarray((uint8_t *)led,LED_NUMBER*3);
//
		////set_Led_OFF(LED_NUMBER);
		//_delay_ms(1000);
		
		

    }
}

