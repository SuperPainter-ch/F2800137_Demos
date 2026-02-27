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
    open_uart_debug(); //printf 函数连接，固定用法，将底层发送函数放置于 my_write 函数内即可； 串口助手采用  ASCII 格式显示





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
    SciaRegs.SCICTL1.all = 0x0003;          // enable TX, RX, internal SCICLK,
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
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x2044;
    SciaRegs.SCIFFCT.all = 0x0;
}





//-------------------------------以下都为 标准 printf函数连接--------------------------------------------------------------
//#################################################
//-----------------------------------------------
//printf 函数连接
//定义printf输出测试变量
//char  test_hex = 0x55;//定义一个 十六进制数
//Uint16 test_dec = 1005;//定义一个十进制数
//long  test_long = 0x12345678;//定义一个long型
//float  test_float = 99.06;//定义一个浮点数
//char *test_str={"S100"}; //定义字符串
//
//printf("\r\n DSP is Ready!");//采用标准C语言printf函数  发送字符串测试
//printf("\r\nprintf测试输出十六进制 0x%x",test_hex);  //发送十六进制测试
//printf("\r\nprintf测试输出long型的十六进制 0x%lx",test_long);//发送超过16bit长度的long型数据， 格式为  %lx
//printf("\r\nprintf测试输出十进制 %d",test_dec);//测试发送十进制
//printf("\r\nprintf测试输出浮点数 %0.2f",test_float); //输出2位小数点
//-----------------------------------------------
void open_uart_debug (void)
{
    int status=0;
    status = add_device("uart", _MSA, my_open, my_close, my_read, my_write, my_lseek, my_unlink, my_rename);
    if (status == 0) {
        freopen("uart:", "w", stdout);      // open uart and redirect stdout to UART
        setvbuf(stdout, NULL, _IONBF, 0);   // disable buffering for stdout
    }
}

int my_open(const char *path, unsigned flags, int fno)
{
    //scia_fifo_init();
    //scia_echoback_init();
    path = path;
    flags = flags;
    fno = fno;
    return 0;
}

int my_close(int fno)
{
    fno =fno;
    return 0;
}

int my_read(int fno, char *buffer, unsigned count)
{
    fno = fno;
    buffer = buffer;
    count = count;
    return 0;
}

int my_write(int fno, const char *buffer, unsigned count)
{
    int i=0;
    fno = fno;

    while(count-- > 0) {
        transmitSCIAChar(buffer[i++]);
    }
    return count;
}

off_t my_lseek(int fno, off_t offset, int origin)
{
    fno = fno; offset = offset; origin = origin;
    return 0;
}

int my_unlink(const char *path)
{
    path = path;
    return 0;
}

int my_rename(const char *old_name, const char *new_name)
{
    old_name = old_name;
    new_name = new_name;
    return 0;
}
