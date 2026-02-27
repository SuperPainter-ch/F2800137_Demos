/*
 * Sci.c
 *
 *  Created on: 2025年5月2日
 *      Author: Painter
 */
#include "Sci.h"


void SciaInit(void){
    GPIO_SetupPinMux(28, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(28, GPIO_INPUT, GPIO_PUSHPULL);
    GPIO_SetupPinMux(29, GPIO_MUX_CPU1, 1);
    GPIO_SetupPinOptions(29, GPIO_OUTPUT, GPIO_ASYNC);

    initSCIAFIFO();                         // Initialize the SCI FIFO
    initSCIAEchoback();                     // Initialize SCI for echoback
////    open_uart_debug(); //printf 函数连接，固定用法，将底层发送函数放置于 my_write 函数内即可； 串口助手采用  ASCII 格式显示






    transmitSCIAChar('a');
    unsigned char *msg;
    msg = "\r\n\n\nHello World!\0";
    transmitSCIAMessage(msg);

}


void initSCIAEchoback(void)
{
    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function
    //
    SciaRegs.SCICCR.all = 0x0007;           // 1 stop bit,  No loopback
                                            // No parity, 8 char bits,
                                            // async mode, idle-line protocol
    SciaRegs.SCICTL1.all = 0x0043;          // enable TX, RX, internal SCICLK,
                                            //使能错误接收
                                            // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCICTL2.bit.TXINTENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;



    //
    // SCIA at 115200 baud
    // @LSPCLK = 30 MHz (120 MHz SYSCLK) HBAUD = 0x00  and LBAUD = 0x20(115200)
    //                                 ||HBAUD = 0x00  and LBAUD = 0x00C3(19200)
    //                                 ||HBAUD = 0x01  and LBAUD = 0x0186(9600)
    // SCIHBAUD = (LSPCLK / (BaudRate * 8)) - 1 >> 8
    // SCILBAUD = (LSPCLK / (BaudRate * 8)) - 1 & 0xFF
    SciaRegs.SCIHBAUD.all = 0x0000;
    SciaRegs.SCILBAUD.all = 0x0020;

    SciaRegs.SCICTL1.all = 0x0023;          // Relinquish SCI from Reset
}

//
// transmitSCIAChar - Transmit a character from the SCI
//
void transmitSCIAChar(uint16_t a)
{
    while (SciaRegs.SCIFFTX.bit.TXFFST != 0)
    {

    }
    SciaRegs.SCITXBUF.all = a;
}

//
// transmitSCIAMessage - Transmit message via SCIA
//
void transmitSCIAMessage(unsigned char * msg)
{
    int i;
    i = 0;
    while(msg[i] != '\0')
    {
        transmitSCIAChar(msg[i]);
        i++;
    }
}

//
// initSCIAFIFO - Initialize the SCI FIFO
//
void initSCIAFIFO(void)
{
    SciaRegs.SCIFFTX.all = 0xE040; // 1110 0000 0100 0000

    SciaRegs.SCIFFRX.all = 0x2061;  // 0010 0000 0110 0001

    SciaRegs.SCIFFCT.all = 0x0;

}
