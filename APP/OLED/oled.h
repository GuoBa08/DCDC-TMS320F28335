/*
 * oled.h
 *
 *  Created on: 2022年5月1日
 *      Author: ZGJ
 *      @brief: OLED函数接口头文件
 */

#ifndef APP_OLED_OLED_H_
#define APP_OLED_OLED_H_
#include "DSP28x_Project.h"
#include "math.h"
#define OLED_RES_SET()        GpioDataRegs.GPASET.bit.GPIO27=1
#define OLED_RES_CLR()        GpioDataRegs.GPACLEAR.bit.GPIO27=1

#define OLED_SDA_SET()        GpioDataRegs.GPASET.bit.GPIO16=1
#define OLED_SDA_CLR()        GpioDataRegs.GPACLEAR.bit.GPIO16=1

#define OLED_SCK_SET()        GpioDataRegs.GPASET.bit.GPIO18=1
#define OLED_SCK_CLR()        GpioDataRegs.GPACLEAR.bit.GPIO18=1

#define OLED_CMD  0 //写命令
#define OLED_DATA 1 //写数据

#define devAddr  0x3C//OLED的从机地址

#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64

#define OLED_CMD  0
#define OLED_DATA 1

void delay_1ms(Uint16 t);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);
Uint32 oled_pow(unsigned char m,unsigned char n);
void OLED_ShowNum(unsigned char x,unsigned char y,Uint32 num,unsigned char len,unsigned char size2);
void OLED_ShowDecimalNum(unsigned char x,unsigned char y,float shu,unsigned char size2);
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size);
void OLED_Clear(void);
void OLED_Init(void);


#endif /* APP_OLED_OLED_H_ */
