/*
 * Timer0_ISR.c
 *
 *  Created on: 2025Äê5ÔÂ1ÈÕ
 *      Author: Painter
 */
#include "Timer0_ISR.h"

//
// cpuTimer0ISR - CPU Timer0 ISR with interrupt counter
//
__interrupt void cpuTimer0ISR(void)
{
    CpuTimer0.InterruptCount++;


//    GpioDataRegs.GPBTOGGLE.bit.GPIO32 = 1;


    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


