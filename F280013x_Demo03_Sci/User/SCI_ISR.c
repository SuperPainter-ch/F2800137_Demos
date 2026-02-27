/*
 * SCI_ISR.c
 *
 *  Created on: 2025年8月9日
 *      Author: Painter
 */

#include "SCI_ISR.h"


//#################################################
//串口接收中断函数
//采用FIFO机制（缓存）
//SCI_FIFO_LEN 定义为 1，最大为4
//-----------------------------------------------
interrupt void SCIA_Rx_isr(void){
    Uint16 revData;

    SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;      // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

    if(SciaRegs.SCIFFRX.bit.RXFFOVF == 0)//接收FIFO未溢出
    {
        //接收串口数据
        while(SciaRegs.SCIFFRX.bit.RXFFST)
        {
            revData = SciaRegs.SCIRXBUF.all;//从接收寄存器中取出数据

            transmitSCIAChar(revData);
            ;
        }
    }
    else
    {
        //用户这里做串口硬件溢出的处理,可以完全读取出FIFO里的数据或者清空FIFO
        //这里清空FIFO操作
        SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear HW Overflow flag
        SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;  //Write 0 to reset the FIFO pointer to zero, and hold in reset.
        SciaRegs.SCIFFRX.bit.RXFIFORESET = 1 ; //Re-enable receive FIFO operation
    }
}
