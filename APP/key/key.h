/*
 * key.h
 *
 *  Created on: 2022年3月18日
 *      Author: ZGJ
 */

#ifndef APP_KEY_H_
#define APP_KEY_H_
#include "DSP28x_Project.h"

#define KEY1  GpioDataRegs.GPADAT.bit.GPIO17 //读取按键1
#define KEY1_PRES   1   //KEY1按下

/*-----------------------------------------------------------------------------
Define the structure of the PWM Driver Object
-----------------------------------------------------------------------------*/
typedef struct {
        void (*init)(void);       // Pointer to the key_init function
        unsigned char (*scan)(unsigned char mode);     // Pointer to the key_scan function
        } KEY;

extern KEY key_module;

void Key_Init(void);
unsigned char Key_Scan(unsigned char mode);



#endif /* APP_KEY_H_ */
