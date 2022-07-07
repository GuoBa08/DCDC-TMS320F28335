/*
 * iic.h
 *
 *  Created on: 2022年5月1日
 *      Author: ZGJ
 *      @brief: I2C通信函数接口头文件
 */

#ifndef APP_IIC_IIC_H_
#define APP_IIC_IIC_H_
#include "DSP28x_Project.h"

//函数声明
Uint16  ReadData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, Uint16 *RamAddr);
Uint16  WriteData( Uint16 SlaveAddress, Uint16 RomAddress,Uint16 number, unsigned char *Wdata);
void IICwriteBit(Uint16 slaveaddress, Uint16 regaddress, unsigned char bitNum, unsigned char data);
void IICwriteBits(Uint16 slaveaddress,Uint16 regaddress,unsigned char bitStart,unsigned char length,unsigned char data);
Uint16  I2C_xrdy();
Uint16  I2C_rrdy();
void Init_I2CA(void);

#endif /* APP_IIC_IIC_H_ */
