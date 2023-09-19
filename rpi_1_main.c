#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "rpi_1_stub.h"
#include "rpi_1_can.h"
#include "rpi_1_led.h"


int socketCANDescriptor;


int main()
{
        
        printf("start\n");

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

        delay(1000);
        while(1)
        {
                
                printf("working\n");

                moveMotor(180);
                delay(2000);

                displayText(1, "Hello world!");
                delay(2000);


                terminateRPC("quit");
                delay(2000);


                //quit 인거 terminateRPC호출;
            
                delay(2000);
        }

        
        if (close(socketCANDescriptor) < 0) {
                perror("Close");
                return -1;
        }

    return 0;
}