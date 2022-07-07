/*
 * epwm_0.h
 *
 *  Created on: 2022年3月23日
 *      Author: ZGJ
 */

#ifndef APP_EPWM_EPWM_0_H_
#define APP_EPWM_EPWM_0_H_
#include "DSP28x_Project.h"

#ifndef CPU_CLK
#define  CPU_CLK  150e6               // 系统时钟 150MHz
#endif

#ifndef PWM_CLK
#define  PWM_CLK  20e3                // 开关频率 20kHz
#endif

void Setup_ePWM1(void);
void Setup_ePWM2(void);

#endif /* APP_EPWM_EPWM_0_H_ */
