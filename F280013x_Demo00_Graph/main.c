#include "f28x_project.h"



int i = 0;
int ScopeBuf[100] = {0};
int ScopeCnt = 0;




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

        ScopeBuf[ScopeCnt] = i;
        i += 2;
        ScopeCnt++;

        if(i == 200){
            i = 0;
        }
        if(ScopeCnt == 100){
            ScopeCnt = 0;
        }

        DELAY_US(10000);
    }

}
