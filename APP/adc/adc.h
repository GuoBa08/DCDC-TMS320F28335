/*
 * adc.h
 *
 *  Created on: 2022Äê3ÔÂ29ÈÕ
 *      Author: ZGJ
 */

#ifndef APP_ADC_ADC_H_
#define APP_ADC_ADC_H_
#include "DSP28x_Project.h"

#define ADC_MODCLK 3
#define ADC_CKPS 0x1 // ADC module clock = HSPCLK/2*ADC_CKPS = 25.0MHz/(1*2) = 12.5MH
#define ADC_SHCLK 0xf // S/H width in ADC module periods = 16 ADC clocks

void Setup_Adc(void);

#endif /* APP_ADC_ADC_H_ */
