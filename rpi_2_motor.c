#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#include "rpi_2_motor.h"


void moveMotor(int degree)
{
    float dutyCycle;        // the unit is %
    int pulseWidth;

    dutyCycle = ((float)(degree*5)/180 + 5.0);
    pulseWidth = dutyCycle*(PWM_RANGE/100);

    softPwmWrite(PIN, pulseWidth);

    printf("RPC request 'moveMotor(120)' received and processed.");
    printf("\n");

    return;
}

int R2_motor(void) 
{
    int inputValue;         // the unit is degree
    
    wiringPiSetupGpio();
    pinMode(PIN, OUTPUT);

    // Set PWM range (= the total number of clock ticks during a period)
    softPwmCreate(PIN, 0, PWM_RANGE);
  
    inputValue = 180;
    moveMotor(inputValue);
    delay(600);
    inputValue = 0;
    moveMotor(inputValue);
    delay(600);


    return 1;
}