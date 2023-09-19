#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>  

#include "rpi_2_lcd.h"

int deviceHandle;

void toggleLCDEnable(int eightBits)
{
  // Toggle enable pin on LCD display
  delayMicroseconds(500);
  wiringPiI2CWrite(deviceHandle, (eightBits | LCD_ENABLE));
  delayMicroseconds(500);
  wiringPiI2CWrite(deviceHandle, (eightBits | LCD_DISABLE));
  delayMicroseconds(500);
}

void sendBitsToLCD(int eightBits, int mode)
{
  // Send data or instruction to LCD I/O register
  // eightBits = the data or instruction to send
  // mode can be OR'ed with LCD_BACKLIGH_ON/OFF, LCD_ENABLE/DISABLE, LCD_RW_READ/WRITE, LCD_RS_DATA/INST
  // Since we use 4-bit mode, we first send high 4 bits (highFourBits), and then send low 4 bits (lowFourBits)
  int highFourBits;
  int lowFourBits;

  // The LCD's I/O register reads only the four high order data pins each time the Enable pin is pulsed
  // Let 'xxxx yyyy' be "eightBits" received as the parameter of sendBitsToLCD() function
  // We will first send highFourBits in the form of 'xxxx abcd', and then send lowFourBits in the form of 'yyyy abcd'  
  // We found that wiringPi uses the remaining 4-bit 'abcd' to control LCD pins as follows  
  //    'a': LCD_BACKLIGHT_ON or LCD_BACKLIGHT_OFF 
  //    'b': LCD_ENABLE or LCD_DISABLE
  //    'c': LCD_RW_READ or LCD_RW_WRITE
  //    'd': LCD_RS_DATA or LCD_RS_INST
  highFourBits = mode | (eightBits & 0xF0) | LCD_BACKLIGHT_ON;                // Let's always turn on the backlight
  lowFourBits = mode | ((eightBits << 4) & 0xF0) | LCD_BACKLIGHT_ON;          // Let's always turn on the backlight
  
  // First, send highFourBits and pulse the enable pin
  wiringPiI2CWrite(deviceHandle, highFourBits);  // 'xxxx abcd': xxxx is the high 4 bits of eightBits
  toggleLCDEnable(highFourBits);

  // Next, send lowFourBits and pulse the enable pin
  wiringPiI2CWrite(deviceHandle, lowFourBits);   // 'yyyy abcd': yyyy is the low 4 bits of eightBits
  toggleLCDEnable(lowFourBits);
}

// Let's initialize LCD
// We found that, to make LCD work correctly, we need to perform some operation more than once
// We also found that, to make LCD work correctly, we need to use some specific values for undefined bit fields
// It seems like that there is something unpublished, or LCD may have some bugs
// So do not change the following initialization function 
void initializeLCD()
{
  // Instruction: Function Set '001D NF--' 
  sendBitsToLCD(0x33, LCD_RS_INST | LCD_RW_WRITE);       // "0011 0011" (8-bit mode, 1 line, 5x8 dots)

  // Instruction: Function Set '001D NF--'
  sendBitsToLCD(0x32, LCD_RS_INST | LCD_RW_WRITE);       // "0011 0010" (8-bit mode, 1 line, 5x8 dots)
  
  // Instruction: Entry Mode Set '0000 01IS'
  sendBitsToLCD(0x06, LCD_RS_INST | LCD_RW_WRITE);       // "0000 0110" (cursor move direction is increment, normal shift operation)

  // Instruction: Display ON/OFF Control '0000 1DCB'
  sendBitsToLCD(0x0C, LCD_RS_INST | LCD_RW_WRITE);       // "0000 1100" (display on, cursor Off, blink off)

  // Instruction: FUnction Set '001D NF--'
  sendBitsToLCD(0x28, LCD_RS_INST | LCD_RW_WRITE);       // "0010 1000" (4-bit mode, 2 lines, 5x8 dots)

  // Instruction: Clear Display
  sendBitsToLCD(0x01, LCD_RS_INST | LCD_RW_WRITE);       // "0000 0001" (clear display)

  sendBitsToLCD(0x80, LCD_RS_INST | LCD_RW_WRITE);       // set the cursor to '0x80'

  delayMicroseconds(500);
}

// Display text string 
int displayText(int line, const char *stringPointer)
{
  char characterToSend;
  int i = 0;

  if (line == 1)
    sendBitsToLCD(0x80, LCD_RS_INST | LCD_RW_WRITE);   // 1st position in 1st line: "1000 0000" | "0000 0000"
  else if (line == 2)
    sendBitsToLCD(0xC0, LCD_RS_INST | LCD_RW_WRITE);   // 1st position in 2nd line: "1100 0000" | "0000 0000"
  else
    return -1;

  while (*stringPointer) {
    characterToSend = *stringPointer;

    // Don't send LF (line feed or new line) since LCD will display LF as some character on the screen 
    // Note that ASCII code of LF is 10
    if ((unsigned int)characterToSend != 10) {
      sendBitsToLCD(*(stringPointer++), LCD_RS_DATA | LCD_RW_WRITE);
    }
    else
      return -1;
  }
  while(stringPointer[i] != '\0'){
    i++
  }
  return i;
}

// Change the text line
// void changeLine(int line)
// {
//   if (line == 1)
//     sendBitsToLCD(0x80, LCD_RS_INST | LCD_RW_WRITE);   // 1st position in 1st line: "1000 0000" | "0000 0000"
//   else if (line == 2)
//     sendBitsToLCD(0xC0, LCD_RS_INST | LCD_RW_WRITE);   // 1st position in 2nd line: "1100 0000" | "0000 0000"
//   else
//     return;
// }