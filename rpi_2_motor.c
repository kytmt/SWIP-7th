#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#include "rpi_2_motor.h"


int moveMotor(int inputValue)
{
    float dutyCycle;        // the unit is %
    int pulseWidth;

    if(inputValue < 0){
        printf("The inputValue is smaller than 0")
        return -1;
    }
    wiringPiSetupGpio();
    pinMode(PIN, OUTPUT);

    // Set PWM range (= the total number of clock ticks during a period)
    softPwmCreate(PIN, 0, PWM_RANGE);

    dutyCycle = ((float)(degree*5)/180 + 5.0);
    pulseWidth = dutyCycle*(PWM_RANGE/100);

    softPwmWrite(PIN, pulseWidth);

    delay(600);

    return 0;
}