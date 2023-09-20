#include "rpi_1_stub.h"
#ifndef _CAN_H_
#define _CAN_H_


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

//extern struct initData;

int can1_send(const char* cmd, DATA args);
int can1_recv();
int socketInit();
int socketClose();

#endif