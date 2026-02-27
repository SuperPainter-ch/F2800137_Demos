#include "Adc.h"


struct _ADC_IN RAW_ADC = {0};



/*****************************************************************************
 * 函    数: ADCInit(void)
 * 功    能:电压电流采样;
 * Parameters  : none
 * Returns     : none
*****************************************************************************/
void ADCInit(void)
{
    EALLOW;



    GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO242 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO226 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO228 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 1;
    GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 1;

    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO226 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO228 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;

    EDIS;

    //
    // Setup VREF as external
    //
    SetVREF(ADC_ADCA, ADC_EXTERNAL, ADC_VREF3P3);

    EALLOW;
    //
    // Set ADCCLK divider to /4
    //
    AdcaRegs.ADCCTL2.bit.PRESCALE = 6; //ADCCLK = SYSCLKOUT(30Mhz)
    //
    // Set pulse positions to late
    //
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Set pulse positions to late
    //
    // Power up the ADC and then delay for 1 ms
    //
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up the ADC and then delay for 1 ms

    EDIS;


    DELAY_US(1000);


    EALLOW;

    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 6;     // SOC0 will convert pin A6
//    AdcaRegs.ADCSOC1CTL.bit.CHSEL = 1;     // SOC1 will convert pin A1
//    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 2;     // SOC2 will convert pin A2
//    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 3;     // SOC3 will convert pin A3
//    AdcaRegs.ADCSOC4CTL.bit.CHSEL = 4;     // SOC4 will convert pin A4
//    AdcaRegs.ADCSOC5CTL.bit.CHSEL = 5;     // SOC5 will convert pin A5
//    AdcaRegs.ADCSOC6CTL.bit.CHSEL = 6;     // SOC6 will convert pin A6
//    AdcaRegs.ADCSOC7CTL.bit.CHSEL = 7;     // SOC7 will convert pin A7
//    AdcaRegs.ADCSOC8CTL.bit.CHSEL = 8;     // SOC8 will convert pin A8
//    AdcaRegs.ADCSOC9CTL.bit.CHSEL = 9;     // SOC9 will convert pin A9
//    AdcaRegs.ADCSOC10CTL.bit.CHSEL = 10;     // SOC10 will convert pin A10
//    AdcaRegs.ADCSOC11CTL.bit.CHSEL = 11;     // SOC11 will convert pin A11
//    AdcaRegs.ADCSOC12CTL.bit.CHSEL = 12;     // SOC12 will convert pin A12
//    AdcaRegs.ADCSOC13CTL.bit.CHSEL = 13;     // SOC13 will convert pin A13
//    AdcaRegs.ADCSOC14CTL.bit.CHSEL = 14;     // SOC14 will convert pin A14
//    AdcaRegs.ADCSOC15CTL.bit.CHSEL = 15;     // SOC15 will convert pin A15

    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC1CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC2CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC3CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC4CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC5CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC6CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC7CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC8CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC9CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC10CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC11CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC12CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC13CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC14CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles
//    AdcaRegs.ADCSOC15CTL.bit.ACQPS = 9;     // Sample window is 10 SYSCLK cycles

    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL = 9;   // Trigger on SoftWare || ePWM3 SOCA
//    AdcaRegs.ADCSOC1CTL.bit.TRIGSEL = 9;   // Trigger on ePWM3 SOCA
//    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL = 9;   // Trigger on ePWM3 SOCA
//    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL = 9;   // Trigger on ePWM3 SOCA
//    AdcaRegs.ADCSOC4CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC5CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC6CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC7CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC8CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC9CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC10CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC11CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC12CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC13CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC14CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA
//    AdcaRegs.ADCSOC15CTL.bit.TRIGSEL = 5;   // Trigger on ePWM1 SOCA



    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL = 0; // End of SOC0 will set INT1 flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E = 1;   // Enable INT1 flag
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; // Make sure INT1 flag is cleared

    EDIS;

    RAW_ADC.Raw0 = 0;
//    RAW_ADC.Raw1 = 0;
//    RAW_ADC.Raw2 = 0;
//    RAW_ADC.Raw3 = 0;
//    RAW_ADC.Raw4 = 0;
//    RAW_ADC.Raw5 = 0;
//    RAW_ADC.Raw6 = 0;
//    RAW_ADC.Raw7 = 0;
//    RAW_ADC.Raw8 = 0;
//    RAW_ADC.Raw9 = 0;
//    RAW_ADC.Raw10 = 0;
//    RAW_ADC.Raw11 = 0;
//    RAW_ADC.Raw12 = 0;
//    RAW_ADC.Raw13 = 0;
//    RAW_ADC.Raw14 = 0;
//    RAW_ADC.Raw15 = 0;
}

void RAW_ADCGet(void){
    RAW_ADC.Raw0 = AdcaResultRegs.ADCRESULT0;
//    RAW_ADC.Raw1 = AdcaResultRegs.ADCRESULT1;
//    RAW_ADC.Raw2 = AdcaResultRegs.ADCRESULT2;
//    RAW_ADC.Raw3 = AdcaResultRegs.ADCRESULT3;
//    RAW_ADC.Raw4 = AdcaResultRegs.ADCRESULT4;
//    RAW_ADC.Raw5 = AdcaResultRegs.ADCRESULT5;
//    RAW_ADC.Raw6 = AdcaResultRegs.ADCRESULT6;
//    RAW_ADC.Raw7 = AdcaResultRegs.ADCRESULT7;
//    RAW_ADC.Raw8 = AdcaResultRegs.ADCRESULT8;
//    RAW_ADC.Raw9 = AdcaResultRegs.ADCRESULT9;
//    RAW_ADC.Raw10 = AdcaResultRegs.ADCRESULT10;
//    RAW_ADC.Raw11 = AdcaResultRegs.ADCRESULT11;
//    RAW_ADC.Raw12 = AdcaResultRegs.ADCRESULT12;
//    RAW_ADC.Raw13 = AdcaResultRegs.ADCRESULT13;
//    RAW_ADC.Raw14 = AdcaResultRegs.ADCRESULT14;
//    RAW_ADC.Raw15 = AdcaResultRegs.ADCRESULT15;
}






