/*
 * key.c
 *
 *  Created on: 2022年3月18日
 *      Author: ZGJ
 */

#include "key.h"

/*------------------------------------------------------------------------------
Default Initializers for the Key Object
------------------------------------------------------------------------------*/
KEY key_module = {
            .init = Key_Init,
            .scan = Key_Scan,
};


/*--------按键初始化函数--------*/
//功能：初始化按键IO口
//输入：无
//输出：无
/*---------------------------*/
void Key_Init(void)
{
    EALLOW;

    GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;    //IO口设置为GPIO功能
    GpioCtrlRegs.GPADIR.bit.GPIO17 = 0; //方向为输入
    GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0; //配置上拉

    EDIS;

    GpioDataRegs.GPASET.bit.GPIO17 = 1; //默认高电平
}


/*--------按键处理函数--------*/
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY1按下
//注意此函数有响应优先级,KEY1>KEY2
/*---------------------------*/
unsigned char Key_Scan(unsigned char mode)
{
    static unsigned char key_up=1;//按键按松开标志
    if(mode)key_up=1;  //支持连按
    if(key_up && KEY1==0)
    {
        DELAY_US(10000);    //去抖动
        key_up=0;
        if(KEY1==0)return KEY1_PRES;
    }else if(KEY1==1)key_up=1;
    return 0;// 无按键按下
}
