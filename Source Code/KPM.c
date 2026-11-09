//KPM.c
#include "defines.h"
#include<lpc21xx.h>
#include "types.h"
#include "lcd.h"
// Define the GPIO pin numbers for the 4x4 matrix keypad rows and columns on Port 1
// ROW CONFIGURATION
#define ROW0 16    // Assign P1.16 as Row 0 of the keypad
#define ROW1 17    // Assign P1.17 as Row 1 of the keypad
#define ROW2 18    // Assign P1.18 as Row 2 of the keypad
#define ROW3 19    // Assign P1.19 as Row 3 of the keypad
// COLUMN CONFIGURATION
#define COL0 20    // Assign P1.20 as Column 0 of the keypad
#define COL1 21    // Assign P1.21 as Column 1 of the keypad
#define COL2 22    // Assign P1.22 as Column 2 of the keypad
#define COL3 23    // Assign P1.23 as Column 3 of the keypad

u8 KpmLUT[4][4]={{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'c',0,'=','+'}}; // Declares a 4x4 array to store keypad values
// Function to initialize the keypad
void InitKPM(void)
{
        WRITENIBBLE(IODIR1,ROW0,15); // Configures 4 consecutive GPIO pins of Port 1 as output pins
}
// Function to check whether any key is pressed in the keypad
u8 ColScan(void)
{
				// Reads the four column pin values from Port 1
        // READNIBBLE() reads 4 consecutive bits starting from COL0
        // Compares the read value with 15 (binary 1111)
        if((READNIBBLE(IOPIN1,COL0))<15) 
                return 0; // Returns 0 if any column pin is LOW
                           // Indicates that a key press is detected

        else
                return 1; // Returns 1 if all four column pins are HIGH
                           // Indicates that no key is pressed
}
// Function to identify which row contains the pressed key
u8 RowCheck(void)
{
	u8 rno; // Declares an 8-bit unsigned variable to store the row number
	for(rno=0; rno<=3; rno++) // Loops through all four rows (row 0 to row 3)
	{
		WRITENIBBLE(IOPIN1,ROW0,~(1<<rno)); // Activates one row at a time by making its corresponding pin LOW
		if(ColScan()==0) // Calls ColScan() to check whether any key is pressed
		{
			break; // Stops the loop when a pressed key is detected
		}
	}
	WRITENIBBLE(IOPIN1,ROW0,0x0);  // Writes 0000 to all four row pins, Makes all four row outputs LOW after scanning
	return rno; // Returns the detected row number (0 to 3)
}
// Function to identify which column contains the pressed key
u8 ColCheck(void)
{
	u8 cno; // Declares an 8-bit unsigned variable to store the column number
	for(cno=0; cno<=3; cno++) // Loops through all four columns (column 0 to column 3)
	{
		if(STATUSBIT(IOPIN1,(COL0+cno))==0)// Reads the status of one column pin at a time
		{
			break;  // Terminates the loop when a LOW column is detected
		}
	}
	return cno; // Returns the detected column number (0 to 3)
}
// Function to scan the 4x4 keypad and return the pressed key value
u8 KeyScan(void)
{
	u8 keyv,rno,cno;  // Declares three unsigned 8-bit variables, keyv stores the detected key value, rno stores the row number, cno stores the column number
	while(ColScan()); // Waits until a key is pressed
  rno = RowCheck(); // Calls RowCheck() to identify the pressed key's row, Stores the detected row number in rno (0 to 3)
  cno = ColCheck(); // Calls ColCheck() to identify the pressed key's column, Stores the detected column number in cno (0 to 3)
  keyv = KpmLUT[rno][cno]; // Accesses the keypad look-up table using row and column numbers, Retrieves the corresponding key value, Stores the key value in keyv
	while(!ColScan()); // Waits until the pressed key is released
	return keyv; // Returns the detected key value to the calling function
}
u32 ReadNum(void)
{
	s32 key,i=0; // Declares a signed 32-bit variable key to store the pressed keypad key, i is initialized to 0 and tracks the LCD cursor position / digit count
	u32 sum=0;	// Declares an unsigned 32-bit variable sum, Initializes sum to zero, Stores the complete number entered through the keypad
	while(1) // Starts an infinite loop to continuously read keypad inputs
  {
		CmdLCD(0xc0+i); // Sets the LCD cursor position, 0xC0 represents the starting address of the second LCD row, Adding i moves the cursor to the next position
		key=KeyScan(); // Calls KeyScan() to detect the pressed keypad key, Stores the detected key value in the key variable
		if((key>=0)&&(key<=9))   // Checks whether the pressed key is a numeric digit from 0 to 9
		{
			U32LCD(key); // Displays the entered numeric digit on the LCD
			sum=(sum*10)+(key);   // Shifts the previously entered number one decimal position left, Adds the newly entered digit to the num
			i++; // Increments the cursor position
		}
		else if(key=='c') // Checks whether the Clear/Backspace key 'c' is pressed
		{
			if(i>0) // Checks whether at least one digit has been entered
			{
				i--;  // Decrements the digit count
				CmdLCD(0xc0+(i)); // Moves the LCD cursor to the previous digit position
				CharLCD(' '); // Displays a blank space at the previous position
				sum/=10; // Removes the last digit from the stored number
			}
		}
		else if(key=='=')   // Checks whether the equal key '=' is pressed
			break;	// Terminates the infinite while loop
   }
   return sum; // Returns the final number entered through the keypad
}
