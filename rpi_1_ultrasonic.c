#include "rpi_1_ultrasonic.h"
#include <wiringPi.h>

float measureDistance(void) 
{   
    struct timeval tv1;
    struct timeval tv2;

    long time1, time2;
    float distance;

    // To make a clean start, we may need to pull down the sensor to LOW
    //digitalWrite(Trig, LOW);    
    //delayMicroseconds(2);

    // Generate a 10us-long pulse 
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);

    // Wait unitl the sensor's echo pin becomes HIGH,
    // and then measure time1
    while(digitalRead(Echo) == LOW)
        ;
    gettimeofday(&tv1, NULL);

    // Wait unitl the sensor's echo pin becomes LOW,
    // and then measure time2
    while(digitalRead(Echo) == HIGH)
        ;
    gettimeofday(&tv2, NULL);

    // Calculate the distance (in cm) from the measured time values 
    time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;
    time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;
    distance = (float)(time2 - time1) / 1000000 * 34000 / 2;

    return distance;
}


void* R1_ultrasonic() 
{	
    float distance;
    
    pinMode(Echo, INPUT);
    pinMode(Trig, OUTPUT);

    while(1)
    {
        distance = measureDistance();
        //printf("%0.2f cm\n", distance);
        
        if (distance < 20.0)
            isInTwenty = 1;
        else
            isInTwenty = 0;
        delay(10);
    }
}
