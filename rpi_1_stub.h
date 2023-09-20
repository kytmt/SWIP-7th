#ifndef _STUB_H_
#define _STUB_H_

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "rpi_1_can.h"

int moveMotor(const int inputValue);
int displayText(const int lineNum, const char *text);
int terminateRPC(const char* text);


#endif