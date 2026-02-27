/*
 * Epwm.c
 *
 *  Created on: 2025年5月22日
 *      Author: Administrator
 */
#include "Epwm.h"


// 50kHz 三相 相位差120度
void EpwmInit(void){
    EALLOW;

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;   // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;   // Disable pull-up on GPIO1 (EPWM1B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;   // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;   // Disable pull-up on GPIO3 (EPWM2B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;   // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;   // Disable pull-up on GPIO5 (EPWM3B)
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    // EPWM Module 1 config
    EPwm1Regs.TBPRD = PWM_PRD; // Period = 900 TBCLK counts
    EPwm1Regs.TBPHS.bit.TBPHS = 0; // Set Phase register to zero
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE; // Master module
    EPwm1Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm1Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm1Regs.EPWMSYNCOUTEN.bit.ZEROEN = 1;
    EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM1A
    EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM1B
    EPwm1Regs.AQCTLB.bit.CBD = AQ_CLEAR;

//    EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
//    EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
//    EPwm1Regs.DBFED.bit.DBFED = 20;
//    EPwm1Regs.DBRED.bit.DBRED = 20;


    // EPWM Module 2 config
    EPwm2Regs.TBPRD = PWM_PRD; // Period = 900 TBCLK counts
    EPwm2Regs.TBPHS.bit.TBPHS = 800; // Phase = 300/900 * 360 = 120 deg
    EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm2Regs.TBCTL.bit.PHSEN = TB_ENABLE; // Slave module
    EPwm2Regs.TBCTL.bit.PHSDIR = TB_DOWN; // Count DOWN on sync (=120 deg)
    EPwm2Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm2Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm2Regs.EPWMSYNCINSEL.bit.SEL = SYNC_IN_SRC_SYNCOUT_EPWM1;
    EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM2A
    EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM2B
    EPwm2Regs.AQCTLB.bit.CBD = AQ_CLEAR;

//    EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable dead-band module
//    EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi Complementary
//    EPwm2Regs.DBFED.bit.DBFED = 20;
//    EPwm2Regs.DBRED.bit.DBRED = 20;


    // EPWM Module 3 config
    EPwm3Regs.TBPRD = PWM_PRD; // Period = 900 TBCLK counts
    EPwm3Regs.TBPHS.bit.TBPHS = 800; // Phase = 300/900 * 360 = 120 deg
    EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Symmetrical mode
    EPwm3Regs.TBCTL.bit.PHSEN = TB_ENABLE; // Slave module
    EPwm2Regs.TBCTL.bit.PHSDIR = TB_UP; // Count UP on sync (=240 deg)
    EPwm3Regs.TBCTL.bit.PRDLD = TB_SHADOW;
    EPwm3Regs.TBCTL.bit.HSPCLKDIV=TB_DIV1;
    EPwm3Regs.EPWMSYNCINSEL.bit.SEL = SYNC_IN_SRC_SYNCOUT_EPWM1;
    EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO; // load on CTR=Zero
    EPwm3Regs.AQCTLA.bit.CAU = AQ_SET; // set actions for EPWM3A
    EPwm3Regs.AQCTLA.bit.CAD = AQ_CLEAR;
    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET; // set actions for EPWM3B
    EPwm3Regs.AQCTLB.bit.CBD = AQ_CLEAR;

//    EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // enable Dead-band module
//    EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi complementary
//    EPwm3Regs.DBFED.bit.DBFED = 20;
//    EPwm3Regs.DBRED.bit.DBRED = 20;

    EDIS;



    EALLOW;

    EPwm3Regs.ETSEL.bit.SOCAEN = 0;     // Disable SOC on A group
    EPwm3Regs.ETSEL.bit.SOCASEL = 2;    // Select SOC on up-count
    EPwm3Regs.ETPS.bit.SOCAPRD = 1;     // Generate pulse on 1st event

    EPwm3Regs.CMPA.bit.CMPA = 0x0001;   // Set compare A value to 1 counts

    EDIS;
    //
    // Start ePWM
    //
    EPwm3Regs.ETSEL.bit.SOCAEN = 1;    // Enable SOCA



    // Run Time (Note: Example execution of one run-time instant)
    //===========================================================
    EPwm1Regs.CMPA.bit.CMPA = 400; // adjust duty for output EPWM1A
    EPwm1Regs.CMPB.bit.CMPB = 400; // adjust duty for output EPWM1A
    EPwm2Regs.CMPA.bit.CMPA = 400; // adjust duty for output EPWM2A
    EPwm2Regs.CMPB.bit.CMPB = 400; // adjust duty for output EPWM2B
    EPwm3Regs.CMPA.bit.CMPA = 400; // adjust duty for output EPWM3A
    EPwm3Regs.CMPB.bit.CMPB = 400; // adjust duty for output EPWM3B
}
