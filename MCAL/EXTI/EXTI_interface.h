/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer		  **********************/
/*********************	Date:25/9/2021				  **********************/
/*********************	Layer: MCAL					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#define ENABLED			1
#define DISABLED		2

#define INT0 	0
#define INT1 	1
#define INT2 	2

void EXTI_voidInit(void);

uint8 EXTI_u8SetSenseControl(uint8 Copy_IntNum, uint8 Copy_u8Sense);
uint8 EXTI_u8EnableInterrupt(uint8 Copy_IntNum);
uint8 EXTI_u8DisableInterrupt(uint8 Copy_IntNum);
uint8 EXTI_u8SetCallBack(uint8 Copy_IntNum,void(*Copy_pvCallBackFunc)(void));

#endif
