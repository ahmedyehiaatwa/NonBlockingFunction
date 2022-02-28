/*
 * Timer.c
 *
 * Created: 29/05/2021 18:28:43
 *  Author: Ahmed
 */ 

#include "Timer.h"

//#include <avr/interrupt.h>

uint8_t static NUM_OVF = 0;
uint8_t static INIT_VALUE = 0;

 void(*Ptr_0)(void);
 void(*Ptr_1)(void);
 
// static void (*delayCallBack)(void);
static uint8_t cnt = 0;

sint8_t Timer0_Init (timer* t, uint8_t n)
{
	switch(n){
	case 0:	
	CLR_BIT(TCCR0, 3); // Set normal mode including step below //
	CLR_BIT(TCCR0, 6);
	SET_BIT(SREG, 7); // Enable global interrupt//
	SET_BIT(TIMSK, 0); //Enable overflow interrupt 
	t->intialized = 1;
	break;
	default:
	return INVALID_TIMER_NUM;
	}
	return SUCCESS_STAT;
}


uint8_t Timer0_SetDelay (uint32_t Delay_Ms)
{
	uint8_t Tick_Time = (PRESCALER / OVFTime) ;
	
	uint32_t Total_Ticks = ((Delay_Ms * 1000) / Tick_Time); // in microsecond (millisecond *1000)
	
	NUM_OVF = Total_Ticks / MaxTicks ;
	
	INIT_VALUE = MaxTicks - (Total_Ticks % MaxTicks) ;
	
	TCNT0 = INIT_VALUE;
	
	if (INIT_VALUE != 0)
	{
		NUM_OVF++;
	}
}

sint8_t Timer0_Start (timer* t)
{
	if(t->intialized != 1)
	return TIMER_NOT_INIT_ERROR;
	
	SET_BIT(TCCR0, 0); //Start timer using prescaler 1024//
	CLR_BIT(TCCR0, 1);
	SET_BIT(TCCR0, 2);
	return SUCCESS_STAT;
}

sint8_t Timer0_Stop (timer* t)
{
	if(t->intialized != 1)
	return TIMER_NOT_INIT_ERROR;
	CLR_BIT(TCCR0, 0); // Stop timer //
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);
	return SUCCESS_STAT;
}

void Set_CallBack_0(void(*p)(void))
{
	Ptr_0 = p;
}


void __vector_10(void)
{
	cnt++;
	
	if(cnt==NUM_OVF)
	{
		cnt=0;
		(*Ptr_0)();
		TCNT0 = INIT_VALUE;
	}
}

/*
ISR(TIMER0_OVF_vect)
{
	static uint32_t cnt = 0;
	
	cnt++;
	
	if(cnt==NUM_OVF)
	{
		cnt=0;
		(*Ptr_0)();
		TCNT0 = INIT_VALUE;
	}
}

// TIMER 1 //


void Timer1_Init (void)
{
	CLR_BIT(TCCR1A,0);  // select mode 4 CTC //
	CLR_BIT(TCCR1A,1);
	SET_BIT(TCCR1B,3);
	CLR_BIT(TCCR1B,4);
	
	SET_BIT(SREG, 7); // Set global interrupt //
	SET_BIT(TIMSK,4); // Enable Output compare match interrupt 
}

void Timer1_SetDelay (uint32_t Delay_Ms)
{
	if (Delay_Ms<4000)
	{
		uint8_t Tick_Time= 1024 / 16;
		uint8_t NUM_Ticks = (Delay_Ms*1000) / Tick_Time;
	//	OCR1A = NUM_Ticks - 1;
	}
}

void Timer1_Start (void)
{
		SET_BIT(TCCR1B,0);
		CLR_BIT(TCCR1B,1);
		SET_BIT(TCCR1B,2);
}

void Timer1_Stop (void)
{
	CLR_BIT(TCCR1B,0);
	CLR_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);
}

void Set_CallBack_1(void(*p)(void))
{
	Ptr_1 = p;
}


ISR(TIMER1_COMPA_vect)
{
	(*Ptr_1)();
}


void PWM_Init(void)
{
	SET_BIT(DDRB,3); // OC0 pin output
    SET_BIT(TCCR0,3); // FAST PWM MODE
	SET_BIT(TCCR0,6);
	SET_BIT(TCCR0,5);  // NON INVERTED MODE
	
}

void PWM0_Generate(uint16_t Duty_Cycle)
{
	OCR0 = ((Duty_Cycle *256) / 100) -1;
}

void PWM0_Start(void)
{
	SET_BIT(TCCR0,0); // NO PRESCALER //
	
}

*/