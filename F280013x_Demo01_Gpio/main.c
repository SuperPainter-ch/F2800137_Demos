#include "f28x_project.h"

#include "Gpio.h"



/**
 * main.c
 */
int main(void)
{
    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize Peripheral
    //
    InitGpio();
    GpioInit();




    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    InitPieVectTable();

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    //
    // Loop Forever
    //
    for(;;)
    {
        GpioDataRegs.GPBCLEAR.bit.GPIO32 = 1;
        DELAY_US(100000);
        GpioDataRegs.GPBSET.bit.GPIO32 = 1;
        DELAY_US(100000);


    }

}
