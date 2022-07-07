/*
 * epwm_0.c
 *
 *  Created on: 2022年3月23日
 *      Author: ZGJ
 */

#include "epwm_0.h"

void Setup_ePWM1(void)
{
    // 设置时钟
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;  //Disable TBCLK within the ePWM
    SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;
    EDIS;

    // 设置相关引脚
    InitEPwm1Gpio();

    //时基模块TB
    EPwm1Regs.TBPRD = CPU_CLK/(2*PWM_CLK);  // 周期值 SP = CPU_CLK/(2*PWM_CLK)
    EPwm1Regs.TBPHS.half.TBPHS = 0;         // 相位为0
    EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;      // 时基时钟 TBCLK=SYSCLKOUT=1/150M
    EPwm1Regs.TBCTL.bit.CLKDIV = 0;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;          // 禁用相位寄存器
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;        // 增减计数

    //计数比较模块CC
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // 影子装载模式
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // CTR = 0 或 CTR = PRD时装载
    EPwm1Regs.CMPA.half.CMPA =0;        // 设置初始占空比为0

    //动作模块AQ
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // 向上计数且CTR=CMPA时，ePWM1A置低
    EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;       // 向下计数且CTR=CMPA时，ePWM1A置高

    //死区产生模块DB
    EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;    // ePWM1A是双边沿输入
    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;     // ePWM1A不翻转，ePWM1B翻转
    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // 使能双边沿延时
    EPwm1Regs.DBRED = 30;               // 上升沿延时 DBRED*TBCLK = 200ns
    EPwm1Regs.DBFED = 30;               // 下降沿延时 DBRED*TBCLK = 200ns

    //错误联防模块TZ
    EALLOW;
    EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;        // 错误事件发生时，强制ePWM1A低状态
    EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;        // 错误事件发生时，强制ePWM1B低状态
    EDIS;

    // 开启时基子模块时钟以启动计数
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

}

void Setup_ePWM2(void)  // ePWM2模块配置子函数
{

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;  //Disable TBCLK within the ePWM
    SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;
    EDIS;

    // 设置相关引脚
    InitEPwm2Gpio();

    //时基模块TB
    EPwm2Regs.TBPRD = CPU_CLK/(2*PWM_CLK);             // 周期值设置与 ePWM1 的相同
    EPwm2Regs.TBPHS.half.TBPHS = 0;     // 相位为 0
    EPwm2Regs.TBCTL.bit.HSPCLKDIV = 0;  // 时基时钟 TBCLK=SYSCLKOUT=1/150M
    EPwm2Regs.TBCTL.bit.CLKDIV = 0;
    EPwm2Regs.TBCTL.bit.PHSEN = 0;      // 禁用相位寄存器
    EPwm2Regs.TBCTL.bit.CTRMODE = 2;    // 增减计数

    //计数比较模块CC
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW; // 影子装载模式
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO_PRD; // CTR = 0 或 CTR = PRD时装载
    EPwm2Regs.CMPA.half.CMPA =0;        // 设置初始占空比为0

    //动作模块AQ
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;       // 向上计数且CTR=CMPA时，ePWM2A置低
    EPwm2Regs.AQCTLA.bit.CAD = AQ_SET;       // 向下计数且CTR=CMPA时，ePWM2A置高

    //死区产生模块DB
    EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;    // ePWM2A是双边沿输入
    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC;     // ePWM2A不翻转，ePWM2B翻转
    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;   // 使能双边沿延时
    EPwm2Regs.DBRED = 30;               // 上升沿延时 DBRED*TBCLK = 200ns
    EPwm2Regs.DBFED = 30;               // 下降沿延时 DBRED*TBCLK = 200ns

    //错误联防模块TZ
    EALLOW;
    EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;        // 错误事件发生时，强制ePWM2A低状态
    EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;        // 错误事件发生时，强制ePWM2B低状态
    EDIS;

    //事件触发模块ET
    EPwm2Regs.ETSEL.bit.SOCAEN = 1;     // 使能 ePWM2SOCA 信号产生
    EPwm2Regs.ETSEL.bit.SOCASEL = 1;    // 当TBCTR=0时产生 ePWM2SOCA信号
    EPwm2Regs.ETPS.bit.SOCAPRD = 1;     // 在第1个事件时产生 ePWM2SOCA信号

    // 开启时基子模块时钟以启动计数
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;
}

