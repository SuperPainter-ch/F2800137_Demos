/*
 * I2c.h
 *
 *  Created on: 2025年5月22日
 *      Author: Administrator
 */

#ifndef PERIPHERAL_I2C_H_
#define PERIPHERAL_I2C_H_

#include "f28x_project.h"


//
// I2C GPIO pins
//
#define GPIO_PIN_SDAA        21U  // GPIO number for I2C SDAA
#define GPIO_PIN_SCLA        20U  // GPIO number for I2C SCLA

#define IIC_RST_BIT 0X0020      //IIC 复位

// Status Flags
#define I2C_AL_BIT          0x0001
#define I2C_NACK_BIT        0x0002
#define I2C_ARDY_BIT        0x0004
#define I2C_RRDY_BIT        0x0008
#define I2C_SCD_BIT         0x0020

// I2C State defines
#define IIC_IDLE               0
#define IIC_WRITE              1
#define IIC_READ_STEP1         2
#define IIC_READ_STEP2         3
#define IIC_READ_STEP3         4
#define IIC_BUS_BUSY           5
#define IIC_BUS_ERROR          6

#define I2C_SLAVE_ADDRESS 0x6AU
#define I2C_OWN_ADDRESS 0x30U


// I2C Message Structure
typedef struct I2CSlaveMSG{
  Uint16 IntSRC[10];            //中断源            测试用
  Uint16 IntSRCCnt;             //中断源记录  测试用
  Uint16 MasterStatus;          //自行软件定义的IIC状态
  Uint16 SlavePHYAddress;       //IIC物理地址（硬件地址）
  Uint16 LogicAddr;             //类似于EEPROM，需要提供逻辑地址
  Uint16 Len;                   //操作数据的长度（不含物理地址）
  Uint16 MsgInBuffer[4]; //发送数组，最大4个深度
  Uint16 MsgOutBuffer[4];//接收数组，最大4个深度
  Uint16 IIC_TimerOUT;   //软件定义的超时变量，在1ms定时器中计数
}I2CSlaveMSG;


void I2cInit(void);
void I2CMaster_Init(void);

void I2CWrite(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition);
uint16_t I2CRead(uint16_t slaveAddr, uint16_t byteCount, bool sendStopCondition);

void I2CA_Tx_STOP(struct I2CSlaveMSG *msg);
Uint16 I2CA_Rxdata_STOP(struct I2CSlaveMSG *msg);
void I2CA_Txdata_NoSTOP(struct I2CSlaveMSG *msg);


#endif /* PERIPHERAL_I2C_H_ */
