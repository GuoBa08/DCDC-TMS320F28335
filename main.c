/*
 * main.c
 *
 *  Created on: 2022年3月14日
 *      Author: ZGJ
 *      此工程为双向DCDC双闭环控制程序
 */

/*---------------------Include---------------------*/
#include "DSP28x_Project.h"
#include "key.h"
#include "led.h"
#include "epwm_0.h"
#include "adc.h"
#include "math.h"
#include "pi.h"
#include "iic.h"
#include "oled.h"
/*---------------------------------函数声明---------------------------------------------*/
interrupt void adc_isr(void);

/*----------------------------------宏定义----------------------------------------------*/
#define  CPU_CLK  150e6               // 系统时钟 150MHz
#define  PWM_CLK  20e3                // 开关频率 20kHz
#define  Tsam     1/PWM_CLK      // 采样周期 Tsam=1/20k=50us
#define  SP       CPU_CLK/(2*PWM_CLK) // ePWM周期寄存器的值 3750

//调节器参数
#define  Kp_V   0.05                     // 电压环比例系数
#define  Ki_V   0.05                     // 电压环积分系数
#define  Kp_I   0.1                     // 电流环比例系数
#define  Ki_I   0.03                     // 电流环积分系数

//限幅值
#define  Umax       25              // 过压保护阈值
#define  Imax       1.6               // 过流保护阈值

/*-------------------------------变量定义及初始化----------------------------------------*/
float  Uo=0;                          // 输出电压
float  IL=0;                          // 负载电流
float  Uin=0;                         // 输入电压
int    Uo_AD=0;
int    IL_AD=0;
int    Uin_AD=0;
float  Irefm = 1.5;
float  Urefm = 0.7;                    // 输出电压幅值给定 Uom*=24V，最大占空比限定
float  Iref=0;                        // 电流环输入指令值 Io*
float  Uref=24.3;                        // 输出电压指令值 Uo*
float     Uoc = 0;                      // 输出电压设定值,范围为0-1，比较器设定值为SP*Uoc
int    start_flag = 0;                // 启动标志，为1表示装置正常运行
int    protect_flag = 0;              // 保护标志，为1表示已启动保护
PI_t PI_Voltage;
PI_t PI_Current;
#define N 30
void main()
{
    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd, &RamfuncsRunStart);
    InitFlash();
    //Step 0. 初始化调节器变量
    pi_init(&PI_Voltage, Kp_V, Ki_V, Tsam);
    pi_init(&PI_Current, Kp_I, Ki_I, Tsam);
    //Step 1. 初始化系统控制
    InitSysCtrl();  //Initialize System Control

    //Step 2. 初始化GPIO
    InitGpio(); //Initialize GPIO

    //Step 3. 清除所有中断并初始化中断向量表
    DINT;
    InitPieCtrl();  //Initialize the PIE control registers to their default state
    IER = 0x0000;   //Disable CPU interrupts and clear all CPU interrupt flags
    IFR = 0x0000;
    InitPieVectTable(); //Initialize the PIE vector table with pointers to the shell Interrupt't Service Routines(ISR)
    EALLOW;
    PieVectTable.ADCINT = &adc_isr;       // 将程序中需要的中断映射到中断向量表
    EDIS;

    //Step 4. 初始化外设
//    InitAdc();                            // 初始化ADC模块(使能ADC时钟，校验ADC，并给ADC上电)
    Led_Init();
    Key_Init();
    Init_I2CA();
    Setup_ePWM1();                        // 配置ePWM1模块
    Setup_ePWM2();                        // 配置ePWM2模块
    Setup_Adc();                          // 配置ADC模块
    EPwm1Regs.TBCTR = 0;                  // 计数器同时清零
    EPwm2Regs.TBCTR = 0;

    //Step 5. 使能中断
    IER |= M_INT8;                        //I2C
    IER |= M_INT1;                        // 使能CPU中断：ADCINT在第1组中断
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;    // 使能PIE中断：ADCINT是PIE第1组的第6个中断
    PieCtrlRegs.PIEIER8.bit.INTx1 = 1;    //I2C

    EINT;                                 // 使能总中断 INTM
    ERTM;                                 // 使能总实时中断 DBGM

    OLED_Init();//OLED初始化
    OLED_Clear();


    OLED_ShowString(0,0,"DC-DC",8);
    OLED_ShowString(0,2,"Ui:",8);
    OLED_ShowString(0,3,"Uo:",8);
    OLED_ShowString(0,4,"Io:",8);
    //Step 6. 循环等待中断
    for(; ;)
    {
        OLED_ShowDecimalNum(24,2,Uin,8);
        OLED_ShowDecimalNum(24,3,Uo,8);
        OLED_ShowDecimalNum(24,4,IL,8);
        OLED_ShowDecimalNum(24,5,Uoc,8);
//        asm("          NOP");
    }
}


interrupt void adc_isr(void)   // ADC中断子函数
{
    //数据读取与处理
    Uo_AD = AdcRegs.ADCRESULT0 >> 4;         // 读取AD转换结果
    IL_AD = AdcRegs.ADCRESULT1 >> 4;
    Uin_AD = AdcRegs.ADCRESULT2 >> 4;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;

    Uo = Uo_AD*3.0/4095;
    IL = IL_AD*3.0/4095;
    Uin = Uin_AD*3.0/4095;

    Uo = Uo * 13.33333 - 0.0933333;      // 计算电压电流实际值
    IL = (IL/0.82-2.5)/0.4;    //应根据实际采样电路重新计算
    Uin = Uin * 12.820513 - 0.0128205;

    //*******测试用*********
    //    Uin = 20;
    //    Uo = 24;
    //    IL = 1;
    //*******end*********

    //过压过流检测
    if ((IL>Imax))//(Uo>Umax)||
    {
        EALLOW;
        EPwm1Regs.TZFRC.bit.OST=1;           // 封锁ePWM1的驱动信号
        EPwm2Regs.TZFRC.bit.OST=1;           // 封锁ePWM2的驱动信号
        EDIS;
        protect_flag = 1;
        LED1_OFF;    // LED1灭
    }

    start_flag = 1;
    //欠压检测
    //根据输入电压范围确定阈值
//        if ((protect_flag==0)&&(Uin>=10)&&(Uin<=40))
//        {
//            EALLOW;
//            EPwm1Regs.TZCLR.bit.OST = 1;           // 清除联防信号，即PWM驱动复原
//            EPwm2Regs.TZCLR.bit.OST = 1;           // 清除联防信号，即PWM驱动复原
//            EDIS;
//            start_flag = 1;
//            LED1_ON;  // LED1亮
//        }
//        else
//        {
//            EALLOW;
//            EPwm1Regs.TZFRC.bit.OST = 1;           // 封锁ePWM1的驱动信号
//            EPwm2Regs.TZFRC.bit.OST = 1;           // 封锁ePWM1的驱动信号
//            EDIS;
//            start_flag = 0;
//            LED1_OFF;    // LED1灭
//        }

    //闭环运算
    if (start_flag == 1)
    {
        //电压外环计算
        Iref = pi_calc(&PI_Voltage, Uref, Uo);      //电压环输出给到电流内环指定值
        if(Iref > Irefm)  Iref = Irefm;            // 对电流内环指定值进行限幅

        //电流内环计算
        Uoc = pi_calc(&PI_Current, Iref, IL);
        //*******测试用*********
        //电压外环测试
        Uoc = Iref;
        //********end**********
        if(Uoc > Urefm)  Uoc = Urefm;            // 对电流调节器的输出进行限幅
    }

        //********************************
        //测试用
    //    Uoc = 0.5;  //开环控制调试用
        //********************************
    EPwm1Regs.CMPA.half.CMPA = (int)((1-Uoc)*SP);
    EPwm2Regs.CMPA.half.CMPA = (int)(Uoc*SP);
//    }
    //清除中断标志
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1; // 清除ADC的中断标志位
    PieCtrlRegs.PIEACK.bit.ACK1 = 1;    // 清除第1组的中断响应标志位，使CPU可以响应第1组更多中断
}

