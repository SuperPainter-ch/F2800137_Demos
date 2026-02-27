/*
 * Sci.h
 *
 *  Created on: 2025Äê5ÔÂ2ÈÕ
 *      Author: Painter
 */

#ifndef PERIPHERAL_SCI_H_
#define PERIPHERAL_SCI_H_

#include "f28x_project.h"


void SciaInit(void);
void initSCIAEchoback(void);
void transmitSCIAChar(uint16_t a);
void transmitSCIAMessage(unsigned char * msg);
void initSCIAFIFO(void);

#endif /* PERIPHERAL_SCI_H_ */
