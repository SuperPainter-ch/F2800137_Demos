#include "f28x_project.h"

#include "Gpio.h"
#include "Timer.h"
#include "Sci.h"
#include "Epwm.h"
#include "sfo_v8.h"



#include "Timer0_ISR.h"
#include "Timer1_ISR.h"
#include "Timer2_ISR.h"


//定义printf输出测试变量
char  test_hex = 0x55;//定义一个 十六进制数
Uint16 test_dec = 1005;//定义一个十进制数
long  test_long = 0x12345678;//定义一个long型
float  test_float = 99.6;//定义一个浮点数
char *test_str={"S100"}; //定义字符串


Uint16 status = SFO_INCOMPLETE;
int MEP_ScaleFactor = 0; //scale factor value
volatile struct EPWM_REGS *ePWM[] = {0, &EPwm1Regs, &EPwm2Regs};


extern Uint16 hrcmpa;
extern Uint16 hrcmpb;

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
    HrpwmInit();

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



//     Enable Global Interrupt (INTM) and realtime interrupt (DBGM)

    EINT;
    ERTM;


    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of MEP
            // steps/coarse step exceeds maximum of 255.
            //
            ESTOP0;
        }
    }
//    MEP_ScaleFactor = 66*256;
    //
    // Loop Forever
    //
    for(;;)
    {

        int status;
        // User code
        // ePWM1, 2, 3, 4 are running in HRPWM mode
        // The status variable returns 1 once a new MEP_ScaleFactor has been
        // calculated by the MEP Calibration Module running SFO
        // diagnostics.

        status = SFO_INCOMPLETE;
        while(status == SFO_INCOMPLETE){
            status = SFO();
        }
        if(status == SFO_ERROR)
        {
            //
            // SFO function returns 2 if an error occurs & # of
            // M    EP steps/coarse step exceeds maximum of 255.
            //
            ESTOP0;
        }


        DELAY_US(100000);
        SetHrpwm();


    }

}


