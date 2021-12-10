/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer		  **********************/
/*********************	Date:25/9/2021				  **********************/
/*********************	Layer: MCAL					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_type.h"
#include "EXTI_private.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"
#include "EXTI_config.h"

//to hold ISR addresses
static void (*EXTI_pvCallBackFunc[3])(void)={NULL};

/*void EXTI_voidInit(void)
{
	//activate falling edge sense control on int1
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);
	//activate falling edge sense control on int0
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
	//enable PIE to int1
	SET_BIT(GICR,GICR_INT1);
	//enable PIE to int0
	SET_BIT(GICR,GICR_INT0);
}*/

void EXTI_voidInit(void)
{
	//set INT0 sense control
#if EXTI_u8_INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif EXTI_u8_INT0_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);

#elif EXTI_u8_INT0_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#elif EXTI_u8_INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);

#else
#error "Wrong EXIT_u8_INT0_SENSE Config option"
#endif

	//set INT1 sense control
#if EXTI_u8_INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif EXTI_u8_INT1_SENSE == ON_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	CLR_BIT(MCUCR,MCUCR_ISC11);

#elif EXTI_u8_INT1_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#elif EXTI_u8_INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC10);
	SET_BIT(MCUCR,MCUCR_ISC11);

#else
#error "Wrong EXIT_u8_INT1_SENSE Config option"
#endif

	//set INT2 sense control
#if EXTI_u8_INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif EXTI_u8_INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "Wrong EXIT_u8_INT2_SENSE Config option"
#endif

//set INT0 initial state
#if EXTI_u8_INT0_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT0);
#elif EXTI_u8_INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT0);
#else
#error "Wrong EXIT_u8_INT0_SENSE Config option"
#endif

//set INT1 initial state
#if EXTI_u8_INT1_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT1);
#elif EXTI_u8_INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT1);
#else
#error "Wrong EXIT_u8_INT1_SENSE Config option"
#endif

//set INT2 initial state
#if EXTI_u8_INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR,GICR_INT2);
#elif EXTI_u8_INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR,GICR_INT2);
#else
#error "Wrong EXIT_u8_INT2_SENSE Config option"
#endif

}

uint8 EXTI_u8SetSenseControl(uint8 Copy_IntNum, uint8 Copy_u8Sense)
{
	uint8 LocalErrState= OK;
	switch(Copy_IntNum)
	{
	case 0:
		{
			switch (Copy_u8Sense)
			{
			case LOW_LEVEL   :CLR_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
			case ON_CHANGE   :SET_BIT(MCUCR,MCUCR_ISC00);CLR_BIT(MCUCR,MCUCR_ISC01);break;
			case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00);SET_BIT(MCUCR,MCUCR_ISC01);break;
			case RISING_EDGE :SET_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
			default			 :LocalErrState=NOK;break;
			}
		}break;
	case 1:
	{
		switch (Copy_u8Sense)
		{
		case LOW_LEVEL   :CLR_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		case ON_CHANGE   :SET_BIT(MCUCR,MCUCR_ISC10);CLR_BIT(MCUCR,MCUCR_ISC11);break;
		case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		case RISING_EDGE :SET_BIT(MCUCR,MCUCR_ISC10);SET_BIT(MCUCR,MCUCR_ISC11);break;
		default			 :LocalErrState=NOK;break;
		}
	}break;
	case 2:
		{
			switch (Copy_u8Sense)
			{
			case FALLING_EDGE:CLR_BIT(MCUCSR,MCUCSR_ISC2);break;
			case RISING_EDGE :SET_BIT(MCUCSR,MCUCSR_ISC2);break;
			default			 :LocalErrState=NOK;break;
			}
		}break;
	default:LocalErrState=NOK;break;
	}
	return LocalErrState;
}

uint8 EXTI_u8EnableInterrupt(uint8 Copy_IntNum)
{
	uint8 LocalErrState= OK;
	switch(Copy_IntNum)
	{
	case 0:SET_BIT(GICR,GICR_INT0);break;
	case 1:SET_BIT(GICR,GICR_INT1);break;
	case 2:SET_BIT(GICR,GICR_INT2);break;
	default:LocalErrState= NOK;break;
	}
	return LocalErrState;
}

uint8 EXTI_u8DisableInterrupt(uint8 Copy_IntNum)
{
	uint8 LocalErrState= OK;
	switch(Copy_IntNum)
	{
	case 0:CLR_BIT(GICR,GICR_INT0);break;
	case 1:CLR_BIT(GICR,GICR_INT1);break;
	case 2:CLR_BIT(GICR,GICR_INT2);break;
	default:LocalErrState= NOK;break;
	}
	return LocalErrState;
}

uint8 EXTI_u8SetCallBack(uint8 Copy_IntNum,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=OK;
	if(Copy_pvCallBackFunc!=NULL)
	{
		if(Copy_IntNum<3)
		{
			EXTI_pvCallBackFunc[Copy_IntNum]=Copy_pvCallBackFunc;
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


//INT0 ISR
void __vector_1(void)	__attribute__((signal));
void __vector_1(void)
{
	if(EXTI_pvCallBackFunc[INT0]!=NULL)
	{
		EXTI_pvCallBackFunc[INT0]();
	}
}

//INT1 ISR
void __vector_2(void)	__attribute__((signal));
void __vector_2(void)
{
	if(EXTI_pvCallBackFunc[INT1]!=NULL)
	{
		EXTI_pvCallBackFunc[INT1]();
	}
}

//INT2 ISR
void __vector_3(void)	__attribute__((signal));
void __vector_3(void)
{
	if(EXTI_pvCallBackFunc[INT2]!=NULL)
	{
		EXTI_pvCallBackFunc[INT2]();
	}
}
