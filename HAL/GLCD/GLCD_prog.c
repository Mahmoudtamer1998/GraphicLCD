/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer		  **********************/
/*********************	Date:23/9/2021				  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_type.h"
#include <util/delay.h>
#include <string.h>
#include "DIO_reg.h"
#include "DIO_interface.h"
#include "PORT_reg.h"
#include "PORT_interface.h"
#include "SPI_interface.h"
#include "GLCD_private.h"
#include "GLCD_config.h"
#include "GLCD_interface.h"
#include "Font.h"


void GLCD_SendNum(uint16 Copy_u16Num)
{
	char NumStr[10];
	sprintf(NumStr,"%d",Copy_u16Num);
	GLCD_VoidSendString(NumStr);
}

void N5110_DATAA(uint8 DATA)
{
	// SET DC to Data
	SET_BIT(PORTB,GLCD_DC_PIN);

	// send enable pulse
	CLR_BIT(PORTB,GLCD_SCE_PIN);

	// send data
	SPI_u8Transceive(DATA);

	// set DC to Command
	CLR_BIT(PORTB, GLCD_DC_PIN);
	// disable pulse
	SET_BIT(PORTB,GLCD_SCE_PIN);

}


void GLCD_VoidSendCommand(uint8 Copy_u8Command)
{
	// SET DC to command
	CLR_BIT(PORTB,GLCD_DC_PIN);

	// send enable pulse
	CLR_BIT(PORTB,GLCD_SCE_PIN);

	// send data
	SPI_u8Transceive(Copy_u8Command);

	// set DC to data
	SET_BIT(PORTB, GLCD_DC_PIN);
	// disable pulse
	SET_BIT(PORTB,GLCD_SCE_PIN);

}


void GLCD_Init()
{
	//N5110_Reset();  /* reset the display */
	CLR_BIT(PORTB,GLCD_RST_PIN);
	_delay_ms(100);
	SET_BIT(PORTB,GLCD_RST_PIN);
	GLCD_VoidSendCommand(0x21);  /* command set in addition mode */
	GLCD_VoidSendCommand(0xC0);  /* set the voltage by sending C0 means VOP = 5V */
	GLCD_VoidSendCommand(0x07);  /* set the temp. coefficient to 3 */
	GLCD_VoidSendCommand(0x13);  /* set value of Voltage Bias System */
	GLCD_VoidSendCommand(0x20);  /* command set in basic mode */
	GLCD_VoidSendCommand(0b00001100);  /* display result in normal mode */
}



void GLCD_VoidSendString(const char* Copy_pchString)
{

	// set DC pin to high for data
	SET_BIT(PORTB, GLCD_DIN_PIN);

	// Enable pulse
	CLR_BIT(PORTB,GLCD_SCE_PIN);


	uint16 lenan = strlen(Copy_pchString);  /* measure the length of data */
	for (uint16 g=0; g<lenan; g++)
	{
		for (uint16 index=0; index<5; index++)
		{
			SPI_u8Transceive(ASCII[Copy_pchString[g] - 0x20][index]);  /* send the data on data register */
		}
		SPI_u8Transceive(0x00);
	}
	// disable pulse
	SET_BIT(PORTB,GLCD_SCE_PIN);

}

void lcd_setXY(uint8 x, uint8 y)  /* set the column and row */
{
	GLCD_VoidSendCommand(0x80 | x);
	GLCD_VoidSendCommand(0x40| y);
}

void PWM_Draw(float dutyCycle,uint8 PeriodTime)
{

	uint8 CountCycles=0;

	uint8 OnTime = (dutyCycle/100)*(PeriodTime/15);
	uint8 OffTime = (PeriodTime/15)-OnTime;
	lcd_setXY(0,5);
	for(CountCycles=0;CountCycles<5;CountCycles++)
	{
		drawPulse();
		drawUpLine(OnTime);
		drawPulse();
		drawDownLine(OffTime);
	}
	lcd_setXY(0,4);
	drawPulse();
	lcd_setXY(1,4);
	drawMiddleLine((PeriodTime/15));
	drawPulse();
}

void drawUpLine(uint8 OnTime)
{
	uint8 counter=0;
	while(counter<OnTime)
	{
		N5110_DATAA(0b00000001);
		counter++;
	}
}

void drawPulse(void)
{
	N5110_DATAA(0b11111111);
}

void drawDownLine(uint8 OffTime)
{
	uint8 counter=0;
	while(counter<OffTime)
	{
		N5110_DATAA(0b10000000);
		counter++;
	}
}

void drawMiddleLine(uint8 Copy_Sahm)
{
	uint8 counter=0;
	while(counter<Copy_Sahm)
	{
		N5110_DATAA(0b00010000);
		counter++;
	}
}
