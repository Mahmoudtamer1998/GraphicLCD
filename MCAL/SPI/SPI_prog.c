/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer*******************************/
/*********************	Date:27/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"

#include "SPI_config.h"

#include "SPI_private.h"
#include "SPI_reg.h"
#include "SPI_interface.h"


void SPI_Inits(void){


	//Master select
	SET_BIT(SPCR,SPCR_MSTR);

	//Set Prescaler :/128
	SET_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

	// SPR0
	SET_BIT(SPCR,SPCR_SPR0);

	//SPI enable
	SET_BIT(SPCR,SPCR_SPE);
}


uint8 SPI_u8Transceive(uint8 copy_u8Data)
{
	//1-Send data
	SPDR=copy_u8Data;

	//wait for transfer complete
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	//return received data
	return SPDR;
}

void SPI_voidMstrResetSlave(uint8 Copy_u8Port,uint8 Copy_u8Pin)
{
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8_PIN_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8_PIN_LOW);
}
