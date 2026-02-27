#ifndef PERIPHERAL_ADC_H_
#define PERIPHERAL_ADC_H_

#include "f28x_project.h"


struct _ADC_IN{
    Uint16 Raw0;
    Uint16 Raw1;
    Uint16 Raw2;
    Uint16 Raw3;
    Uint16 Raw4;
    Uint16 Raw5;
    Uint16 Raw6;
    Uint16 Raw7;
    Uint16 Raw8;
    Uint16 Raw9;
    Uint16 Raw10;
    Uint16 Raw11;
    Uint16 Raw12;
    Uint16 Raw13;
    Uint16 Raw14;
    Uint16 Raw15;
};


extern struct _ADC_IN RAW_ADC;


void ADCInit(void);
void RAW_ADCGet(void);




#endif /* PERIPHERAL_ADC_H_ */
