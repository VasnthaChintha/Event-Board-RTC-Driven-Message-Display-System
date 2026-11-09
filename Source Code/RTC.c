#include<lpc21xx.h>
#include"types.h"
#include"lcd.h"
#define GOTO_LINE1_POS0 0x80
#define GOTO_LINE2_POS0 0xc0
// Define the clock frequency, RTC prescaler values, control bits, and weekday constants
// CLOCK CONFIGURATION
#define FOSC 12000000             // Define the external oscillator frequency as 12 MHz
#define CCLK (5*FOSC)              // Calculate the CPU clock frequency (12 MHz × 5 = 60 MHz)
#define PCLK (CCLK/4)              // Calculate the peripheral clock frequency (60 MHz / 4 = 15 MHz)
// RTC PRESCALER CONFIGURATION
#define PREINT_VAL (int) ((PCLK / 32768) - 1) // Calculate the integer portion of the RTC prescaler value
#define PREFRAC_VAL (PCLK -((PREINT_VAL + 1) * 32768)) // Calculate the fractional portion of the RTC prescaler value
// RTC CONTROL BITS
#define RTC_ENABLE (1<<0)         // Set bit 0 to enable the RTC
#define RTC_RESET (1<<1)          // Set bit 1 to reset the RTC counters
#define RTC_CLKSRC (1<<4)         // Set bit 4 to select the RTC clock source
// WEEKDAY DEFINITIONS
#define SUNDAY 0                  // Define Sunday as day number 0
#define MONDAY 1                  // Define Monday as day number 1
#define TUESDAY 2                 // Define Tuesday as day number 2
#define WEDNESDAY 3               // Define Wednesday as day number 3
#define THURSDAY 4                // Define Thursday as day number 4
#define FRIDAY 5                  // Define Friday as day number 5
#define SATURDAY 6                // Define Saturday as day number 6
u8 week[][5] = {"SUN","MON","TUE","WED","THUR","FRI","SAT"}; // Declares a 2D character array to store weekday names

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
