/*
 * led.c
 *
 *  Created on: 2022年3月18日
 *      Author: ZGJ
 */
#include "led.h"

void Led_Init(void)
{
    EALLOW;
    GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;   //将GPIO75设置为GPIO功能
    GpioCtrlRegs.GPCDIR.bit.GPIO75 = 1; //将GPIO75方向设置为输出
    EDIS;
}




