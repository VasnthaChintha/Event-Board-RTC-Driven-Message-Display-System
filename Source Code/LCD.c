//lcd.c
#include "defines.h"
#include "types.h"
#include <lpc21xx.h>
#include "delay.h"
#include "lcd_defines.h"
#include "RTC.h"
// LCD driver: routines below write commands, characters, strings, and numbers to the display
// Write one byte to the LCD data bus and generate the enable pulse
void WriteLCD(u8 data)
{
	SCLRBIT(IOCLR0,RW); // Clear the RW pin (RW = 0) to select LCD write operation
	WRITEBYTE(IOPIN0,LCD_DATA,data); // Send the 8-bit data value to the LCD data pins
	SSETBIT(IOSET0,EN); // Set the Enable pin HIGH (EN = 1) to enable LCD data transfer
	delay_us(1); // Wait for 1 microsecond to allow the LCD to detect the enable signal
	SCLRBIT(IOCLR0,EN); // Clear the Enable pin (EN = 0) to generate the falling edge and latch data into LCD
	delay_ms(2); // Wait for 2 milliseconds to allow the LCD to process the received data
}
// Function to send an instruction or command to the LCD
void CmdLCD(u8 cmd)
{
	SCLRBIT(IOCLR0,RS); // Set RS = 0 to select the LCD instruction register
	WriteLCD(cmd); // Send the command byte to the LCD through the data pins
}
// Function to display a single ASCII character on the LCD
void CharLCD(u8 ascii)
{
	SSETBIT(IOSET0,RS); // Set RS = 1 to select the LCD data register
	WriteLCD(ascii); // Send the ASCII character to the LCD for display
}
// Function to initialize the LCD in 8-bit communication mode
void InitLCD(void)
{
	// Configure LCD data pins P0.8 to P0.15 as GPIO output pins
	WRITEBYTE(IODIR0,LCD_DATA,0xFF); // Set all 8 LCD data pins as outputs
	SETBIT(IODIR0,RS); // Configure RS pin as output
	SETBIT(IODIR0,RW); // Configure RW pin as output
	SETBIT(IODIR0,EN); // Configure EN pin as output
	delay_ms(15); // Wait 15 milliseconds for LCD power stabilization
	CmdLCD(MODE_8BIT_1LINE); // Send initial function-set command to configure 8-bit mode
	delay_ms(5); // Wait 5 milliseconds for LCD to process the command
	CmdLCD(MODE_8BIT_1LINE); // Repeat function-set command as required by LCD initialization sequence
	delay_us(100); // Wait 100 microseconds before sending the next initialization command
	CmdLCD(MODE_8BIT_1LINE); // Send function-set command again to ensure proper initialization
	CmdLCD(MODE_8BIT_2LINE); // Configure LCD for 8-bit interface and 2-line display
	CmdLCD(DISP_ON_CUR_OFF); // Turn ON the LCD display and turn OFF the cursor
	CmdLCD(CLEAR_LCD ); // Clear all characters from the LCD display
	CmdLCD(SHIFT_CUR_RIGHT ); // Set cursor movement direction to right after writing a character
}
// Function to display a null-terminated string on the LCD
void StrLCD(u8* str)
{
	while(*str) // Continue until the null character '\0' is encountered
	{
		CharLCD(*str++); // Display the current character and increment the string pointer
	}
}
// Function to display an unsigned 32-bit integer on the LCD
void U32LCD(u32 n)
{
	u8 a[10]; // Declares an array to store individual digits of the number
                  // Maximum 10 digits are required for a 32-bit unsigned integer
	s32 i=0; // Declares a signed 32-bit integer variable i, It is used as an index for the array
  if(n==0) // Checks whether the given number is zero
	{
		CharLCD('0'); // Displays character '0' directly on the LCD
	}
	else // Executes when the given number is non-zero
	{
		while(n)  // Repeats the loop until n becomes zero
		{
			a[i++]=(n%10)+'0'; //n%10 extracts the last digit of the number
			n/=10;  // Removes the last digit from the number
    }
		for(--i; i>=0; i--) 
		{
			CharLCD(a[i]); // Sends the stored ASCII digit to the LCD ,Displays the digits one by one in the correct order
		}
	}
}
// Function to create a custom character in LCD CGRAM
void BuildCGRAM(u8* p, u8 nBytes) 
{
	s32 i;  // Declares a signed 32-bit integer variable
                                // Used as an index to access the character pattern array
	CmdLCD(GOTO_CGRAM); // Sends the command to the LCD to select CGRAM
                                // CGRAM stands for Character Generator RAM
                                // It is used to store user-defined custom characters
	for(i=0; i<nBytes; i++) // Loop executes from 0 to nBytes-1
                                // It transfers the specified number of bytes
	{
		CharLCD(p[i]); // Sends each byte of the custom character pattern
                                // to the LCD CGRAM through the LCD data register
	}
}
