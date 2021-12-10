/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer		  **********************/
/*********************	Date:25/9/2021				  **********************/
/*********************	Layer: MCAL					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef EXTI_REG_H_
#define EXTI_REG_H_

#define GICR			*((volatile uint8*)0x5B) //general interrupt control register
#define GICR_INT1		7						 //INT1 PIE bit
#define GICR_INT0		6
#define GICR_INT2		5

#define MCUCR			*((volatile uint8*)0x55) //MCU control register
#define MCUCR_ISC11		3						 //Interrupt 1 sense control bit 1
#define MCUCR_ISC10		2 						 //Interrupt 1 sense control bit 0
#define MCUCR_ISC01		1
#define MCUCR_ISC00		0

#define MCUCSR			*((volatile uint8*)0x54) //MCU control and status register
#define MCUCSR_ISC2		6						 //Int2 sense control bit


#endif
