/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer *******************************/
/*********************	Date:29/10/2021		 *******************************/
/*********************	Layer: MCAL			 *******************************/
/*********************	Version:1.00		 *******************************/
/***************************************************************************/
/***************************************************************************/

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidMstrInit(void);

void SPI_voidSlaveInit(void);

uint8 SPI_u8Transceive(uint8 copy_u8Data);

void SPI_voidMstrResetSlave(uint8 Copy_u8Port,uint8 Copy_u8Pin);

#endif
