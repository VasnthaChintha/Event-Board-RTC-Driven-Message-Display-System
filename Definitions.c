#include<LPC21xx.h> // Includes the LPC2148 microcontroller header file
                    // Provides register definitions for GPIO, UART, ADC, timers, etc
#include "Defines.h" // Includes user-defined data types, macros and pin definitions
// Keypad Look-Up Table (LUT)
u8 KpmLUT[4][4]={{7,8,9,'/'},{4,5,6,'*'},{1,2,3,'-'},{'c',0,'=','+'}}; // Declares a 4x4 array to store keypad values
u8 week[][5] = {"SUN","MON","TUE","WED","THUR","FRI","SAT"}; // Declares a 2D character array to store weekday names

															//Delay
// Delay routines: the loop counts are calibrated approximately for a 60 MHz CPU clock
// Microsecond Delay Function
void delay_us(u32 tdly) // Function accepts delay time in microseconds
{
	tdly*=12; // Multiplies the requested delay by 12
									// Approximately 12 loop iterations are used per microsecond
	while(tdly--); // Executes an empty loop until tdly becomes zero
                       // Each iteration consumes processor clock cycles
}                   
// Millisecond Delay Function
void delay_ms(u32 tdly) // Function accepts delay time in milliseconds
{
	tdly*=12000; // Multiplies the requested delay by 12000
                     // Approximately 12000 loop iterations are used per millisecond
	while(tdly--);  // Repeats the empty loop until the counter reaches zero.
                        // This generates the required approximate delay
}
// Second Delay Function
void delay_s(u32 tdly)  // Function accepts delay time in seconds
{
	tdly*=12000000; // Multiplies the requested delay by 12000000
                        // Approximately 12 million loop iterations are used per second
	while(tdly--); // Executes the empty loop until the counter reaches zero
                       // This generates the required approximate delay
}
															//ADC
//INITIALIZATION OF ADC
void Init_ADC(void)
{
	PINSEL1|=AIN3; //cfg p0.30 for AIN3---channel 3
	ADCR=PDN_BIT|CLKDIV; // Power up ADC0 and load the ADC clock-divider value
}
// Read one ADC channel and return both the raw digital count and calculated voltage
void Read_ADC(u32 chno,f32 *eAR, u32 *ADCDVAL)
{
	ADCR&=(~(255<<0)); // Clear the previous channel-selection bits (SEL[7:0])
	ADCR|=(chno|START_CONV); // Select the requested channel and set START to begin conversion
	delay_us(3);  // Allow the ADC conversion process to proceed briefly
	while(((ADDR>>DONE_BIT)&1)==0); // Wait until the DONE flag indicates conversion completion
	ADCR&=(~(START_CONV)); // Clear START so the ADC is no longer commanded to start
	*ADCDVAL=(ADDR>>RESULT)&1023; // Extract the 10-bit ADC result (0 to 1023)
	*eAR=((3.3/1023)*(*ADCDVAL)); // Convert the digital count to voltage for a 3.3 V reference
}
															//LCD
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

															//KPM
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

															//RTC
// Function to initialize the Real-Time Clock (RTC) peripheral
void RTC_Init(void)
{
	CCR = RTC_RESET;
        // Writes the RTC reset command into the Clock Control Register (CCR)
        // Resets the RTC counters and prescaler divider
        // Prepares the RTC peripheral for initialization
	#ifndef _LPC2148
        // Checks whether the macro _LPC2148 is NOT defined
        // If it is not defined, executes the following code
	PREINT = PREINT_VAL;
        // Configures the integer portion of the RTC prescaler
        // PREINT stores the integer prescaler value
        // PREINT_VAL is a predefined macro containing the calculated value
	PREFRAC = PREFRAC_VAL;
        // Configures the fractional portion of the RTC prescaler
        // PREFRAC stores the fractional prescaler value
        // PREFRAC_VAL is a predefined macro containing the calculated value
	CCR = RTC_ENABLE;
        // Enables the RTC by setting the RTC enable bit in CCR
        // Uses the default RTC clock source for this configuration
	#else
        // Executes this section when _LPC2148 is defined
	CCR = RTC_ENABLE | RTC_CLKSRC;
        // Enables the RTC and selects its clock source
        // Bitwise OR (|) combines both control bits
        // RTC_ENABLE enables the RTC
        // RTC_CLKSRC selects the RTC clock source
	#endif
        // Ends the conditional compilation block
}
// Function to read the current RTC time
// Accepts three pointer arguments to store hours, minutes and seconds
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)
{
	*hour = HOUR;
        // Reads the current hour value from the RTC HOUR register
        // *hour accesses the memory location pointed to by hour
        // Stores the RTC hour value in the caller's variable
	*minute = MIN;
        // Reads the current minute value from the RTC MIN register
        // *minute accesses the memory location pointed to by minute
        // Stores the RTC minute value in the caller's variable
	*second = SEC;
        // Reads the current second value from the RTC SEC register
        // *second accesses the memory location pointed to by second
        // Stores the RTC second value in the caller's variable
}
// Function to display RTC time in HH:MM:SS format on the LCD
void DisplayRTCTime(s32 hour, s32 minute, s32 second)
{
	CmdLCD(GOTO_LINE1_POS0);
        // Moves the LCD cursor to the first row, first column
        // GOTO_LINE1_POS0 is a predefined LCD command
	CharLCD(hour/10+48);
        // Divides the hour by 10 to extract the tens digit
        // Adds 48 (ASCII value of '0') to convert the digit into ASCII
        // Sends the tens digit of the hour to the LCD
	CharLCD(hour%10+48);
        // Uses modulo 10 to extract the units digit of the hour
        // Adds 48 to convert the numeric digit into its ASCII character
        // Displays the units digit of the hour
	CharLCD(':');
        // Displays a colon separator between hours and minutes
	CharLCD(minute/10+48);
        // Divides the minute by 10 to extract the tens digit
        // Adds 48 to convert the digit into ASCII
        // Displays the tens digit of the minute
	CharLCD(minute%10+48);
        // Uses modulo 10 to extract the units digit of the minute
        // Adds 48 to convert the digit into ASCII
        // Displays the units digit of the minute
	CharLCD(':');
        // Displays a colon separator between minutes and seconds
	CharLCD(second/10+48);
        // Divides the second by 10 to extract the tens digit
        // Adds 48 to convert the digit into ASCII
        // Displays the tens digit of the second
	CharLCD(second%10+48);
        // Uses modulo 10 to extract the units digit of the second
        // Adds 48 to convert the digit into ASCII
        // Displays the units digit of the second
}
// Function to read date, month and year from the RTC
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)
{
	*date = DOM;
        // Reads the current date from the RTC DOM (Date Of Month) register
        // Stores the date value in the memory location pointed to by date
	*month = MONTH;
        // Reads the current month from the RTC MONTH register
        // Stores the month value in the memory location pointed to by month
	*year = YEAR;
        // Reads the current year from the RTC YEAR register
        // Stores the year value in the memory location pointed to by year
}
// Function to display RTC date in DD/MM/YYYY format on the LCD
void DisplayRTCDate(s32 date, s32 month, s32 year)
{
	CmdLCD(GOTO_LINE2_POS0);
        // Moves the LCD cursor to the second row, first column
        // GOTO_LINE2_POS0 is a predefined LCD command
	CharLCD(date/10+48);
        // Divides the date by 10 to extract the tens digit
        // Adds 48 (ASCII value of '0') to convert the digit into ASCII
        // Displays the tens digit of the date
	CharLCD(date%10+48);
        // Uses modulo 10 to extract the units digit of the date
        // Adds 48 to convert the digit into ASCII
        // Displays the units digit of the date
	CharLCD('/');
        // Displays '/' as a separator between date and month
	CharLCD(month/10+48);
        // Divides the month by 10 to extract the tens digit
        // Adds 48 to convert the digit into ASCII
        // Displays the tens digit of the month
	CharLCD(month%10+48);
        // Uses modulo 10 to extract the units digit of the month
        // Adds 48 to convert the digit into ASCII
        // Displays the units digit of the month
	CharLCD('/');
        // Displays '/' as a separator between month and year
	U32LCD(year);
        // Converts the year into individual ASCII digits
        // Displays the complete year on the LCD
}
// Function to set hours, minutes and seconds in the RTC
void SetRTCTimeInfo(s32 hour, s32 minute, s32 second)
{
	HOUR = hour;        // Writes the given hour value into the RTC HOUR register
	MIN = minute;        // Writes the given minute value into the RTC MIN register
	SEC = second;        // Writes the given second value into the RTC SEC register
}
// Function to set date, month and year in the RTC
void SetRTCDateInfo(s32 date, s32 month, s32 year)
{
	DOM = date;        // Writes the given date value into the RTC DOM (Date Of Month) register
	MONTH = month;        // Writes the given month value into the RTC MONTH register
	YEAR = year;        // Writes the given year value into the RTC YEAR register
}
// Function to get the current day of the week from the RTC
void GetRTCDay(s32 *dow)
{
	*dow = DOW; // Read the current day of the week from the RTC register (DOW) and store it at the memory address pointed to by dow
}
// Function to display the day of the week on the LCD
void DisplayRTCDay(s32 dow)
{
	CmdLCD(GOTO_LINE1_POS0+11); // Move the LCD cursor to the first line, position 11
	StrLCD(week[dow]);          // Display the corresponding day of the week from the week array on the LCD
}
// Function to set the day of the week in the RTC
void SetRTCDay(s32 dow)
{
	DOW = dow; // Set the day-of-week value in the RTC Day of Week (DOW) register
}
// Function to display minutes and seconds on the LCD with a 2-second delay adjustment
void DisplayRTCTime_delay(s32 minute, s32 second)
{
	s32 i=0;                         // Initialize the local variable i to 0
	CmdLCD(GOTO_LINE2_POS0);         // Move the LCD cursor to the beginning of the second line
	CharLCD(minute/10+48);           // Extract the tens digit of minutes and display it on the LCD
	CharLCD(minute%10+48);           // Extract the units digit of minutes and display it on the LCD
	CharLCD(':');                   // Display the colon separator between minutes and seconds
	CharLCD(second/10+48);          // Extract the tens digit of seconds and display it on the LCD
	CharLCD(second%10+48);          // Extract the units digit of seconds and display it on the LCD
	i+=2;                            // Increment the variable i by 2
	second-=2;                       // Decrement the second variable by 2
}
