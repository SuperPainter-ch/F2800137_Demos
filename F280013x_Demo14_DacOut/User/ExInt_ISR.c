/*
 * ExInt_ISR.c
 *
 *  Created on: 2025年5月23日
 *      Author: Administrator
 */
#include "ExInt_ISR.h"



__interrupt void xInt1ISR(void){
//    GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;//清除中断Group1的标识位
}
