/*
 * Spi.c
 *
 *  Created on: 2025Äê3ÔÂ6ÈÕ
 *      Author: Administrator
 */


#include "Dac8552.h"




void DAC8552_Set_Channel_A(long Data){
        SpiaRegs.SPITXBUF = 0X0010<<8;
        SpiaRegs.SPITXBUF = Data;
        SpiaRegs.SPITXBUF = Data<<8;
}

void DAC8552_Set_Channel_B(long Data){
        SpiaRegs.SPITXBUF = 0x24<<8;
        SpiaRegs.SPITXBUF = Data;
        SpiaRegs.SPITXBUF = Data<<8;
}

void Dac8552Init(void){
    DELAY_US(1000);
    DAC8552_Set_Channel_A(0);
    DELAY_US(1000);
    DAC8552_Set_Channel_B(0);
    DELAY_US(1000);
}

