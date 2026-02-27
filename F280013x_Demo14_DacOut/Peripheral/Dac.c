/*
 * Dac.c
 *
 *  Created on: 2025年5月28日
 *      Author: Administrator
 */

#include "Dac.h"


void DacInit(void){
    EALLOW;

    //使能DAC输出
    AnalogSubsysRegs.CMPSSCTL.bit.CMPSSCTLEN = 1;
    AnalogSubsysRegs.CMPSSCTL.bit.CMP1LDACOUTEN = 1;

    //使能COMP 和 DAC模块
    Cmpss1Regs.COMPCTL.bit.COMPDACE = 1;

    //选择DAC的来源 (0 DACHVALA is updated from DACHVALS; 1 DACHVALA is updated from the high ramp generator)
    Cmpss1Regs.COMPDACHCTL.bit.DACSOURCE = 0;

    //按项目需求配置DAC输出电压；
    Cmpss1Regs.DACLVALS.bit.DACVAL = 0;

    EDIS;
}
