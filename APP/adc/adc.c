/*
 * adc.c
 *
 *  Created on: 2022年3月29日
 *      Author: ZGJ
 */

#include "adc.h"

void Setup_Adc(void)  // ADC模块配置子函数
{
    EALLOW;
    SysCtrlRegs.HISPCP.all = 3; // HSPCLK = SYSCLKOUT/(2*3)=25MHz
    EDIS;

    InitAdc();   // For this example, init the ADC

    //设置ADC时钟
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;     // FCLK = HSPCLK / (2 * ADCCLKPS) = 12.5MHz
    AdcRegs.ADCTRL1.bit.CPS = 0;          // ADCCLK = FCLK / (CPS + 1) = 12.5MHz
    AdcRegs.ADCTRL1.bit.ACQ_PS = 5;       // 采样窗，每个通道采样时间 =(2+ACQ_PS)*ADCCLK

    //设置转换模式
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;     // 启动/停止模式
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 0;     // 禁用排序器覆盖
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;     // 级联排序器模式
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;    // 顺序采样模式

    //设置采样通道
    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 2; // 最大采样通道数为 3
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;  // 设置ADCINA0作为第1个采样通道
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1;  // 设置ADCINA1作为第2个采样通道
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2;  // 设置ADCINA2作为第3个采样通道

    //设置触发方式
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;// 允许ePWM的触发信号启动SEQ1
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // 使能SEQ1中断
}

