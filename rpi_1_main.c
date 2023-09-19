#inclue <pthread.h>

const int socketCANDescriptor;


int main()
{
        
        struct sockaddr_can addr;
        struct ifreq ifr;
       


        if ((socketCANDescriptor = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
                perror("Socket creation failed.");
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

        while(1)
        {
            //quit 인거 terminateRPC호출;
            
        }

        
        if (close(socketCANDescriptor) < 0) {
                perror("Close");
                return -1;
        }

    return 0;
}