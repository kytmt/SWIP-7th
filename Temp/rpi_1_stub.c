#include "rpi_1_stub.h"
#include <stddef.h>
#include <string.h>

int moveMotor(const int inputValue)
{
    int ret;
    struct Data data;


    data.i_data = inputValue;

    strcpy(data.str_data,NULL);

    if(can1_send("moveMotor", data) < 0) {
        perror("can1_send error");
        return -1;
    }

    ret = can1_recv();
    if(ret < 0) {
        perror("can1_recv error");
        return -1;
    }

    return ret;
}

int displayText(const int lineNum, const char *text)
{
    int ret;
    struct Data data;


    data.i_data = lineNum;

    strcpy(data.str_data, text);

    if(can1_send("displayText", data) < 0) {
        perror("can1_send error");
        return -1;
    }

    ret = can1_recv();
    if(ret < 0) {
        perror("can1_recv error");
        return -1;
    }

    return ret;
}

int terminateRPC(const char* text)
{
    int ret;
    struct Data data;


    data.i_data = 0;

    strcpy(data.str_data, text);

    if(can1_send("terminateRPC", data) < 0) {
        perror("can1_send error");
        return -1;
    }

    ret = can1_recv();
    if(ret < 0) {
        perror("can1_recv error");
        return -1;
    }

    return ret;
}
