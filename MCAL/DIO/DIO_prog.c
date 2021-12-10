#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_type.h"

#include "DIO_private.h"
#include "DIO_reg.h"
#include "DIO_config.h"

#include "DIO_interface.h"

uint8 DIO_u8SetPinDirection(uint8 Copy_u8Port,uint8 Copy_u8PinNumber,uint8 Copy_u8Direction)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8PinNumber <= DIO_u8_PIN7)
	{

		if(Copy_u8Direction == DIO_u8_PIN_INPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8_PORTA: CLR_BIT(DDRA,Copy_u8PinNumber); break;
			case DIO_u8_PORTB: CLR_BIT(DDRB,Copy_u8PinNumber); break;
			case DIO_u8_PORTC: CLR_BIT(DDRC,Copy_u8PinNumber); break;
			case DIO_u8_PORTD: CLR_BIT(DDRD,Copy_u8PinNumber); break;
			default: Local_u8ErrorState= NOK;				   break;
			}
		}
		else if(Copy_u8Direction == DIO_u8_PIN_OUTPUT)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8_PORTA: SET_BIT(DDRA,Copy_u8PinNumber); break;
			case DIO_u8_PORTB: SET_BIT(DDRB,Copy_u8PinNumber); break;
			case DIO_u8_PORTC: SET_BIT(DDRC,Copy_u8PinNumber); break;
			case DIO_u8_PORTD: SET_BIT(DDRD,Copy_u8PinNumber); break;
			default: Local_u8ErrorState= NOK;				   break;
			}
		}
		else
		{
			/*Error direction input*/
			Local_u8ErrorState= NOK;
		}
	}
	else
	{
		/*error pin number input*/
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}

uint8 DIO_u8SetPortDirection(uint8 Copy_u8Port,uint8 Copy_u8Direction)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_u8Port)
	{
	case DIO_u8_PORTA : DDRA = Copy_u8Direction; break;
	case DIO_u8_PORTB : DDRB = Copy_u8Direction; break;
	case DIO_u8_PORTC : DDRC = Copy_u8Direction; break;
	case DIO_u8_PORTD : DDRD = Copy_u8Direction; break;
	default: Local_u8ErrorState= NOK; 			 break;

	}
	return Local_u8ErrorState;
}

uint8 DIO_u8SetPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNumber,uint8 Copy_u8Value)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8PinNumber <= DIO_u8_PIN7)
	{

		if(Copy_u8Value == DIO_u8_PIN_LOW)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8_PORTA: CLR_BIT(PORTA,Copy_u8PinNumber); break;
			case DIO_u8_PORTB: CLR_BIT(PORTB,Copy_u8PinNumber); break;
			case DIO_u8_PORTC: CLR_BIT(PORTC,Copy_u8PinNumber); break;
			case DIO_u8_PORTD: CLR_BIT(PORTD,Copy_u8PinNumber); break;
			default: Local_u8ErrorState= NOK;				   break;
			}
		}
		else if(Copy_u8Value == DIO_u8_PIN_HIGH)
		{
			switch(Copy_u8Port)
			{
			case DIO_u8_PORTA: SET_BIT(PORTA,Copy_u8PinNumber); break;
			case DIO_u8_PORTB: SET_BIT(PORTB,Copy_u8PinNumber); break;
			case DIO_u8_PORTC: SET_BIT(PORTC,Copy_u8PinNumber); break;
			case DIO_u8_PORTD: SET_BIT(PORTD,Copy_u8PinNumber); break;
			default: Local_u8ErrorState= NOK;				   break;
			}
		}
		else
		{
			/*Error direction input*/
			Local_u8ErrorState= NOK;
		}
	}
	else
	{
		/*error pin number input*/
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}

uint8 DIO_u8SetPortValue(uint8 Copy_u8Port,uint8 Copy_u8Value)
{
	uint8 Local_u8ErrorState = OK;

	switch(Copy_u8Port)
	{
	case DIO_u8_PORTA : PORTA = Copy_u8Value; break;
	case DIO_u8_PORTB : PORTB = Copy_u8Value; break;
	case DIO_u8_PORTC : PORTC = Copy_u8Value; break;
	case DIO_u8_PORTD : PORTD = Copy_u8Value; break;
	default: Local_u8ErrorState= NOK; 			 break;

	}
	return Local_u8ErrorState;
}

uint8 DIO_u8GetPinValue(uint8 Copy_u8Port,uint8 Copy_u8PinNumber,uint8* Copy_pu8Value)
{
	uint8 Local_u8ErrorState = OK;

	if(Copy_u8PinNumber <= DIO_u8_PIN7)
	{
		switch(Copy_u8Port)
		{
		case DIO_u8_PORTA : *Copy_pu8Value = GET_BIT(PINA,Copy_u8PinNumber); break;
		case DIO_u8_PORTB : *Copy_pu8Value = GET_BIT(PINB,Copy_u8PinNumber); break;
		case DIO_u8_PORTC : *Copy_pu8Value = GET_BIT(PINC,Copy_u8PinNumber); break;
		case DIO_u8_PORTD : *Copy_pu8Value = GET_BIT(PIND,Copy_u8PinNumber); break;
		default: Local_u8ErrorState= NOK; 			 break;

		}
	}
	else
	{
		Local_u8ErrorState= NOK;
	}

	return Local_u8ErrorState;
}
