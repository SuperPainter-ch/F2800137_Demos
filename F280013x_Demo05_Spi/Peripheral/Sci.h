/*
 * Sci.h
 *
 *  Created on: 2025Äê5ÔÂ2ÈÕ
 *      Author: Painter
 */

#ifndef PERIPHERAL_SCI_H_
#define PERIPHERAL_SCI_H_

#include "f28x_project.h"
#include <stdio.h>
#include <file.h>


void SciaInit(void);
void initSCIAEchoback(void);
void transmitSCIAChar(uint16_t a);
void transmitSCIAMessage(unsigned char * msg);
void initSCIAFIFO(void);



void open_uart_debug (void);
int my_open(const char *path, unsigned flags, int fno);
int my_close(int fno);
int my_read(int fno, char *buffer, unsigned count);
int my_write(int fno, const char *buffer, unsigned count);
off_t my_lseek(int fno, off_t offset, int origin);
int my_unlink(const char *path);
int my_rename(const char *old_name, const char *new_name);


#endif /* PERIPHERAL_SCI_H_ */
