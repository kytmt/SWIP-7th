

#include <unistd.h>

#define GPIO_LED 4 // LED pin Number
#define BLINK_1s 0 // blinking every 1 second
#define BLINK_10Hz 1 // blinking 10Hz when detected within 20cm

void* blinkLED();