#include "rpi_1_stub.h"
#ifndef _CAN_H_
#define _CAN_H_

int can1_send(const char* cmd, DATA args);
int can1_recv();

extern struct sendData;
extern struct recvData;
extern struct Data;
#endif