/*
 * led.h
 *
 *  Created on: 2022Äê3ÔÂ18ÈÕ
 *      Author: ZGJ
 */

#ifndef APP_LED_LED_H_
#define APP_LED_LED_H_
#include "DSP28x_Project.h"

#define LED1_ON  GpioDataRegs.GPCCLEAR.bit.GPIO75 = 1
#define LED1_OFF  GpioDataRegs.GPCSET.bit.GPIO75 = 1
#define LED1_TOGGLE GpioDataRegs.GPCTOGGLE.bit.GPIO75 = 1


void Led_Init(void);


#endif /* APP_LED_LED_H_ */
