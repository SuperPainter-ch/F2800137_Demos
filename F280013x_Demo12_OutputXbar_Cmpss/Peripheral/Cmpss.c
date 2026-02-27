/*
 * Cmpss.c
 *
 *  Created on: 2025年5月23日
 *      Author: Administrator
 */

#include "Cmpss.h"


void CmpssInit(void){
    EALLOW;

    //配置GPIO6为复用外设2--OUTPUTXBAR4
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0; //配置为IO口
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;  //配置为输出模式
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;  //配置为上拉
    GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;

    //配置A2为 CMPSS1.0
    GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;
    AnalogSubsysRegs.CMPHPMXSEL.bit.CMP1HPMXSEL = 0;

    EDIS;


    EALLOW;

    //使能COMP 和 DAC模块
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;

    //选择比较器输入电压的来源（外部接入或者内部DAC）
    Cmpss1Regs.COMPCTL.bit.COMPHSOURCE = 0;

    //选择DAC的来源 (0 DACHVALA is updated from DACHVALS; 1 DACHVALA is updated from the high ramp generator)
    Cmpss1Regs.COMPDACHCTL.bit.DACSOURCE = 0;

    //按项目需求配置DAC输出电压；
    Cmpss1Regs.DACHVALS.bit.DACVAL = 1000;


    //配置Output_XBar输出路径
    OutputXbarRegs.OUTPUT4MUX0TO15CFG.bit.MUX0 = 0; // MUX0=0  CMPSS1.CTRIPOUTH
    OutputXbarRegs.OUTPUT4MUXENABLE.bit.MUX0 = 1;

    EDIS;
}
