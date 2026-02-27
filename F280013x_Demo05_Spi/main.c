#include "f28x_project.h"

#include "Gpio.h"
#include "Timer.h"
#include "Sci.h"
#include "Spi.h"



#include "Timer0_ISR.h"
#include "Timer1_ISR.h"
#include "Timer2_ISR.h"



#include "Dac8552.h"



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
    EDIS;

    //
    // Initialize the Device Peripheral. For this example, initialize the
    // Cpu Timers.
    // Scia.
    //
    InitCpuTimers();
    SciaInit();
    SpiInit();
    void Dac8552Init();

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
    IER |= M_INT1;  //定时器0中断使能
    IER |= M_INT13; //定时器1中断使能
    IER |= M_INT14; //定时器2中断使能

    EALLOW;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //定时器中断使能；
    EDIS;



    //Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        DAC8552_Set_Channel_A(0);
        DELAY_US(10);
        DAC8552_Set_Channel_B(0);
        DELAY_US(10);

        DAC8552_Set_Channel_A(65535);
        DELAY_US(10);
        DAC8552_Set_Channel_B(65535);
        DELAY_US(10);

    }

}


