#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "rpi_1_can.h"

#define PACKET_SIZE 36

int socketCANDescriptor;

int socketInit()
{
        struct sockaddr_can addr;
        struct ifreq ifr;

        if ((socketCANDescriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
                printf("Socket creation failed.");
                return -1;
        }


        strcpy(ifr.ifr_name, "can0" );
        ioctl(socketCANDescriptor, SIOCGIFINDEX, &ifr);
        memset(&addr, 0, sizeof(addr));

        addr.can_family = AF_CAN;        
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(socketCANDescriptor, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("Bind failed");
                return -1;
        }

        return 0; 

}

int socketClose()
{
        if (close(socketCANDescriptor) < 0) {
                perror("Close");
                return -1;
        }
        return 0;
}


int can1_send(const char* cmd,  DATA args)
{

        // 1
        struct can_frame frame;
        struct sendData sdata;

        int index = 0;
        int packetTotal;
        int lastPacketSize;


        struct sockaddr_can addr;
        struct ifreq ifr;
       


        if ((socketCANDescriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
                printf("Socket creation failed.");
                return -1;
        }


        strcpy(ifr.ifr_name, "can0" );
        ioctl(socketCANDescriptor, SIOCGIFINDEX, &ifr);
        memset(&addr, 0, sizeof(addr));
        
        addr.can_family = AF_CAN;        
        addr.can_ifindex = ifr.ifr_ifindex;

        if (bind(socketCANDescriptor, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("Bind failed");
                return -1;
        } 

        //frame 설정
        frame.can_id = 0x555;
        frame.can_dlc = 8;

        //데이터 입력
        sdata.data = args;
        //sdata.func_len = strlen(cmd);
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
                memcpy(frame.data, (char *) (&sdata + index * 8),  frame.can_dlc);

                if (write(socketCANDescriptor, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
                        perror("Write failed");
                        return -1;
                }

                index++;
                packetTotal--;
        }

        if (close(socketCANDescriptor) < 0) {
        perror("Close");
        return -1;
        }

        return sizeof(sdata);
}

int can1_recv()
{
        struct can_frame frame;
        struct recvData rdata;
        char receiveMessage[8];

        // rpi#2가 리턴해주는 값을 받는 것.
        int nbytesReceived;

        nbytesReceived = read(socketCANDescriptor, &frame, sizeof(struct can_frame));
        if (nbytesReceived < 0) {
                perror("Read failed");
                return -1;
        }

        memcpy(receiveMessage, (unsigned char *)(frame.data), frame.can_dlc);

        rdata.ret = (int)receiveMessage[0];

        return rdata.ret;
}