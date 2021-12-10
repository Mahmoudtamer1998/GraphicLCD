/***************************************************************************/
/***************************************************************************/
/*********************	Author: Mahmoud Tamer		  **********************/
/*********************	Layer: Hal					  **********************/
/*********************	Version:1.00				  **********************/
/***************************************************************************/
/***************************************************************************/

#ifndef GLCD_INTERFACE_H_
#define GLCD_INTERFACE_H_

void N5110_DATAA(uint8 DATA);
void GLCD_Init(void);
void GLCD_VoidSendString(const char* Copy_pchString);
void GLCD_SendNum(uint16 Copy_u16Num);

void GLCD_VoidSendCommand(uint8 Copy_u8Command);
void GLCD_VoidSendData(uint8 Copy_u8Data);
void lcd_setXY(uint8 x, uint8 y);
void PWM_Draw(float dutyCycle,uint8 PeriodTime);
void drawDownLine(uint8 OffTime);
void drawPulse(void);
void drawUpLine(uint8 OnTime);
uint16 CountDigits(uint8 Copy_u16Number);

void RotateArr(uint16 Copy_Arr[],uint16 Copy_Arr2[],uint16 Copy_voidNumber);



void SendInteger(uint8 Copy_voidNumber,uint16 Copy_Arr[]);






#endif
