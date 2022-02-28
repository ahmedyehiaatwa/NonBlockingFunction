/*
 * LCD.c
 *
 *  Author: Ahmed
 */ 


#include   "LCD.h"
static LCD_ERR_STATE state;




LCD_ERR_STATE LCD_Init(void)
{	
	state = LCD_OK;
		state = DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT , LCD_RS_PIN , DIO_PIN_OUTPUT);
		if(state == LCD_OK){
		DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT , LCD_RW_PIN , DIO_PIN_OUTPUT);
		}
		if(state == LCD_OK){
		DIO_SetPinDir(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_OUTPUT);
		}
		DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT , LCD_D4, DIO_PIN_OUTPUT);
		if(state == LCD_OK){
		DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT , LCD_D5, DIO_PIN_OUTPUT);
		}
		DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT , LCD_D6, DIO_PIN_OUTPUT);
		if(state == LCD_OK){
		DIO_SetPinDir(LCD_4BIT_MODE_DATA_PORT , LCD_D7, DIO_PIN_OUTPUT);
		state = LCD_Initialized;
		}
	
	  
	   switch (state){
		   case LCD_Initialized:
			  LCD_WriteCommand(0X33);
			  state=LCD_FirstCommand;
			  break;
	   
		   case LCD_FirstCommand:
			  LCD_WriteCommand(0X32);   // send 4 bit intialization of LCD
		  	  state=LCD_SecondCommand;
		      break;
		   case LCD_SecondCommand:
		      LCD_WriteCommand(0X28);  // 2 line, 5*7 matrix for 4 bit mode
		      state==LCD_ThirdCommand;
	          break;
	       case LCD_ThirdCommand:
		      LCD_WriteCommand(0X0C); //display on cursor off
		      state==LCD_FourthCommand;
	          break;
	       case LCD_FourthCommand:
		      LCD_WriteCommand(0X01); // clear display
		      state==LCD_FifthCommand;
	          break;
		   case LCD_FifthCommand:
		      LCD_WriteCommand(0X06); // increment cursor to right
		      state==LCD_Initialized;
		      break;
		   default:
		      state==LCD_ERR;
			  break;
	   }
	return state;
}

LCD_ERR_STATE LCD_WriteCommand(uint8_t cmd)
{
	if( state==LCD_Initialized)
	{
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_RS_PIN , DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_RW_PIN , DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
	state= LCD_FirstNibble;
	switch (state){
		case LCD_FirstNibble:
			PORTA = ((cmd & 0xF0) | (PORTA & 0x0F));  // send higher nibble			
			DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
			Timer0_SetDelay(5);
			state=LCD_FirstNibbleWait;
		case LCD_FirstNibbleWait:
			DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
			Timer0_SetDelay(5);
			state=LCD_SecondNibble;
			break;
		case LCD_SecondNibble:
			PORTA = ((cmd << 4) | (PORTA & 0x0F));    // sends lower nibble
			Timer0_SetDelay(5);	
			DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
			Timer0_SetDelay(5);
			state=LCD_SecondNibbleWait;
			break;
		case LCD_SecondNibbleWait:
			DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
			Timer0_SetDelay(5);
			state==LCD_OK;
			break;
		default:
		break;
	}
	}
	
	return state;
	
	
}

void LCD_WriteChar(uint8_t data)
{
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_RS_PIN , DIO_PIN_HIGH);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_RW_PIN , DIO_PIN_LOW);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
	Timer0_SetDelay(5);
	PORTA = ((data & 0xF0) | (PORTA & 0x0F));
	Timer0_SetDelay(5);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
	Timer0_SetDelay(5);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
	Timer0_SetDelay(5);
	PORTA = ((data << 4) | (PORTA & 0x0F));
	Timer0_SetDelay(5);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_HIGH);
	Timer0_SetDelay(5);
	DIO_SetPinValue(LCD_4BIT_MODE_CMD_PORT , LCD_E_PIN , DIO_PIN_LOW);
	Timer0_SetDelay(5);
	
}

void LCD_WriteString(uint8_t* str)
{
	uint8_t  cnt = 0;
	
	while(str[cnt] != '\0')
	{
		LCD_WriteChar(str[cnt]);
		cnt++;
	}
}


void LCD_WriteInteger(uint16_t  num)
{
	uint16_t y=1;
	while(num>0)
	{
		y=(y*10)+(num%10);
		num=num/10;
	}
	while(y>1)
	{
		LCD_WriteChar((y%10)+48);
		y=y/10;
	}
}

void LCD_GoToLocation(uint8_t row , uint8_t col)
{
	uint8_t Loc[2] = {0x80 , 0xc0};
	
	LCD_WriteCommand(Loc[row]+col);
}

void LCD_Clear(void)
{
	LCD_WriteCommand(0X01);
}

