/*
 * Epwm.h
 *
 *  Created on: 2025Äê5ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef PERIPHERAL_EPWM_H_
#define PERIPHERAL_EPWM_H_


#include "f28x_project.h"


#define PWM_PRD     5

#define HR_Disable 0x0
#define HR_REP 0x1 // Rising Edge position
#define HR_FEP 0x2 // Falling Edge position
#define HR_BEP 0x3 // Both Edge position #define HR_CMP 0x0 // CMPAHR controlled
#define HR_PHS 0x1 // TBPHSHR controlled #define HR_CTR_ZERO 0x0 // CTR = Zero event
#define HR_CTR_PRD 0x1 // CTR = Period event
#define HR_CTR_ZERO_PRD 0x2 // CTR = ZERO or Period event
#define HR_NORM_B 0x0 // Normal ePWMxB output
#define HR_INVERT_B 0x1 // ePWMxB is inverted ePWMxA output


void HrpwmInit(void);
void SetHrpwm(void);


#endif /* PERIPHERAL_EPWM_H_ */
