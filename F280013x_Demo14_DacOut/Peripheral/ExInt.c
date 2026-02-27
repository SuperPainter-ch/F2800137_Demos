/*
 * ExInt.c
 *
 *  Created on: 2025年5月23日
 *      Author: Administrator
 */
#include "ExInt.h"


void ExIntInit(void){
    EALLOW;

    //外部中断输入
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0; //GPIO功能
    GpioCtrlRegs.GPBDIR.bit.GPIO33 = 0;  //输入
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;  //内部上拉使能
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 2;//脉冲滤除,采样窗口 0:系统同步   1:3samples   2:6samples


    InputXbarRegs.INPUT4SELECT = 33; //定位中断引脚

    XintRegs.XINT1CR.bit.POLARITY = 2;  //下降沿触发
    XintRegs.XINT1CR.bit.ENABLE = 1;

    EDIS;

}

