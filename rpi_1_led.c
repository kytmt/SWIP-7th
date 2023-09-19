#include <stdio.h>
#include <wiringPi.h>
#include <rpi_1_led.h>

void blinkLED(int mode) 
{
    wiringPiSetupGpio();

    pinMode(GPIO_LED, OUTPUT);

    while(1) {
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
            delay(1000);
            
            digitalWrite(GPIO_LED, LOW);
            delay(1000);
        }
    }
}