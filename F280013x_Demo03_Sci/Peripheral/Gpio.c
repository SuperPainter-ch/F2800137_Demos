/*
 * Gpio.c
 *
 *  Created on: 2025年4月26日
 *      Author: Painter
 */
#include "Gpio.h"


void GpioInit(void){

    EALLOW;

    // GPIOA DATA数据全清0
    GpioDataRegs.GPADAT.all = 0ul;
    // GPIOB DATA数据全清0
    GpioDataRegs.GPBDAT.all = 0ul;


    //LED
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0; //配置为IO口
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;  //配置为输出模式
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;  //配置为上拉

    //LED
    GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0; //配置为IO口
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;  //配置为输出模式
    GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;  //配置为上拉



//    //KEY
//    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0; //配置为IO口
//    GpioCtrlRegs.GPADIR.bit.GPIO24 = 0;  //配置为输入模式
//    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;  //配置为上拉
//    GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; //输入滤波
//
//
////    LED
//    GpioCtrlRegs.GPAAMSEL.bit.GPIO20 = 0;
//    AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO20 = 1;
//
//    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0; //配置为IO口
//    GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;  //配置为输出模式
//    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;  //配置为上拉

    EDIS;
}



// 应用
// GpioDataRegs.GPASET.bit.GPIO20 = 1; //置高电平
// GpioDataRegs.GPACLEAR.bit.GPIO20 = 1; //置低电平
// GpioDataRegs.GPATOGGLE.bit.GPIO20 = 1; //电平翻转
//
//
// KEY = GpioDataRegs.GPADAT.bit.GPIO20; //读取GPIO

