#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#include "rpi_2_motor.h"

int moveMotor(int inputValue)
{
    float dutyCycle; // the unit is %
    int pulseWidth;
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#include "rpi_2_motor.h"

int inputValue;

int moveMotor(int inputValue)
{
    float dutyCycle; // the unit is %
    int pulseWidth;

    if (inputValue < 0)
    {
        printf("The inputValue is smaller than 0");
        return -1;
    }

    wiringPiSetupGpio();
    pinMode(PIN, OUTPUT); // wrong positon PIN

    // Set PWM range (= the total number of clock ticks during a period)
    if(softPwmCreate(PIN, 0, PWM_RANGE) != 0){
        printf("softPwmcreate error!!");
        return -1;
    }

    dutyCycle = ((float)(inputValue * 5) / 180 + 5.0);
    pulseWidth = dutyCycle * (PWM_RANGE / 100);

    softPwmWrite(PIN, pulseWidth);

    delay(600);

    printf("RPC request 'moveMotor(%d)' and receved and processed\n", inputValue);

    return 0;
}
    if (inputValue < 0)
    {
        printf("The inputValue is smaller than 0");
        return -1;
    }

    wiringPiSetupGpio();
    pinMode(PIN, OUTPUT); // wrong positon PIN

    // Set PWM range (= the total number of clock ticks during a period)
    if(softPwmCreate(PIN, 0, PWM_RANGE) != 0){
        printf("softPwmcreate error!!");
        return -1;
    }

    dutyCycle = ((float)(inputValue * 5) / 180 + 5.0);
    pulseWidth = dutyCycle * (PWM_RANGE / 100);

    softPwmWrite(PIN, pulseWidth);

    delay(600);

    printf("RPC request 'moveMotor(%d)' and receved and processed\n", inputValue);

    return 0;
}