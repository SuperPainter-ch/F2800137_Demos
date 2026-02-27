/*
 * At24c0x.h
 *
 *  Created on: 2025年5月22日
 *      Author: Administrator
 */

#ifndef APP_AT24CXX_H_
#define APP_AT24CXX_H_


#include "f28x_project.h"
#include "I2c.h"


#define EE_PAGE_SIZE   8 //AT24C02 每页8个字节
#define EE_PAGE_NUM    32//AT24C02 一共有32页
#define EE_MEM_BYTE    256//总的容量，单位byte
#define EE_COMM_ID     0xA2 //宏定义EEPROM串口操作的地址

#define AT24Cxx_TIMER_OUT 3 //ms为单位


void EepromInit(void);
void EEPROM_Read(char addr,char len);
void EEPROM_Send(char addr,char data);


#endif /* APP_AT24CXX_H_ */
