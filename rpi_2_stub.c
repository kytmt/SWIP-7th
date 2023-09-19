#include "rpi_2_stub.h"

void Unmarshall(char** func, DATA* args)
{
    can2_recv();
    memcpy(func, buf, 16);
    memcpy( &(*args).i_data, buf+16, 4);
    memcpy( &(*args).str_data, buf+20,16);

}


int moveMotor(const int inputValue)
{
    int ret;
    struct Data data;

    //모터 호출

    return ret;
}

int displayText(const int lineNum, const char *text)
{

    //lcd 호출

}

int terminateRPC(const char* text)
{
    // 실행 종료 
}
