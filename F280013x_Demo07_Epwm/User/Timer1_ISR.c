/*
 * Timer1_ISR.c
 *
 *  Created on: 2025Äê5ÔÂ1ÈÕ
 *      Author: Painter
 */
#include "Timer1_ISR.h"

//
// cpuTimer1ISR - CPU Timer1 ISR with interrupt counter
//
__interrupt void cpuTimer1ISR(void)
{
//    GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;



    //
    // The CPU acknowledges the interrupt
    //
    CpuTimer1.InterruptCount++;
}


