#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include "rpi_1_stub.h"
#include "rpi_1_can.h"
#include "rpi_1_led.h"





int main()
{
        
        printf("start\n");

        socketInit();

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
        socketClose();
        


    return 0;
}