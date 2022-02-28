/*
 * KeyPadWithLCD.c
 *
 * Created: 30/01/2022 03:17:21
 * Author : HP
 */ 

#include "../ECUAL/LCD/LCD.h"

#include "../ECUAL/Keypad/KEYPAD1.h"

timer timer0;
uint8_t checkstatus;

int main(void)
{
    checkstatus=LCD_Init();
	KEYPAD_u8Init();
	//LCD_Clear();
	Timer0_Init(&timer0,0);
	Timer0_Start(&timer0);
	uint8_t key = 0;
	uint8_t counter = 0;
	
	while(1){
		
		KEYPAD_u8GetKey(&key);
		if(key != 0xFF){
			
			if(counter == 16){
				LCD_GoToLocation(1, 0);
			}
			else if(counter == 32){
				counter = 0;
				if(checkstatus==LCD_Initialized){
				checkstatus=LCD_WriteCommand(CLEAR);
				}
			}
			if(checkstatus==LCD_OK)
			{
			LCD_WriteInteger(key);
			counter++;
			}
			
		}
	}
}


		
		
			
		
	

	


