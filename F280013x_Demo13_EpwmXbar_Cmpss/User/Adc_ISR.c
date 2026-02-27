/*
 * Adc_ISR.c
 *
 *  Created on: 2025Äê5ÔÂ23ÈÕ
 *      Author: Administrator
 */
#include "Adc_ISR.h"



//
// adcA1ISR - ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{

    RAW_ADCGet();

    if(EPwm1Regs.TZFLG.bit.DCAEVT1==1 || EPwm2Regs.TZFLG.bit.DCAEVT1==1 || EPwm3Regs.TZFLG.bit.DCAEVT1==1)
    {
        GpioDataRegs.GPBSET.bit.GPIO32 = 1;
        EALLOW;
        EPwm1Regs.TZCLR.all = 0xffff;
        EPwm2Regs.TZCLR.all = 0xffff;
        EPwm3Regs.TZCLR.all = 0xffff;
        EDIS;
    }else{
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
    }



    //
    // Clear the interrupt flag
    //
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    //
    // Check if overflow has occurred
    //
    if(1 == AdcaRegs.ADCINTOVF.bit.ADCINT1)
    {
        AdcaRegs.ADCINTOVFCLR.bit.ADCINT1 = 1; //clear INT1 overflow flag
        AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; //clear INT1 flag
    }
    //
    // Acknowledge the interrupt
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}
