/*
 * Spi.h
 *
 *  Created on: 2025Äê3ÔÂ6ÈÕ
 *      Author: Administrator
 */

#ifndef PERIPHERAL_DAC8552_H_
#define PERIPHERAL_DAC8552_H_


#include "f28x_project.h"
#include "Gpio.h"


void DAC8552_Set_Channel_A(long Data);
void DAC8552_Set_Channel_B(long Data);
void Dac8552Init(void);



#endif /* PERIPHERAL_DAC8552_H_ */
