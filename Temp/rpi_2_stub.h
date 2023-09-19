#ifndef _STUB_H_
#define _STUB_H_

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

#include "rpi_2_can.h"

#define BUF_SIZE 256
char buf[BUF_SIZE];



typedef struct Data
{
        int i_data;
        char str_data[16];

}DATA;

struct sendData{
        char func[16]; // 8
        DATA data;  // 20
};

struct recvData{
        int ret;
};
#endif