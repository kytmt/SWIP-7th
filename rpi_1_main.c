#include <stdio.h>
#include <pthread.h>
#include "rpi_1_led.h"
#include "rpi_1_ultrasonic.h"
#include "wiringPi.h"
#include "rpi_1_dijkstra.h"


int isInTwenty;

int main(void)
{
    char temp[1024]; // 문자열 저장 배열
    int src = 3; // 시작 노드
    int dest = 6; // 도착 노드

    pthread_t thread_1, thread_2;

    wiringPiSetupGpio();
    
    pthread_create(&thread_2, NULL, blinkLED, &isInTwenty);
    pthread_create(&thread_1, NULL, R1_ultrasonic, 0);
    findShortestPath(src, dest, temp, &len);

    printf("%s", temp);
    while(1){
        
    }

}