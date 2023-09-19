#include <string.h>

const int socketCANDescriptor;
int terminateRequirement = 0;

int main()
{
        char func[16];
        DATA args;
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

    // rpi1으로부터 켄 메시지 받고, 처리

    while(1)
    {

        Unmarshall(&func, &args);


        if(!strcmp(func, "moveMotor")) {
                moveMotor(args.i_data);
        } else if(!strcmp(func, "displayText")) {
                displayText(args.i_data, args.str_data);
        } else if(!strcmp(func, "terminateRPC")) {
                terminateRPC(args.str_data);
               
        } else{
                printf("Unmarshall error\n");
                continue;
        }


        if(terminateRequirement == 1){
                break;
        }
        
        
    }


    if (close(socketCANDescriptor) < 0) {
            perror("Close");
            return -1;
    }

}