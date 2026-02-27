/*
 * I2c.c
 *
 *  Created on: 2025年5月22日
 *      Author: Administrator
 */
#include "I2c.h"


uint16_t I2C_TXdata[16];
uint16_t I2C_RXdata[16];
char I2C_NUMBYTES  =0; // 0x2U



//
// 初始化DSP的 IIC接口 芯片
//
void I2cInit(void)
{
    //
    //Configure I2C pins
    //
    GPIO_SetupPinMux(GPIO_PIN_SDAA, GPIO_MUX_CPU1, 11);
    GPIO_SetupPinOptions(GPIO_PIN_SDAA, GPIO_OUTPUT, GPIO_PULLUP);
    GPIO_SetupPinMux(GPIO_PIN_SCLA, GPIO_MUX_CPU1, 11);
    GPIO_SetupPinOptions(GPIO_PIN_SCLA, GPIO_OUTPUT, GPIO_PULLUP);

    I2CMaster_Init();  //主机模式，100KHz SCL频率
    DELAY_US(5000);
}




//IIC底层发送函数
//IIC Maste Mode，发送模式
//I2caRegs.I2CCNT 为发送的字节长度，不包括从器件的物理地址
//发送格式：START, ADDRESS, CONTROL_BYTE ,DA_BYTE ,STOP
//STOP信号结束
void I2CA_Tx_STOP(struct I2CSlaveMSG *msg)
{
    Uint16 i;

    I2caRegs.I2CSAR.all = msg->SlavePHYAddress;//设置访问从器件地址，物理地址

    I2caRegs.I2CMDR.bit.MST = 1; //主机
    I2caRegs.I2CMDR.bit.TRX = 1; //发送模式

    I2caRegs.I2CCNT = msg->Len; //设置发送长度

 //   I2caRegs.I2CDXR.all =  msg->MsgOutBuffer[0];

    I2caRegs.I2CMDR.bit.STT = 1; // send Start condition

    for(i=0;i<msg->Len;i++)
    {
        I2caRegs.I2CDXR.all =  msg->MsgOutBuffer[i];

        while(I2caRegs.I2CSTR.bit.BYTESENT != 1);//wait till byte is sent

        I2caRegs.I2CSTR.bit.BYTESENT = 1;       //clear the byte sent

      //  DELAY_US(5000);
    }

    // Send STOP condition if specified
    I2caRegs.I2CMDR.bit.STP = 0x1;
    while(I2caRegs.I2CMDR.bit.STP != 0x0);
    I2caRegs.I2CSTR.bit.BYTESENT = 0x1;
}


//IIC底层接收函数
//先发送从器件的物理地址，再接收 I2CCNT 个字节
//IIC Maste Mode，接收模式
//I2caRegs.I2CCNT 为发送的字节长度，不包括从器件的物理地址，
//格式(接收4个字节为例)：START ADDRESS DATA_BYTE1 DATA_BYTE2 DATA_BYTE3 DATA_BYTE4  STOP //DATA为读取的数据
//当写入I2caRegs.I2CMDR.all = 0x2C20，硬件IIC进行操作，硬件STOP发送后，接收的数据在FIFO中
Uint16 I2CA_Rxdata_STOP(struct I2CSlaveMSG *msg)
{
    Uint16 i = 0;
    I2caRegs.I2CSAR.all = msg->SlavePHYAddress;//设置访问从器件地址，物理地址
    I2caRegs.I2CCNT = msg->Len; //设置发送长度
    I2caRegs.I2CMDR.bit.MST = 0x1; //主机
    I2caRegs.I2CMDR.bit.TRX = 0x0; //接收模式
    I2caRegs.I2CMDR.bit.STT = 0x1;  // send Start condition

    // Read the received data into RX buffer
    while(i < msg->Len)
    {
        if(I2caRegs.I2CSTR.bit.RRDY ==0x1)
        {
            msg->MsgInBuffer[i] = I2caRegs.I2CDRR.all;
            i++;
        }
    }

    // Send STOP condition
    I2caRegs.I2CMDR.bit.STP = 0x1;
    while(I2caRegs.I2CMDR.bit.STP != 0x0);
    I2caRegs.I2CSTR.bit.BYTESENT = 0x1;

    return i;
}


/************************************************************************/
//IIC发送函数，不带停止位
//IIC Maste Mode，发送模式,主机，发送从器件地址，无STOP
/************************************************************************/
void I2CA_Txdata_NoSTOP(struct I2CSlaveMSG *msg)
{
    I2caRegs.I2CSAR.all = msg->SlavePHYAddress;//设置访问从器件地址，物理地址
    I2caRegs.I2CCNT = msg->Len; //设置发送长度
    I2caRegs.I2CDXR.all = msg->MsgOutBuffer[0] ; //发送的数据，EEPROM的逻辑地址

    I2caRegs.I2CMDR.bit.MST = 0x1; //主机
    I2caRegs.I2CMDR.bit.TRX = 0x1; //发送模式
    I2caRegs.I2CMDR.bit.STT = 0x1; // send Start condition
    //TRX = 1 发送模式,STP = 0，不发送STOP
}



//
// IIC初始化，100KHz
//
void I2CMaster_Init(void)
{
    EALLOW;
    //
    // Must put I2C into reset before configuring it
    //
    I2caRegs.I2CMDR.all &= ~(0x20U);


    //
    // I2C configuration. Use a 400kHz I2CCLK with a 50% duty cycle.
    //
    //I2C_initMaster(base, DEVICE_SYSCLK_FREQ, 400000, I2C_DUTYCYCLE_50);
    I2caRegs.I2CPSC.all = 9;        // Prescaler - need 7-12 Mhz on module clk， 这里设置10MHz，  I2C Module Clock

    //当I2CCLKL = 7， I2CCLKH = 8
    //SCL频率1： I2C Module Clock /( (ICCL + 5) + (ICCH + 5)) = 10MHz / 25 =  400KHz

    //当I2CCLKL = 45， I2CCLKH = 45
    //SCL频率2： I2C Module Clock /( (ICCL + 5) + (ICCH + 5)) = 10MHz / 100 =  100KHz

    I2caRegs.I2CCLKL = 45;          // NOTE: must be non zero
    I2caRegs.I2CCLKH = 45;           // NOTE: must be non zero

    //
    // Configure Master as a Transmitter
    //
    I2caRegs.I2CMDR.bit.MST = 0x1;   //作为主机


    //
    // Set the bit count to 8 bits per data byte
    //
    I2caRegs.I2CMDR.bit.BC = 0x0U;

    //
    // Set emulation mode to FREE
    //
    I2caRegs.I2CMDR.bit.FREE = 0x1;

    //
    //Clear all status
    //
    I2caRegs.I2CSTR.all = 0xFFFF;

    //
    // Enable I2C Interrupts- RRDY
    //
    I2caRegs.I2CIER.all = 0x08;

    //
    // Take I2C out of reset
    //
    I2caRegs.I2CMDR.all |= 0x0020;
}

//
// Function to send data over I2C.
//
void I2CWrite(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition)
{

    //
    // Locals
    //
    uint16_t index = 0;

    //
    // Configure slave address
    //
    I2caRegs.I2CSAR.all = slaveAddr;      // Slave address

    //
    // Configure I2C as Master Transmitter
    //
    I2caRegs.I2CMDR.bit.MST = 0x1;
    I2caRegs.I2CMDR.bit.TRX = 0x1;

    //
    //Set Data Count
    //
    I2caRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2caRegs.I2CMDR.bit.STT = 0x1;

    //
    //transmit the bytes
    //
    for(index=0; index < I2C_NUMBYTES; index++)
    {
        I2caRegs.I2CDXR.all= I2C_TXdata[index];
        //
        //wait till byte is sent
        //
        while(I2caRegs.I2CSTR.bit.BYTESENT != 0x1);
        //
        //clear the byte sent
        //
        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;
    }

    //
    // Send STOP condition if specified
    //
    if(sendStopCondition)
    {
        I2caRegs.I2CMDR.bit.STP = 0x1;
        while(I2caRegs.I2CMDR.bit.STP != 0x0);

        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;
    }
}

//
// Function to read data over I2C. Returns the number of bytes read
//
uint16_t I2CRead(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition)
{
    //
    // Configure slave address
    //
    I2caRegs.I2CSAR.all = slaveAddr;

    //
    // Configure I2C in Master Receiver mode
    //
    I2caRegs.I2CMDR.bit.MST = 0x1;
    I2caRegs.I2CMDR.bit.TRX = 0x0;

    //
    //Set Data Count
    //
    //I2caRegs.I2CCNT = byteCount;

    //
    // send Start condition
    //
    I2caRegs.I2CMDR.bit.STT = 0x1;

    uint16_t count = 0;

    //
    // Read the received data into RX buffer
    //
    while(count < I2C_NUMBYTES)
    {
        if(I2caRegs.I2CSTR.bit.RRDY ==0x1)
        {
            I2C_RXdata[count] = I2caRegs.I2CDRR.all;
            count++;
        }
    }

    //
    // Send STOP condition
    //
    if(sendStopCondition)
    {
        I2caRegs.I2CMDR.bit.STP = 0x1;
        while(I2caRegs.I2CMDR.bit.STP != 0x0);

        I2caRegs.I2CSTR.bit.BYTESENT = 0x1;

    }
    return count;
}

