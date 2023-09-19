#include "rpi_1_led.h"
#include <wiringPi.h>
#include <stdio.h>

void* blinkLED(void *mode) 
{
    
    int md = *(int*)mode;
 
    pinMode(GPIO_LED, OUTPUT);

    while (1)
    {
        md = *(int*)mode;
        
        if( md == BLINK_10Hz)
        {
            digitalWrite(GPIO_LED, HIGH);
            delay(100);
            
            digitalWrite(GPIO_LED, LOW);
            delay(100);
        } else {
            digitalWrite(GPIO_LED, HIGH);
            delay(1000);
            
            digitalWrite(GPIO_LED, LOW);
            delay(1000);
        }

    }
}