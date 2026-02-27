/*
 * Timer2_ISR.c
 *
 *  Created on: 2025Äê5ÔÂ1ÈÕ
 *      Author: Painter
 */
#include "Timer2_ISR.h"

//
// cpuTimer2ISR CPU Timer2 ISR with interrupt counter
//
__interrupt void cpuTimer2ISR(void)
{
    GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;
    GpioDataRegs.GPATOGGLE.bit.GPIO11 = 1;


    //
    // The CPU acknowledges the interrupt
    //
    CpuTimer2.InterruptCount++;
}


