#include "f28x_project.h"

#include "Gpio.h"
#include "Timer.h"
#include "Sci.h"
#include "Epwm.h"
#include "Adc.h"
#include "ExInt.h"
#include "Cmpss.h"
#include "Dac.h"


#include "Adc_ISR.h"
#include "Timer0_ISR.h"
#include "Timer1_ISR.h"
#include "Timer2_ISR.h"
#include "ExInt_ISR.h"




Uint16 dacvalue = 0;

/**
 * main.c
 */
int main(void)
{
    // 初始化时钟
    InitSysCtrl();

    //
    // Initialize Peripheral
    //
    InitGpio();
    GpioInit();

    //初始化PIE和PIE寄存器，关掉CPU中断
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;


    //初始化中断向量
    InitPieVectTable();

    //
    // Map ISR functions
    //
    EALLOW;
    PieVectTable.TIMER0_INT = &cpuTimer0ISR;
    PieVectTable.TIMER1_INT = &cpuTimer1ISR;
    PieVectTable.TIMER2_INT = &cpuTimer2ISR;
    PieVectTable.ADCA1_INT = &adcA1ISR;     // Function for ADCA interrupt 1
    PieVectTable.XINT1_INT = &xInt1ISR; //外部中断1
    EDIS;

    //
    // Initialize the Device Peripheral. For this example, initialize the
    // Cpu Timers.
    // Scia.
    //
    InitCpuTimers();
    SciaInit();
    EpwmInit();
    ADCInit();
    ExIntInit();
//    CmpssInit();
    DacInit();

    //
    // Configure CPU-Timer 0, 1, and 2 to interrupt every second:
    // 120MHz CPU Freq, 0.5 second Period (in uSeconds)
    //
    ConfigCpuTimer(&CpuTimer0, 120, 500000);
    ConfigCpuTimer(&CpuTimer1, 120, 500000);
    ConfigCpuTimer(&CpuTimer2, 120, 500000);

    //
    // To ensure precise timing, use write-only instructions to write to the
    // entire register. Therefore, if any of the configuration bits are changed
    // in ConfigCpuTimer and InitCpuTimers, the below settings must also be
    // be updated.
    //
    CpuTimer0Regs.TCR.all = 0x4000;
    CpuTimer1Regs.TCR.all = 0x4000;
    CpuTimer2Regs.TCR.all = 0x4000;

    PieCtrlRegs.PIEACK.all = 0xFFFF;
    IER |= M_INT1;  //ADC中断使能
    IER |= M_INT1;  //定时器0中断使能
    IER |= M_INT13; //定时器1中断使能
    IER |= M_INT14; //定时器2中断使能
    IER |= M_INT1;  //xINT1使能

    EALLOW;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; //ADC中断使能
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //定时器中断使能；
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1; //INT1使能
    EDIS;



    //Enable Global Interrupt (INTM) and realtime interrupt (DBGM)

    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {

        dacvalue++;
        if(dacvalue>4000){
            dacvalue = 0;
        }
        Cmpss1Regs.DACLVALS.bit.DACVAL = dacvalue;

        DELAY_US(10);


    }

}


