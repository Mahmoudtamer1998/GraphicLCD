/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer			  **********************/
/*********************	Date:23/9/2021				  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef PORT_REG_H_
#define PORT_REG_H_

#define DDRA		*((volatile uint8*)0x3A)
#define PORTA		*((volatile uint8*)0x3B)

#define DDRB		*((volatile uint8*)0x37)
#define PORTB		*((volatile uint8*)0x38)

#define DDRC		*((volatile uint8*)0x34)
#define PORTC		*((volatile uint8*)0x35)

#define DDRD		*((volatile uint8*)0x31)
#define PORTD		*((volatile uint8*)0x32)


#endif
