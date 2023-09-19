#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rpi_1_can.h"

#define PACKET_SIZE 36

int can1_send(const char* cmd,  DATA args)
{

        // 1
        struct can_frame frame;
        struct sendData sdata;

        int index = 0;
        int packetTotal;
        int lastPacketSize;

        //frame 설정
        frame.can_id = 0x555;
        frame.can_dlc = 8;

        //데이터 입력
        sdata.data = args;
        sdata.func_len = strlen(cmd);
        strcpy(sdata.func, cmd);

        //기본값 설정
        packetTotal = PACKET_SIZE / 8 + 1;
        lastPacketSize = PACKET_SIZE % 8;


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

int can1_recv()
{
        struct can_frame frame;
        struct recvData data;

        // rpi#2가 리턴해주는 값을 받는 것.
        int nbytesReceived;

        nbytesReceived = read(socketCANDescriptor, &frame, sizeof(struct can_frame));
        if (nbytesReceived < 0) {
                perror("Read failed");
                return -1;
        }

        memcpy(data, (unsigned char *)(frame.data), frame.can_dlc);

        return data.ret;
}