#include "rpi_1_led.h"

void blinkLED(int mode) 
{
    wiringPiSetupGpio();

    pinMode(GPIO_LED, OUTPUT);


    if (mode == BLINK_1s)
    {
        digitalWrite(GPIO_LED, HIGH);
        delay(1000);
        
        digitalWrite(GPIO_LED, LOW);
        delay(1000);
    }

    else if (mode = BLINK_10Hz)
    {
        digitalWrite(GPIO_LED, HIGH);
        delay(100);
        
        digitalWrite(GPIO_LED, LOW);
        delay(100);
    }
}