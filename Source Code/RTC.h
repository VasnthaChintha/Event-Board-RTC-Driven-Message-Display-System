#include"types.h"
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
