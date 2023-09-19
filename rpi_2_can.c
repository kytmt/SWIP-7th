#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rpi_2_can.h"

int can2_send()
{

        // 1
        struct can_frame frame;
        struct sendData sdata;

        int index = 0;
        int packetTotal;
        int lastPacketSize;

        //frame 설정
        frame.can_id = 0x556;
        frame.can_dlc = 8;

        //데이터 입력
        sdata.data = args;
        sdata.func_len = strlen(cmd);
        strcpy(sdata.func, cmd);

        //기본값 설정
        packetTotal = sizeof(data) / 8 + 1;
        lastPacketSize = sizeof(data) % 8;


        //로직
        while(packetTotal != 0)
        {
                if(packetTotal == 1)
                        frame.can_dlc = lastPacketSize;

                // frame 내용 수정
                memcpy(frame.data, (char *) (sendData + index * 8),  frame.can_dlc);

                if (write(socketCANDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                        perror("Write failed");
                        return -1;
                }

                index++;
                packetTotal--;
        }

        return sizeof(sdata);
}

int can2_recv()
{

        struct can_frame frame;
        struct recvData data;

        // rpi#2가 리턴해주는 값을 받는 것.
        int nbytesReceived;

        // 1. func_len 수신

        int cnt = 5; // 36 바이트 수신
        int offset = 0;
        
        for(int i = 0 ; i < cnt; i++)
        {

            nbytesReceived = read(socketCANDescriptor, &frame, sizeof(struct can_frame));
            if (nbytesReceived < 0) {
                perror("Read failed");
                return -1;
            }    
            memcpy(buf + offset, (unsigned char *)(frame.data), frame.can_dlc);
            offset += frame.can_dlc;

        }

        return 0;
}


/*
struct recvData{
        int func_len; // 4 + 4
        char *func; // 8
        DATA data;  // 20
}

struct sendData{
        int ret;
}

typedef struct Data
{
        int i_len;
        int i_data;
        int str_len;
        char* str_data;

}DATA;

*/