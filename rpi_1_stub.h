#ifndef _STUB_H_
#define _STUB_H_

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "rpi_1_can.h"

struct sendData{
        int func_len; // 4 + 4
        char *func; // 8
        DATA data;  // 20
}

struct recvData{
        int ret;
}

typedef struct Data
{
        int i_len;
        int i_data;
        int str_len;
        char* str_data;

}DATA;
#endif