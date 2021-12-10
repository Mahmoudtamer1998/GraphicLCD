/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer *******************************/
/*********************	Date:29/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef SPI_REG_H_
#define SPI_REG_H_

#define SPDR			*((volatile uint8*)0x2F)		/*SPI data register*/
#define SPSR			*((volatile uint8*)0x2E)		/*SPI status register*/
#define SPSR_SPIF		7								/*SPI interrupt flag*/
#define SPSR_SPI2X		0								/*Prescaler bit 2*/

#define SPCR			*((volatile uint8*)0x2D)		/*SPI control register*/
#define SPCR_SPE		6								/*SPI enable*/
#define SPCR_MSTR		4								/*Master bit*/
#define SPCR_SPR1		1								/*Prescaler bit 1*/
#define SPCR_SPR0		0								/*Prescaler bit 0*/

#endif
