#include<LPC21XX.h>       // Include the LPC2148 microcontroller header file for accessing hardware registers
#include "Definitions.h"  // Include the header file containing user-defined data types, macros, and configurations
#define TOTAL_MESSAGES 10  // Define the maximum number of messages as 10
#define LED_GREEN 24      // Assign P1.24 as the green LED pin
#define LED_RED   25      // Assign P1.25 as the red LED pin
#define SW        2       // Assign P0.2 as the switch input pin
// GLOBAL VARIABLE DECLARATIONS
s32 Hour,j,k,l, Min, Sec, Date, Month, Year, Day, option=0, message_no, enable_bit,delay; // Declare signed 32-bit global variables to store RTC time, date, day, menu option, message number, enable status, delay, and temporary processing values
f32 eAR;                  // Declare a floating-point variable to store the ADC converted voltage or analog reading
u32 Temp;                 // Declare an unsigned 32-bit variable to store the temperature value
// LCD CUSTOM CHARACTER CONFIGURATION
u8 CgramLUT[10]={0x01,0x01,0x09,0x1f,0x08,0x00,0x00,0x00}; // Define an array containing 8 bytes of custom character pattern data for LCD CGRAM
// MESSAGE STRUCTURE DEFINITION
typedef struct {
    s32 hour;             // Store the hour at which the message should be displayed
    s32 minute;           // Store the minute at which the message should be displayed
    u8 text[80];          // Store the message text with a maximum capacity of 80 characters
    u32 enabled;          // Store the message enable/disable status (1 = enabled, 0 = disabled)
} Message;                // Define Message as a user-defined structure data type
int main() 
{
	s32 r,i,len=0,delay_minute,delay_sec;
  // Declare local signed 32-bit variables for loop control, message length, and storing delay minutes and seconds
  // Initialize the messageList array with 10 predefined scheduled messages
  Message messageList[TOTAL_MESSAGES] = {
        {7, 45, "Good Morning! Classes Start Soon", 1},
        {8, 45, "C Programming Session in Classroom number 2", 1},
        {9, 15, "C module theory exam in 4th floor lab1 ", 1},
        {10, 15, "C module lab exam in 4th floor lab2 and middle lab at 10:30AM ", 1},
        {12, 45, "Lunch Break from 1PM - 2PM ", 1},
        {13, 45, "ARM Workshop on external interrupts in LAB1 at 10AM ", 1},
        {14, 45, "ARM kit issue time from 10AM - 10:30AM in middle lab ", 1},
        {15, 15, "Only 15 mins break time for next ARM session ", 1},
        {17, 00, " Revise today's Class programs at home! ", 1},
        {17, 45, " End of Day - See You Tomorrow! ", 1}
				};
	RTC_Init();                 // Initialize the Real-Time Clock (RTC) module
  Init_ADC();                 // Initialize the Analog-to-Digital Converter (ADC) module
  InitLCD();                  // Initialize the LCD display
  InitKPM();                  // Initialize the 4x4 matrix keypad
  IODIR1 |= (1 << LED_GREEN); // Configure P1.24 as an output pin for the green LED
  IODIR1 |= (1 << LED_RED);   // Configure P1.25 as an output pin for the red LED
	while(1)
  {
		// Continuously execute the following operations to update the RTC information and temperature
    GetRTCTimeInfo(&Hour, &Min, &Sec); // Read the current hours, minutes, and seconds from the RTC and store them in the respective variables
    GetRTCDateInfo(&Date, &Month, &Year); // Read the current date, month, and year from the RTC
    GetRTCDay(&Day); // Read the current day of the week from the RTC
    Read_ADC(0x08,&eAR,&Temp); // Read the analog value from ADC channel 3 (AIN3) connected to the LM35 temperature sensor. Store the converted voltage in eAR and the ADC digital value in Temp
    IOSET1=(1<<LED_RED); // Set P1.25 HIGH to turn ON the red LED
    DisplayRTCTime(Hour, Min, Sec); // Display the current time (hours, minutes, and seconds) on the LCD
    DisplayRTCDay(Day); // Display the current day of the week on the LCD
    DisplayRTCDate(Date, Month, Year); // Display the current date, month, and year on the LCD
    CmdLCD(GOTO_LINE2_POS0 +11); // Move the LCD cursor to the 12th position of the second line to display temperature       
    Temp=((3.3/1023)*(Temp))*100; // Convert the 10-bit ADC digital value into temperature in Celsius using the LM35 conversion formula
    U32LCD(Temp); // Display the calculated temperature value on the LCD
    CmdLCD(GOTO_LINE2_POS0+13); // Move the LCD cursor to the 14th position of the second LCD line
    CharLCD(0xDF); // Display the degree (°) symbol on the LCD
    CmdLCD(GOTO_LINE2_POS0+14);  // Move the LCD cursor to the 15th position of the second LCD line
    CharLCD('C'); // Display the letter C to indicate temperature in Celsius
    for(r = 0; r < TOTAL_MESSAGES; r++) // Check all scheduled messages to find a message matching the current RTC time
    {
			len=0;  // Initialize the message length counter to zero           
      if((Hour == messageList[r].hour && Min == messageList[r].minute && messageList[r].enabled == 1)) // Check whether the current RTC hour and minute match the scheduled message time and verify that the message is enabled
      {                
				delay_minute=15,delay_sec=0; // Initialize the message display countdown to 15 minutes and 0 seconds
        IOCLR1=1<<LED_RED; // Turn OFF the red LED by clearing P1.25
        IOSET1=1<<LED_GREEN; // Turn ON the green LED by setting P1.24
        CmdLCD(CLEAR_LCD); // Clear the LCD display before displaying the scheduled message
        delay=12000000;// Initialize the software delay counter               
        while(messageList[r].text[len] != '\0')
        len++; // Calculate the length of the scheduled message by counting character until the null terminator ('\0') is encountered
        while(delay_minute>=0 && (((IOPIN0>>SW)&1)==1)) // Continue displaying the message while the countdown is active and the switch is not pressed
        {
					for(j=15; j>=-len; j--) // Iterate through different positions to scroll the message
          {
						if(((IOPIN0>>SW)&1)==0)
						break; // Exit the scrolling loop if the switch is pressed
            if(((IOPIN0>>SW)&1)==1) // Execute the message display operation while the switch is not pressed
            {
							CmdLCD(GOTO_LINE2_POS0); // Move the LCD cursor to the beginning of the second line
              DisplayRTCTime_delay(delay_minute,delay_sec); // Display the remaining countdown minutes and seconds on the second LCD line
							CmdLCD(GOTO_LINE1_POS0); // Move the LCD cursor to the beginning of the first line
							for(i=0;i<16;i++) // Iterate through all 16 character positions of the first LCD line
							{
								if(((IOPIN0>>SW)&1)==0)
								break; // Stop displaying the message if the switch is pressed
                if((i-j)>=0 && (i-j)<len)
									CharLCD(messageList[r].text[i-j]); // Display the corresponding message character at the current scrolling position
                else
									CharLCD(' '); // Display a blank space when the scrolling position is outside the message length
              }
              if(delay_sec==0)
              {
								delay_sec=59; // Reset seconds to 59 when the countdown reaches zero
                if(delay_minute>0)
									delay_minute-=1; // Decrease the remaining minutes by one
							}
              if(delay==0)
              {
								delay_sec--; // Decrease the remaining seconds by one when the delay counter reaches zero
                delay=12000000; // Reload the delay counter for the next second
              }
              delay_ms(100); // Generate a delay of 100 milliseconds to control the scrolling speed
              delay=delay/15;  // Reduce the software delay counter to control the countdown timing
						}
					}
				}
        break; // Exit the message-search loop after processing the matching scheduled message
			}
		}
		if(((IOPIN0 >> SW) & 1) == 0)
    {
			// Check whether the switch connected to P0.2 is pressed (active LOW)
      IOCLR1=(1<<LED_GREEN)|(1<<LED_RED); // Turn OFF both green and red LEDs by clearing P1.24 and P1.25
      delay_ms(50);   // Generate a 50 ms delay for switch debouncing to avoid false triggering
      if(((IOPIN0 >> SW) & 1) == 0)
      {
				// Confirm that the switch is still pressed after the debounce delay
        while(option<3)
        {
					// Continue displaying the menu until a valid option is selected (1, 2, or 3)
					CmdLCD(CLEAR_LCD); // Clear the LCD display before showing the menu
					CmdLCD(GOTO_LINE1_POS0); // Move the LCD cursor to the beginning of the first line
					StrLCD("1.RTC 3.EXIT"); // Display the RTC settings and Exit menu options on the first line
					CmdLCD(GOTO_LINE2_POS0); // Move the LCD cursor to the beginning of the second line
					StrLCD("2.Message Edit"); // Display the Message Edit menu option on the second line
					option=KeyScan(); // Read the key pressed on the keypad and store the selected menu option
					// Perform the operation based on the menu option selected by the user
					switch(option)
					{
						case 1: option=0;  // Select RTC configuration and initialize the menu option to 0
						while(option!=4)
						{ 
							// Continue displaying the RTC menu until the user selects Exit (option 4)
							CmdLCD(CLEAR_LCD);          // Clear the LCD display
							CmdLCD(GOTO_LINE1_POS0);    // Move the cursor to the beginning of the first line
							StrLCD("1.TIME 2.DATE");     // Display Time and Date options
							CmdLCD(GOTO_LINE2_POS0);    // Move the cursor to the beginning of the second line
							StrLCD("3.Day 4.Exit");      // Display Day and Exit options
							option=KeyScan();           // Read the RTC menu option entered through the keypad
							switch(option)
							{
								case 1: // Select the TIME configuration option
												while(option<4)
												{
													// Display the time configuration menu until Exit is selected
													option=0;                       // Reset the menu option
													CmdLCD(CLEAR_LCD);              // Clear the LCD
													CmdLCD(GOTO_LINE1_POS0);        // Move the cursor to the first line
													StrLCD("1.Hour 2.Minute");      // Display Hour and Minute options
													CmdLCD(GOTO_LINE2_POS0);        // Move the cursor to the second line
													StrLCD("3.Second 4.Exit");      // Display Second and Exit options
													option=KeyScan();               // Read the selected time configuration option
													CmdLCD(CLEAR_LCD);              // Clear the LCD before processing the selection
													switch(option)
													{
														case 1: // Configure RTC Hour
																		StrLCD("Hour(0-23)");        // Display the valid hour input range
																		BuildCGRAM(CgramLUT,16);     // Load the custom character pattern into LCD CGRAM
                                    CmdLCD(GOTO_LINE1_POS0+10);  // Move the cursor to position 10 of the first line
                                    CharLCD(0);                  // Display the custom input cursor character
																		Hour=ReadNum();              // Read the hour value entered through the keypad
                                    while(Hour<0 || Hour>23)
                                    {
																			// Validate the entered hour value (valid range: 0 to 23)
																			CmdLCD(CLEAR_LCD);       // Clear the LCD
																			CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																			StrLCD("valid Hour:0-23"); // Display the valid hour range
																			BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																			CmdLCD(GOTO_LINE1_POS0+15); // Move the cursor to the last position of the first line
																			CharLCD(0);              // Display the custom cursor
																			Hour=ReadNum();          // Read the hour value again
																		}
                                    break; // Exit the Hour configuration case
														case 2: // Configure RTC Minute
																		StrLCD("minute(0-59)");     // Display the valid minute input range
                                    BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
                                    CmdLCD(GOTO_LINE1_POS0+12); // Position the cursor for minute input
																		CharLCD(0);                 // Display the custom cursor
                                    Min=ReadNum();              // Read the minute value entered through the keypad
                                    while(Min<0 || Min>59)
                                    {
																			// Validate the entered minute value (valid range: 0 to 59)
																			CmdLCD(CLEAR_LCD);      // Clear the LCD
																			CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																			StrLCD("valid Min:0-59"); // Display the valid minute range
																			BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																			CmdLCD(GOTO_LINE1_POS0+14); // Position the cursor for minute input
																			CharLCD(0);              // Display the custom cursor
																			Min=ReadNum();           // Read the minute value again
																		}
																		break; // Exit the Minute configuration case
														case 3: // Configure RTC Seconds
                                    StrLCD("Second:0-59");      // Display the valid seconds input range
                                    BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
                                    CmdLCD(GOTO_LINE1_POS0+11); // Position the cursor for seconds input
                                    CharLCD(0);                 // Display the custom cursor
                                    Sec=ReadNum();              // Read the seconds value entered through the keypad
                                    while(Sec<0 || Sec>59)
                                    {
																			// Validate the entered seconds value (valid range: 0 to 59)
																			CmdLCD(CLEAR_LCD);      // Clear the LCD
																			CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																			StrLCD("valid sec:0-59"); // Display the valid seconds range
																			BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																			CmdLCD(GOTO_LINE1_POS0+14); // Position the cursor for seconds input
																			CharLCD(0);              // Display the custom cursor
																			Sec=ReadNum();           // Read the seconds value again
																		}
																		break; // Exit the Seconds configuration case
													}
												}
                        option=0;                       // Reset the menu option
                        SetRTCTimeInfo(Hour, Min, Sec); // Update the RTC with the entered time
                        break; // Exit the TIME configuration case
						case 2:// Select the DATE configuration option
										while(option<4)
										{	
											// Continue displaying the date configuration menu until Exit is selected
											option=0;                       // Reset the menu optio
											CmdLCD(CLEAR_LCD);              // Clear the LCD
											CmdLCD(GOTO_LINE1_POS0);        // Move the cursor to the first line
											StrLCD("1.Date 2.Month");       // Display Date and Month options
											CmdLCD(GOTO_LINE2_POS0);        // Move the cursor to the second line
											StrLCD("3.Year 4.Exit");        // Display Year and Exit options
											option=KeyScan();               // Read the selected date configuration option
											CmdLCD(CLEAR_LCD);              // Clear the LCD before processing the selection
											switch(option)
											{
												case 1:// Configure RTC Date
																StrLCD("Date(1-31)");       // Display the valid date input range
																BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
																CmdLCD(GOTO_LINE1_POS0+10); // Position the cursor for date input
																CharLCD(0);                 // Display the custom cursor
																Date=ReadNum();             // Read the date entered through the keypad
																while(Date<1 || Date>31)
																{
																	// Validate the entered date (valid range: 1 to 31)
																	CmdLCD(CLEAR_LCD);      // Clear the LCD
																	CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																	StrLCD("valid Date:1-31"); // Display the valid date range
																	BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																	CmdLCD(GOTO_LINE1_POS0+15); // Position the cursor for date input
																	CharLCD(0);              // Display the custom cursor
																	Date=ReadNum();          // Read the date value again
																}
																break; // Exit the Date configuration case
												case 2: // Configure RTC Month
																StrLCD("Month:1-12");       // Display the valid month input range
																BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
																CmdLCD(GOTO_LINE1_POS0+10); // Position the cursor for month input
																CharLCD(0);                 // Display the custom cursor
																Month=ReadNum();            // Read the month entered through the keypad
																while(Month<1 || Month>12)
																{
																	// Validate the entered month (valid range: 1 to 12)
																	CmdLCD(CLEAR_LCD);      // Clear the LCD
																	CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																	StrLCD("valid Month:1-31"); // Display the validation message
																	BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																	CmdLCD(GOTO_LINE1_POS0+15); // Position the cursor for month input
																	CharLCD(0);              // Display the custom cursor
																	Month=ReadNum();         // Read the month value again
																}
																break; // Exit the Month configuration case
												case 3: // Configure RTC Year
																StrLCD("Year");             // Display the year input prompt
																BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
																CmdLCD(GOTO_LINE1_POS0+4);  // Position the cursor for year input
																CharLCD(0);                 // Display the custom cursor
																Year=ReadNum();             // Read the year entered through the keypad
																while(Year<1 || Year>2026)
																{
																	// Validate the entered year (valid range: 1 to 2026)
																	CmdLCD(CLEAR_LCD);      // Clear the LCD
																	CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
																	StrLCD("valid Year");    // Display the year validation message
																	BuildCGRAM(CgramLUT,16); // Load the custom cursor character
																	CmdLCD(GOTO_LINE1_POS0+10); // Position the cursor for year input
																	CharLCD(0);              // Display the custom cursor
																	Year=ReadNum();          // Read the year value again
																}
																break; // Exit the Year configuration case
											}
										}
										option=0;                               // Reset the menu option
										SetRTCDateInfo(Date, Month, Year);      // Update the RTC with the entered date
										break; // Exit the DATE configuration case
            case 3: // Configure RTC Day of the Week
                    CmdLCD(CLEAR_LCD);          // Clear the LCD
                    StrLCD("Day(0-6)");          // Display the valid weekday range
                    BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
                    CmdLCD(GOTO_LINE1_POS0+8);  // Position the cursor for weekday input
                    CharLCD(0);                 // Display the custom cursor
										Day=ReadNum();              // Read the weekday value entered through the keypad
                    while(Day<0 || Day>6)
                    {
											// Validate the weekday value (0 = Sunday to 6 = Saturday)
											CmdLCD(CLEAR_LCD);      // Clear the LCD
											CmdLCD(GOTO_LINE1_POS0); // Move the cursor to the first line
											StrLCD("valid Day:0-6"); // Display the valid weekday range
											BuildCGRAM(CgramLUT,16); // Load the custom cursor character
											CmdLCD(GOTO_LINE1_POS0+13); // Position the cursor for weekday input
											CharLCD(0);              // Display the custom cursor
											Day=ReadNum();           // Read the weekday value again
										}
										SetRTCDay(Day);              // Update the RTC with the selected weekday
										option=0;                    // Reset the menu option
										break;                       // Exit the Day configuration case
						case 4: break; // Exit the RTC configuration menu
						}
					}
					option=0; // Reset the menu option after exiting RTC configuration
          break;    // Exit the main menu's RTC case
          case 2:// Select the Message Edit optio
									CmdLCD(CLEAR_LCD);          // Clear the LCD display
                  CmdLCD(GOTO_LINE1_POS0);    // Move the cursor to the first line
                  StrLCD("MSG NO:0-");         // Display the message number selection prompt
                  U32LCD(TOTAL_MESSAGES-1);   // Display the maximum available message number (9)
                  BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
                  CmdLCD(GOTO_LINE1_POS0+10); // Position the cursor for message number input
                  CharLCD(0);                 // Display the custom cursor
                  message_no =ReadNum();      // Read the message number entered through the keypad
                  while(message_no < 0 || message_no >= TOTAL_MESSAGES)
                  {
										// Validate the message number (valid range: 0 to 9)
										CmdLCD(CLEAR_LCD);      // Clear the LCD
										StrLCD("valid MSG:0-");  // Display the message number validation prompt
										U32LCD(TOTAL_MESSAGES-1); // Display the maximum valid message number
										BuildCGRAM(CgramLUT,16); // Load the custom cursor character
										CmdLCD(GOTO_LINE1_POS0+13); // Position the cursor for message number input
										CharLCD(0);              // Display the custom cursor
										message_no = ReadNum();  // Read the message number again
									}
									CmdLCD(CLEAR_LCD);          // Clear the LCD display
									CmdLCD(GOTO_LINE1_POS0);    // Move the cursor to the first line
									StrLCD("1.EN 2.DIS");       // Display Enable and Disable options
									BuildCGRAM(CgramLUT,16);    // Load the custom cursor character
									CmdLCD(GOTO_LINE1_POS0+11); // Position the cursor for enable/disable input
									CharLCD(0);                 // Display the custom cursor
									enable_bit = ReadNum();     // Read the user's enable/disable selection
									messageList[message_no].enabled = (enable_bit == 1) ? 1 : 0;
                            // Enable the selected message if the entered value is 1
                            // Otherwise, disable the selected message
									CmdLCD(CLEAR_LCD);          // Clear the LCD after updating the message status
									break;                      // Exit the Message Edit case
					case 3: break; // Exit the main menu
         }
       }
       option=0;           // Reset the menu option after completing the selected operation
			}
			CmdLCD(CLEAR_LCD);      // Clear the LCD display before returning to the normal display
		}
	}
}
