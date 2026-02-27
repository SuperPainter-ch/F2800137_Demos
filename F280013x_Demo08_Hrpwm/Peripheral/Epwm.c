/*
 * Epwm.c
 *
 *  Created on: 2025Äê5ÔÂ22ÈÕ
 *      Author: Administrator
 */
#include "Epwm.h"

Uint16 hrcmpa = 0;
Uint16 hrcmpb = 0;


// 1Mhz AB»¥²¹
void HrpwmInit(void){
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;   // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;   // Disable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    // EPWM Module 1 config
    EPwm1Regs.TBPRD = PWM_PRD; // Period = 900 TBCLK counts
    EPwm1Regs.TBPHS.bit.TBPHS = 0; // Set Phase register to zero
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET; // set actions for EPWM1A
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET; // set actions for EPWM1B
    EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;

//    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
//    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
//    EPwm1Regs.DBFED.bit.DBFED = 0;
//    EPwm1Regs.DBRED.bit.DBRED = 0;

    // HRPWM Module config

    EPwm1Regs.HRCNFG.all = 0x0; // clear all bits first
    EPwm1Regs.HRCNFG.bit.EDGMODE = HR_FEP; // Control Falling Edge Position
    EPwm1Regs.HRCNFG.bit.EDGMODEB = HR_FEP;
    EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP; // CMPAHR controls the MEP
    EPwm1Regs.HRCNFG.bit.CTLMODEB = HR_CMP;
    EPwm1Regs.HRCNFG.bit.HRLOAD = HR_CTR_ZERO; // Shadow load on CTR=Zero
    EPwm1Regs.HRCNFG.bit.HRLOADB = HR_CTR_ZERO;
    EPwm1Regs.HRCNFG.bit.AUTOCONV = 1;

//    EPwm1Regs.HRCNFG2.bit.CTLMODEDBFED = 0;
//    EPwm1Regs.HRCNFG2.bit.CTLMODEDBRED = 0;
//    EPwm1Regs.HRCNFG2.bit.EDGMODEDB = 3;
//
//    EPwm1Regs.DBFEDHR.bit.DBFEDHR = 0;
//    EPwm1Regs.DBREDHR.bit.DBREDHR = 0;




    EDIS;

    // Run Time (Note: Example execution of one run-time instant)
    //===========================================================
    EPwm1Regs.CMPA.bit.CMPA = PWM_PRD*0.5; // adjust duty for output EPWM1A
    EPwm1Regs.CMPB.bit.CMPB = PWM_PRD*0.5; // adjust duty for output EPWM1A
    EPwm1Regs.CMPA.bit.CMPAHR = 0;
    EPwm1Regs.CMPB.bit.CMPBHR = 0;
}

void SetHrpwm(void){
    EPwm1Regs.CMPA.bit.CMPA = PWM_PRD*0.5; // adjust duty for output EPWM1A
    EPwm1Regs.CMPB.bit.CMPB = PWM_PRD*0.5; // adjust duty for output EPWM1A
    EPwm1Regs.CMPA.bit.CMPAHR = hrcmpa<<8;
    EPwm1Regs.CMPB.bit.CMPBHR = hrcmpb<<8;
}
