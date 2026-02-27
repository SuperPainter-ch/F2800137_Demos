#include "f28x_project.h"

#include "Gpio.h"
#include "Timer.h"
#include "Sci.h"



#include "Timer0_ISR.h"
#include "Timer1_ISR.h"
#include "Timer2_ISR.h"
#include "SCI_ISR.h"


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
    PieVectTable.SCIA_RX_INT = &SCIA_Rx_isr;
    EDIS;

    //
    // Initialize the Device Peripheral. For this example, initialize the
    // Cpu Timers.
    // Scia.
    //
    InitCpuTimers();
    SciaInit();

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
    IER |= M_INT9; //SCIA中断使能

    EALLOW;
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //定时器中断使能；
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1; //SCIA中断使能
    EDIS;



    //Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    EINT;
    ERTM;

    //
    // Loop Forever
    //
//    uint16_t ReceivedChar;
//    unsigned char *msg;

    for(;;)
    {

//        msg = "\r\nEnter a character: \0";
//        transmitSCIAMessage(msg);
//
//        //接收数据错误，软件复位错误数据
//        if (SciaRegs.SCIRXST.bit.RXERROR == 1) //接收数据错误，软件复位错误数据
//        {
//            SciaRegs.SCICTL1.bit.SWRESET = 0x0;
//            SciaRegs.SCICTL1.bit.SWRESET = 0x1;
//        }
//        //
//        // Wait for character
//        //
//        while(SciaRegs.SCIFFRX.bit.RXFFST == 0)
//        {
//
//        } // wait for empty state
//
//        //
//        // Get character
//        //
//        ReceivedChar = SciaRegs.SCIRXBUF.all;
//
//        //
//        // Echo character back
//        //
//        msg = "  You sent: \0";
//        transmitSCIAMessage(msg);
//        transmitSCIAChar(ReceivedChar);

    }

}


