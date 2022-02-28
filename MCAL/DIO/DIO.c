/*
 * DIO.c
 *
 * Created: 3/20/2021 10:59:51 AM
 *  Author: Ali
 */ 

#include "DIO.h"




DIO_ERR_STATE DIO_SetPortDir(uint8_t Port, uint8_t Dir)
{
	DIO_ERR_STATE state = DIO_OK;
	switch(Port)
	{
		case DIO_PORTA :
		DDRA = Dir;
		break;
		
		case DIO_PORTB :
		DDRB = Dir;
		break;
		
		case DIO_PORTC :
		DDRC = Dir;
		break;
		
		case DIO_PORTD :
		DDRD = Dir;
		break;
		
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}

DIO_ERR_STATE DIO_SetPinDir(uint8_t Port , uint8_t Pin , uint8_t Dir)
{
	DIO_ERR_STATE state = DIO_OK;
	switch (Dir)
	{
		case  DIO_PIN_OUTPUT :
		 
		 switch (Port)
		 {
			 case DIO_PORTA :
			 SET_BIT(DDRA , Pin);
			 break;
			 
			 case DIO_PORTB :
			 SET_BIT(DDRB , Pin);
			 break;
			 
			 case DIO_PORTC :
			 SET_BIT(DDRC , Pin);
			 break;
			 
			 case DIO_PORTD :
			 SET_BIT(DDRD , Pin);
			 break;
			 
			 default :
			 state = DIO_ERR;
			 break;
		 }
		
		break;
		
		
		case  DIO_PIN_INPUT :
		
		switch (Port)
		{
			case DIO_PORTA :
			CLR_BIT(DDRA , Pin);
			break;
			
			case DIO_PORTB :
			CLR_BIT(DDRB , Pin);
			break;
			
			case DIO_PORTC :
			CLR_BIT(DDRC , Pin);
			break;
			
			case DIO_PORTD :
			CLR_BIT(DDRD , Pin);
			break;
			
			default :
			state = DIO_ERR;

			break;
		}
		
		break;
		
	
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}

DIO_ERR_STATE DIO_SetPortValue(uint8_t Port, uint8_t Vlaue)
{
	DIO_ERR_STATE state = DIO_OK;
	switch(Port)
	{
		case DIO_PORTA :
		PORTA = Vlaue;
		break;
		
		case DIO_PORTB :
		PORTB = Vlaue;
		break;
		
		case DIO_PORTC :
		PORTC = Vlaue;
		break;
		
		case DIO_PORTD :
		PORTD = Vlaue;
		break;
		
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}



DIO_ERR_STATE DIO_SetPinValue(uint8_t Port , uint8_t Pin , uint8_t Value)
{
	DIO_ERR_STATE state = DIO_OK;
	switch (Value)
	{
		case  DIO_PIN_HIGH :
		
		switch (Port)
		{
			case DIO_PORTA :
			SET_BIT(PORTA , Pin);
			break;
			
			case DIO_PORTB :
			SET_BIT(PORTB , Pin);
			break;
			
			case DIO_PORTC :
			SET_BIT(PORTC , Pin);
			break;
			
			case DIO_PORTD :
			SET_BIT(PORTD , Pin);
			break;
			
			default :
			state = DIO_ERR;
			break;
		}
		
		break;
		
		
		case  DIO_PIN_LOW :
		
		switch (Port)
		{
			case DIO_PORTA :
			CLR_BIT(PORTA , Pin);
			break;
			
			case DIO_PORTB :
			CLR_BIT(PORTB , Pin);
			break;
			
			case DIO_PORTC :
			CLR_BIT(PORTC , Pin);
			break;
			
			case DIO_PORTD :
			CLR_BIT(PORTD , Pin);
			break;
			
			default :
			state = DIO_ERR;
			break;
		}
		
		break;
		
		
		default:
		break;
		
	}
	return state;
}

DIO_ERR_STATE DIO_ReadPortValue(uint8_t Port, uint8_t* Value)
{
	DIO_ERR_STATE state = DIO_OK;
	switch(Port)
	{
		case DIO_PORTA :
		*Value = PINA;
		break;
		
		case DIO_PORTB :
		*Value = PINB;
		break;
		
		case DIO_PORTC :
		*Value = PINC;
		break;
		
		case DIO_PORTD :
		*Value = PIND;
		break;
		
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}
DIO_ERR_STATE DIO_ReadPinValue(uint8_t Port, uint8_t Pin ,uint8_t* Value)
{
	DIO_ERR_STATE state = DIO_OK;
	switch (Port)
	{
		case DIO_PORTA :
		*Value = GET_BIT(PINA , Pin);
		break;
		
		case DIO_PORTB :
		*Value = GET_BIT(PINB , Pin);
		break;
		
		case DIO_PORTC :
		*Value = GET_BIT(PINC , Pin);
		break;
		
		case DIO_PORTD :
		*Value = GET_BIT(PIND , Pin);
		break;
		
		default:
		state = DIO_ERR;
		break;
	}
	return state;
}

DIO_ERR_STATE DIO_TogglePort(uint8_t Port)
{
	DIO_ERR_STATE state = DIO_OK;
	switch(Port)
	{
		case DIO_PORTA :
		PORTA ^= 0xff;
		break;
		
		case DIO_PORTB :
		PORTB ^= 0xff;
		break;
		
		case DIO_PORTC :
		PORTC ^= 0xff;
		break;
		
		case DIO_PORTD :
		PORTD ^= 0xff;
		break;
		
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}

DIO_ERR_STATE DIO_TogglePin(uint8_t Port, uint8_t Pin)
{
	DIO_ERR_STATE state = DIO_OK;
	switch (Port)
	{
		case DIO_PORTA :
		Toggle_BIT(PORTA , Pin);
		break;
		
		case DIO_PORTB :
		Toggle_BIT(PORTB , Pin);
		break;
		
		case DIO_PORTC :
		Toggle_BIT(PORTC , Pin);
		break;
		
		case DIO_PORTD :
		Toggle_BIT(PORTD , Pin);
		break;
		
		default:
		state = DIO_ERR;
		break;
	}
	return state;
}

DIO_ERR_STATE DIO_SetPullUp(uint8_t Port, uint8_t Pin)
{
	DIO_ERR_STATE state = DIO_OK;
	switch(Port)
	{
		case DIO_PORTA :
		SET_BIT(PORTA , Pin);
		break;
		
		case DIO_PORTB :
		SET_BIT(PORTB , Pin);
		break;
		
		case DIO_PORTC :
		SET_BIT(PORTC , Pin);
		break;
		
		case DIO_PORTD :
		SET_BIT(PORTD , Pin);
		break;
		
		default:
		state = DIO_ERR;
		break;
		
	}
	return state;
}