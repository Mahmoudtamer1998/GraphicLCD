#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>
#include "STD_TYPES.h"
#include"BIT_MATH.h"
#include "Err_type.h"
/*HAL-Layer*/
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "SPI_interface.h"
#include"EXTI_interface.h"
#include "TIMER_interface.h"
#include "TIMER_reg.h"
#include "GIE_interface.h"
/*MCAL-Layer*/
#include "GLCD_interface.h"
/*Font lib*/
#include "Font.h"


void SW_ICU (void);
volatile static f32 SWICU_u16PeriodTicks =0;
volatile static f32 SWICU_u16ONTicks =0;


int main(void)
{
	uint16 Periodic_Time;
	uint16 DutyCycle;
	uint32 Freq;
	PORT_voidInit();

	EXTI_voidInit();
	EXTI_u8SetCallBack(INT0,&SW_ICU);

	SPI_Inits();		/*SPI initialize*/
	GLCD_Init();		/*GLCD initilize*/

	TIMER0_voidInit();     /*Generates PWM*/
	TIMER1_voidInit();     /*Reads the PWM signal*/

	GIE_voidEnableGlobal();
	PWM_Draw(25,255);

	while(1)
	{
		while((SWICU_u16ONTicks ==0 ) && (SWICU_u16PeriodTicks==0));

		//////////////////////////////////Freq/////////////////////////////////////////////
		Freq=1000000/Periodic_Time;
		lcd_setXY(0,0);
		GLCD_VoidSendString("FREQ= ");
		GLCD_SendNum(Freq);
		GLCD_VoidSendString(" Hz");
		////////////////////////////////DUTY_CYCLE/////////////////////////////////////////
		DutyCycle= (SWICU_u16ONTicks/SWICU_u16PeriodTicks)*100;
		lcd_setXY(0,1);
		GLCD_VoidSendString("D_CYCLE= ");
		GLCD_SendNum(DutyCycle);
		GLCD_VoidSendString("%");
		////////////////////////////////////Time/////////////////////////////////////////////
		Periodic_Time= SWICU_u16PeriodTicks * 0.5 +1;
		lcd_setXY(0,3);
		GLCD_VoidSendString("Time= ");
		GLCD_SendNum(Periodic_Time);
		GLCD_VoidSendString(" uSec");

		//////////////////////////////////////////////////////////////////////////////////////
	}
}


/*Call Back Function of timer T1*/
void SW_ICU (void)
{
	static uint8 Local_u8Counter=0;
	Local_u8Counter ++;

	if (Local_u8Counter==1)
	{
		TIMER1_voidSetTimerVal(0);

	}
	else if (Local_u8Counter == 2)
	{
		SWICU_u16PeriodTicks= TIMER1_u16GetTimerReading();
		EXTI_u8SetSenseControl(INT0, FALLING_EDGE);

	}
	else if (Local_u8Counter ==3)
	{
		SWICU_u16ONTicks = TIMER1_u16GetTimerReading()  - SWICU_u16PeriodTicks;
		//Local_u8Counter=0;
		EXTI_u8DisableInterrupt(INT0);
	}

}

