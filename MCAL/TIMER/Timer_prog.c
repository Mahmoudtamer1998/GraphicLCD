/***************************************************************************/
/***************************************************************************/
 /*********************	Author: Mahmoud Tamer *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: Timer		 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "TIMER_reg.h"
#include "TIMER_private.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"

static void (*TIMER0_pvOVFCallBackFunc)(void)=NULL;
static void (*TIMER0_pvCTCCallBackFunc)(void)=NULL;
static void (*TIMER1_pvOFCallBackFunc)(void)=NULL;
static void (*TIMER1_pvOCCallBackFunc)(void)=NULL;
static void (*HWICU_pvCallBackFunc)(void)=NULL;
static uint8 Schedule_u8Periodicity;
static uint32 Schedule_u32TimeMS;
static uint8 OF_KEY=0;

void TIMER0_voidInit(void)
{
	//set CTC mode
	//CLR_BIT(TCCR0,TCCR0_WGM00);
	//SET_BIT(TCCR0,TCCR0_WGM01);

	//fast PWM mode
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	//compare output mode :set on top clear on compare(non inverted)
	CLR_BIT(TCCR0,TCCR0_COM00);
	SET_BIT(TCCR0,TCCR0_COM01);

	//set prescaler /64
	TCCR0 &= 0b11111000;
	TCCR0 |= 3;



	//set compare value =64 for 32 usec*/
	 OCR0= 64;
	//OCR0=64;//for 32 usec on time

	//compare match interrupt enable
	SET_BIT(TIMSK,TIMSK_OCIE0);
}

void TIMER0_voidSetCompVal(uint8 Copy_u8CompVal)
{
	OCR0=Copy_u8CompVal;
}


uint8 Timer0_u8SetCallBack(uint8 Copy_u8IntType,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		if(Copy_u8IntType == TIMER_u8_OVF_INT)
		{
			TIMER0_pvOVFCallBackFunc=Copy_pvCallBackFunc;
		}
		else if(Copy_u8IntType==TIMER_u8_CTC_INT)
		{
			TIMER0_pvCTCCallBackFunc=Copy_pvCallBackFunc;
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER0 CTC ISR
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(TIMER0_pvCTCCallBackFunc!=NULL)
	{
		TIMER0_pvCTCCallBackFunc();
	}
	else
	{
		//Do nothing
	}
}

void TIMER1_voidInit(void)
{
	//Set fast PWM for channel A
	//SET_BIT(TCCR1A,TCCR1A_COM1A1);
	//CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//default is normal mode
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	//Wave form generation mode Fast PWM with top value =ICR1 reg
	//CLR_BIT(TCCR1A,TCCR1A_WGM10);
	//SET_BIT(TCCR1A,TCCR1A_WGM11);
	//SET_BIT(TCCR1B,TCCR1B_WGM12);
	//SET_BIT(TCCR1B,TCCR1B_WGM13);

	//Set top value =40000 for 20ms period time
	//ICR1=40000;

	//Initialize compare value with 2000 for 1ms on time
	//OCR1A=2000;
	//Interrupt Enable (overflow)
	SET_BIT(TIMSK,TIMSK_TOIE1);
	//Prescaler division by 8
	SET_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);
}

void Timer1_voidDisableOVInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TOIE1);
}

uint8 Timer1_u8OFSetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER1_pvOFCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER1 overflow ISR
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(TIMER1_pvOFCallBackFunc!=NULL)
	{
		TIMER1_pvOFCallBackFunc();
	}
	else
	{
		//Do nothing
	}
}

void TIMER1_voidSetCompVal(uint16 Copy_u16CompVal)
{
	OCR1A=Copy_u16CompVal;
}

void TIMER1_voidSetTimerVal(uint16 Copy_u16Val)
{
	TCNT1=Copy_u16Val;
}

uint16 TIMER1_u16GetTimerReading(void)
{
	return TCNT1;
}



void HWICU_voidInit(void)
{
	//Input Capture Edge Select (rising)
	SET_BIT(TCCR1B,TCCR1B_ICES1);
	//Input Capture Interrupt Enable
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

void HWICU_voidSetEdgeTrigger(uint8 Copy_EdgeTrigger)
{
	if(Copy_EdgeTrigger==RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if (Copy_EdgeTrigger==FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
}

void HWICU_voidDisableInterrupt(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

uint16 HWICU_voidGetCaptureReading(void)
{
	return ICR1;
}

uint8 HWICU_SetCallBack(void(*Copy_pvHWICUCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvHWICUCallBackFunc!=NULL)
	{
		HWICU_pvCallBackFunc=Copy_pvHWICUCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//HWICU ISR
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(HWICU_pvCallBackFunc!=NULL)
	{
		HWICU_pvCallBackFunc();
	}
	else
	{
		//Do nothing
	}
}

uint8 Timer1_u8OCSetCallBack(void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		TIMER1_pvOCCallBackFunc=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

uint8 Schedule(void(*Copy_pvSchFunc)(void),uint32 Copy_u32TimeMS,uint8 Copy_u8Periodicity)
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvSchFunc!=NULL)
	{
		Schedule_u8Periodicity=Copy_u8Periodicity;
		Schedule_u32TimeMS=Copy_u32TimeMS;
		//CTC
		CLR_BIT(TCCR1A,TCCR1A_WGM10);
		CLR_BIT(TCCR1A,TCCR1A_WGM11);
		SET_BIT(TCCR1B,TCCR1B_WGM12);
		CLR_BIT(TCCR1B,TCCR1B_WGM13);

		if(Copy_u32TimeMS>4194)
		{
			OCR1A=(uint16)((((uint32)4193UL*1000UL))/64);
			OF_KEY=1;
		}
		else
		{
			OCR1A=(uint16)((((uint32)Copy_u32TimeMS*1000))/64);
		}

		//Interrupt Enable (output compare)
		SET_BIT(TIMSK,TIMSK_OCIE1A);

		//Prescaler division by 1024
		SET_BIT(TCCR1B,TCCR1B_CS10);
		CLR_BIT(TCCR1B,TCCR1B_CS11);
		SET_BIT(TCCR1B,TCCR1B_CS12);

		Timer1_u8OCSetCallBack(Copy_pvSchFunc);
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

//TIMER1 output compare1A ISR
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void)
{
	static uint32 Local_u32CurrentValue;
	static uint8 Counter=0;
	static uint8 KEY=0;
	if(Counter==0)
	{
		Local_u32CurrentValue=Schedule_u32TimeMS;
		Counter=1;
	}
	if(TIMER1_pvOCCallBackFunc!=NULL)
	{
		if(KEY==1)
		{
			TIMER1_pvOCCallBackFunc();
			Local_u32CurrentValue=Schedule_u32TimeMS+4194;
			KEY=0;
			if(Schedule_u8Periodicity==ONCE)
			{
				CLR_BIT(TIMSK,TIMSK_OCIE1A);
			}
		}

		if(OF_KEY==1)
		{
			Local_u32CurrentValue=Local_u32CurrentValue-4195;
			if(Local_u32CurrentValue>4194)
			{
				OCR1A=(uint16)((((uint32)4193*1000UL))/64);
			}
			else
			{
				OCR1A=(uint16)((((uint32)Local_u32CurrentValue*1000UL))/64);
				KEY=1;
			}
		}
		else
		{
			OCR1A=(uint16)((((uint32)Local_u32CurrentValue*1000UL))/64);
			TIMER1_pvOCCallBackFunc();
			if(Schedule_u8Periodicity==ONCE)
			{
				CLR_BIT(TIMSK,TIMSK_OCIE1A);
			}
		}
	}
	else
	{
		//Do nothing
	}
}


