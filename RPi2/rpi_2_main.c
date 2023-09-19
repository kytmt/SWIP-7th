#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <wiringPiI2C.h>
#include <stdlib.h>


#include "rpi_2_lcd.h"
#include "rpi_2_motor.h"


int main()
{
    int inputValue;
    while(1) 
    {     
        printf("Enter the position of motor (in degree): ");
        scanf("%d", &inputValue);
        
        moveMotor(inputValue);
        
        delay(600);
    }
}