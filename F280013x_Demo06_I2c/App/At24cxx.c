/*
 * At24cxx.c
 *
 *  Created on: 2025年5月22日
 *      Author: Administrator
 */
#include "At24cxx.h"



I2CSlaveMSG AT24C02Msg; //EEPROM




//
//
// 初始化AT24C02
//
void EepromInit(void)
{
    //------------AT24C02地址设置----------------------------------------
    AT24C02Msg.SlavePHYAddress = 0x50; //设备地址，即为物理地址,7位地址  1010000b
    AT24C02Msg.MasterStatus = IIC_IDLE;

}


//读取EEPROM的数据放置在 数组 AT24C02Msg.MsgInBuffer[] 里
void EEPROM_Read(char addr,char len)
{
    I2caRegs.I2CSTR.bit.BYTESENT = 1;
    AT24C02Msg.Len  = 1;                  //1 个数据(不含物理地址)
    AT24C02Msg.MsgOutBuffer[0] = addr;    //1个数据为逻辑地址
    I2CA_Txdata_NoSTOP(&AT24C02Msg);      //发送数据，不带STOP

    while(I2caRegs.I2CSTR.bit.BB !=0x0);
    while(I2caRegs.I2CSTR.bit.BYTESENT ==0);

    if(len>4)len = 4;
    AT24C02Msg.Len  = len;              //n 个数据(不含物理地址)
    I2CA_Rxdata_STOP(&AT24C02Msg);      //带STOP
    while(I2caRegs.I2CSTR.bit.BB !=0x0);
}

//写EEPROM芯片
//addr为为EEPROM内部的逻辑地址，范围为 0 - 255，   data为写入一个字节数据
void EEPROM_Send(char addr,char data)
{
   // char i;
    AT24C02Msg.Len  = 2;                  //1 个数据 加 1个 逻辑地址
    AT24C02Msg.MsgOutBuffer[0] = addr;    //1个数据为逻辑地址
    AT24C02Msg.MsgOutBuffer[1] = data;    //1个数据
    I2CA_Tx_STOP(&AT24C02Msg);            //发送数据，带STOP
    while(I2caRegs.I2CSTR.bit.BB !=0x0);
    //--------------注意，写入每个字节时，需要间隔5us后再写入下一个字节
    DELAY_US(5000);
}
