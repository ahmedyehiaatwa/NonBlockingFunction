/*
 * KEYPAD1.c
 *
 * Created: 31/01/2022 02:21:13
 *  Author: HP
 */ 


#include "KEYPAD1.h"


const static uint8_t KEYPAD[KEYPAD_ROWS][KEYPAD_COLS] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
/*
* brief: This function is used to initialize pin directions of the keypad as defined in the configurations
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/

KEYPAD_ERR_STATE KEYPAD_u8Init(void){
	KEYPAD_ERR_STATE state = KEYPAD_OK;
	//Set Cols direction output
	state = DIO_SetPinDir(COL0_PORT, COL0_PIN, OUTPUT_PIN);
	if(state == KEYPAD_OK){
		state = DIO_SetPinDir(COL1_PORT, COL1_PIN, OUTPUT_PIN);
	}
	if(state == KEYPAD_OK){
		state = DIO_SetPinDir(COL2_PORT, COL2_PIN, OUTPUT_PIN);
	}
	
	//Set Cols high
	if(state == KEYPAD_OK){
		state = DIO_SetPinValue(COL0_PORT, COL0_PIN, DIO_PIN_HIGH);
	}
	if(state == KEYPAD_OK){
		state = DIO_SetPinValue(COL1_PORT, COL1_PIN, DIO_PIN_HIGH);
	}
	if(state == KEYPAD_OK){
		state = DIO_SetPinValue(COL2_PORT, COL2_PIN, DIO_PIN_HIGH);
	}
	
	//Set rows direction input with pullup
	if(state == KEYPAD_OK){
		state = DIO_SetPullUp(ROW0_PORT, ROW0_PIN);  /// setpindir
	
	}
	if(state == KEYPAD_OK){
		state = DIO_SetPullUp(ROW1_PORT, ROW1_PIN);
	}
	if(state == KEYPAD_OK){
		state = DIO_SetPullUp(ROW2_PORT, ROW2_PIN);
	}
	
	return state;
}

/*
* brief: This function is used to get the value of the key pressed in the keypad
* param.: (input) a pointer to a variable to hold the key value that was pressed and MAX value if none pressed
* return: (output) the Error state of the function 0 if an error happens and 1 otherwise
*/

KEYPAD_ERR_STATE KEYPAD_u8GetKey(uint8_t* key)
{
	KEYPAD_ERR_STATE state = KEYPAD_OK;
	if(key == NULL){
		state = KEYPAD_ERR;
		
	}
	else{
	//	LCD_WriteChar('X');
		uint8_t pin;
		*key = 0xFF;
		for(uint8_t col = 0; col < KEYPAD_COLS; col++){
			switch(col){
				case  0:
				state = DIO_SetPinValue(COL0_PORT, COL0_PIN, DIO_PIN_LOW);
				break;
				case 1:
				state = DIO_SetPinValue(COL1_PORT, COL1_PIN, DIO_PIN_LOW);
				break;
				case 2:
				state = DIO_SetPinValue(COL2_PORT, COL2_PIN, DIO_PIN_LOW);
				break;
				default:
				break;
			}
			if(state != KEYPAD_OK){
				break;
			}
			for(uint8_t row = 0; row < KEYPAD_ROWS; row++){
				switch(row){
					case  0:
					state = DIO_ReadPinValue(ROW0_PORT, ROW0_PIN, &pin);
					break;
					case 1:
					state = DIO_ReadPinValue(ROW1_PORT, ROW1_PIN, &pin);
					break;
					case 2:
					state = DIO_ReadPinValue(ROW2_PORT, ROW2_PIN, &pin);
					break;
					default:
					break;
				}
				if(pin == DIO_PIN_LOW){
					*key = KEYPAD[row][col];
				//	LCD_WriteChar('F');
					Timer0_SetDelay(10);
				}
			}
			switch(col){
				case  0:
				state = DIO_SetPinValue(COL0_PORT, COL0_PIN, DIO_PIN_HIGH);
				break;
				case 1:
				state = DIO_SetPinValue(COL1_PORT, COL1_PIN, DIO_PIN_HIGH);
				break;
				case 2:
				state = DIO_SetPinValue(COL2_PORT, COL2_PIN, DIO_PIN_HIGH);
				break;
				default:
				break;
			}
		}
	}
	return state;
}
