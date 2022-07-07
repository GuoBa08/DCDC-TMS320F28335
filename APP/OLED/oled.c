/*
 * oled.c
 *
 *  Created on: 2022年5月1日
 *      Author: ZGJ
 *      @brief: OLED显示函数接口
 */
#include "oled.h"
#include "iic.h"
#include "font.h"

void delay_1ms(Uint16 t)
{
    while(t--)
    {
        DELAY_US(1000);
    }
}

/**
 *  @brief                   写入一个字节
 *  @parameter                  dat：写入的数据 ； rom：准备写入数据的寄存器地址
 *  @return_value               无
 */
void Send_Byte(unsigned char dat,Uint16 rom)
{
    while(WriteData(devAddr,rom,1,&dat));//等待发送成功
}

void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd == OLED_CMD)
    {
        Send_Byte(dat, 0x00);   //发送命令
    }
    else
    {
        Send_Byte(dat, 0x40);   //发送数据
    }
}

/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WR_Byte(0xb0+m,0);     //page0-page1
        OLED_WR_Byte(0x00,0);       //low column start address
        OLED_WR_Byte(0x10,0);       //high column start address
        for(n=0;n<128;n++)
            {
                OLED_WR_Byte(fill_Data,1);
            }
    }
}

void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}



//x:0~127
//y:0~63
//size:16/12
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size)
{
    unsigned char c=0,i=0;
    c=chr-' ';
    if(x>Max_Column-1){x=0;y=y+2;}
    if(Char_Size ==16)
    {
        OLED_Set_Pos(x,y);
        for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
        OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
    }
    else
    {
        OLED_Set_Pos(x,y);
        for(i=0;i<6;i++)
        OLED_WR_Byte(F6x8[c][i],OLED_DATA);
    }
}

Uint32 oled_pow(unsigned char m,unsigned char n)
{
    Uint32 result=1;
    while(n--)result*=m;
    return result;
}

void OLED_ShowNum(unsigned char x,unsigned char y,Uint32 num,unsigned char len,unsigned char size2)
{
    unsigned char t,temp;
    unsigned char enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
    }
}

void OLED_ShowDecimalNum(unsigned char x,unsigned char y,float shu,unsigned char size2)
{
    unsigned char sz[32],i=0;  //
    long dd,ff;
    if(shu>=0)
        sz[0]='+';
    else
    {                   //
        sz[0]='-';
        shu=fabsf(shu);  //fabs函数
    }
    if(shu<1.0)        //
    {
        sz[1]='0';    //数字和ASCII码之间由于相差了0X30
        sz[2]='.';
        dd=(long)(shu*1000); //
        sz[3]=dd/100+0x30;
        sz[4]=dd%100/10+0x30;//价格加OX30是因为，传送的是ASCII码
        sz[5]=dd%10+0x30;//就是一直扩大再除而已，其实拿一个数，例如0.356
        sz[6]='\0';       //精确到小数点后面第3位。
        //sz[5]='E';       //
    }                    //加到第5位的话，就乘以100000即可！
    else                //12.678
    {
        dd=(long)shu;   //整数部分
        ff=dd;
        for(i=1;;i++)  //不断的除以10，直到变成小数为止。其实13个的数组容量不仅小数有局限，整数部分也是有局限的
        {
         if(dd/10==0)
               break;
            dd=dd/10;
        }
        sz[i+1]='.';
        dd=(long)(shu*1000)%1000;
        sz[i+2]=dd/100+0x30;
        sz[i+3]=dd%100/10+0x30;
        sz[i+4]=dd%10+0x30;
        sz[i+5]='\0';
        //sz[i+5]='E'; //换用‘e'作为标志位，算是自己的协议吧，中断里对于’e'的处理有没有问题呢？

        for(;;i--)
        {
            sz[i]=ff%10+0x30;
            if(ff/10==0)
               break;
            ff=ff/10;    //这里既是将前面的整数部分还原至数组的前面了
        }
    }
    OLED_ShowString(x,y,sz,size2);
}

void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {
        OLED_ShowChar(x,y,chr[j],Char_Size);
        x+=8;
        if(x>120){x=0;y+=2;}
        j++;
    }
}

void OLED_Clear(void)
{
    unsigned char i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA);
    }
}

//此初始化函数应在IIC初始化之后
void OLED_Init(void)
{
    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//

    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//

    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//

    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//

    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//

    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}

