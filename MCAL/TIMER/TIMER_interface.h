/***************************************************************************/
/***************************************************************************/
/*********************	Author:Mahmoud Tamer	 *******************************/
/*********************	Date:06/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER_u8_OVF_INT		0
#define TIMER_u8_CTC_INT		1

#define RISING_EDGE		1
#define FALLING_EDGE	2

#define PERIODIC		0
#define ONCE			1

void TIMER0_voidInit(void);
uint8 Timer0_u8SetCallBack(uint8 Copy_u8IntType,void(*Copy_pvCallBackFunc)(void));
void TIMER0_voidSetCompVal(uint8 Copy_u8CompVal);


void TIMER1_voidInit(void);
void TIMER1_voidSetCompVal(uint16 Copy_u16CompVal);
void TIMER1_voidSetTimerVal(uint16 Copy_u16Val);
uint16 TIMER1_u16GetTimerReading(void);
uint8 Timer1_u8OFSetCallBack(void(*Copy_pvCallBackFunc)(void));
uint8 Timer1_u8OCSetCallBack(void(*Copy_pvCallBackFunc)(void));
void Timer1_voidDisableOVInterrupt(void);

void HWICU_voidInit(void);
void HWICU_voidSetEdgeTrigger(uint8 Copy_EdgeTrigger);
void HWICU_voidDisableInterrupt(void);
uint16 HWICU_voidGetCaptureReading(void);
uint8 HWICU_SetCallBack(void(*Copy_pvHWICUCallBackFunc)(void));

uint8 Schedule(void(*Copy_pvSchFunc)(void),uint32 Copy_u32TimeMS,uint8 Copy_u8Periodicity);

#endif
