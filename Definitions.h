#include "Defines.h"  // Include the header file containing macro definitions, data types, and hardware configurations.

// ADC FUNCTION DECLARATIONS
void Init_ADC(void);                   // Function prototype to initialize the ADC module.
void Read_ADC(u32,f32 *eAR,u32 *);    // Function prototype to read ADC values and return the converted result.

// DELAY FUNCTION DECLARATIONS
void delay_us(u32);                     // Function prototype to generate a delay in microseconds.
void delay_ms(u32);                     // Function prototype to generate a delay in milliseconds.
void delay_s(u32);                      // Function prototype to generate a delay in seconds.

// KEYPAD (KPM) FUNCTION DECLARATIONS
void InitKPM(void);                     // Function prototype to initialize the 4x4 matrix keypad.
u8 ColScan(void);                       // Function prototype to scan the keypad columns.
u8 RowCheck(void);                      // Function prototype to check which keypad row is pressed.
u8 ColCheck(void);                      // Function prototype to check which keypad column is pressed.
u8 KeyScan(void);                       // Function prototype to identify the pressed keypad key.
u32 ReadNum(void);                      // Function prototype to read a numeric value entered through the keypad.

// LCD FUNCTION DECLARATIONS
void WriteLCD(u8 data);                 // Function prototype to send data to the LCD.
void CmdLCD(u8 cmd);                    // Function prototype to send a command to the LCD.
void CharLCD(u8 ascii);                 // Function prototype to display a single ASCII character on the LCD.
void InitLCD(void);                     // Function prototype to initialize the LCD.
void StrLCD(u8* str);                   // Function prototype to display a string on the LCD.
void U32LCD(u32 n);                     // Function prototype to display an unsigned integer on the LCD.
void BuildCGRAM(u8* ,u8);              	// Function prototype to create custom characters in LCD CGRAM.

// RTC FUNCTION DECLARATIONS
void RTC_Init(void);                    // Function prototype to initialize the RTC module.
void GetRTCTimeInfo(s32 *,s32 *,s32 *); // Function prototype to get hours, minutes, and seconds from the RTC.
void DisplayRTCTime(u32,u32,u32);       // Function prototype to display hours, minutes, and seconds on the LCD.
void GetRTCDateInfo(s32 *,s32 *,s32 *); // Function prototype to get date, month, and year from the RTC.
void DisplayRTCDate(u32,u32,u32);       // Function prototype to display date, month, and year on the LCD.
void SetRTCTimeInfo(u32,u32,u32);       // Function prototype to set hours, minutes, and seconds in the RTC.
void SetRTCDateInfo(u32,u32,u32);       // Function prototype to set date, month, and year in the RTC.
void DisplayRTCTimeDelay(s32,s32,s32);  // Function prototype to display RTC time with a delay adjustment.
void GetRTCDay(s32 *);                  // Function prototype to get the day of the week from the RTC.
void DisplayRTCDay(u32);                // Function prototype to display the day of the week on the LCD.
void SetRTCDay(u32);                    // Function prototype to set the day of the week in the RTC.
void DisplayRTCTime_delay(s32,s32);     // Function prototype to display minutes and seconds with a delay adjustment.
