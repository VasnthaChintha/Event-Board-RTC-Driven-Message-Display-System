// Define user-defined data types using the typedef keyword
typedef unsigned char u8;   // Define u8 as an alias for unsigned char (8-bit unsigned integer)
typedef signed char s8;     // Define s8 as an alias for signed char (8-bit signed integer)
typedef unsigned int u32;   // Define u32 as an alias for unsigned int (32-bit unsigned integer)
typedef signed int s32;     // Define s32 as an alias for signed int (32-bit signed integer)
typedef float f32;          // Define f32 as an alias for float (floating-point data type)
typedef double f64;         // Define f64 as an alias for double (double-precision floating-point data type)

#define SETBIT(WORD,BP) (WORD|=(1<<BP))		// Macro to set a specific bit in a register (make the bit HIGH)
#define CLRBIT(WORD,BP) (WORD&=~(1<<BP))	// Macro to clear a specific bit in a register (make the bit LOW)
#define STATUSBIT(WORD,BP) ((WORD>>BP)&1) // Macro to read the status of a specific bit (returns 0 or 1)
#define WRITEBIT(WORD,BP,BIT) (WORD=((WORD&~(1<<BP))|(BIT<<BP))) 	// Macro to write a specified value (0 or 1) to a particular bit
#define WRITENIBBLE(WORD,SBP,NIBBLE) (WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))) 	// Macro to write a 4-bit nibble at the specified bit position
#define READNIBBLE(WORD,SBP) ((WORD>>SBP)&15)// Macro to read a 4-bit nibble from the specified bit position
#define WRITEBYTE(WORD,SBP,BYTE) (WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))) // Macro to write an 8-bit byte at the specified bit position
#define WRITEHWORD(WORD,SBP,HWORD) (WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))) // Macro to write a 16-bit half-word at the specified bit position
#define SSETBIT(WORD,BP) (WORD=1<<BP); // Macro to set a specific bit by assigning a bit mask to the register
#define SCLRBIT(WORD,BP) (WORD=1<<BP); // Macro to clear a specific bit by assigning a bit mask to the register

																												//ADC CONFIGURATION
#define FOSC 12000000          // Define the external oscillator frequency as 12 MHz
#define CCLK (5*FOSC)           // Calculate the CPU clock frequency (12 MHz × 5 = 60 MHz)
#define PCLK (CCLK/4)           // Calculate the peripheral clock frequency (60 MHz / 4 = 15 MHz)
#define ADCLK 3000000           // Define the ADC clock frequency as 3 MHz
// CLOCK DIVIDER FREQUENCY
#define CLK_DIV ((PCLK/ADCLK)-1) // Calculate the ADC clock divider value based on PCLK and ADCLK
// CHANNEL SELECTION
#define CH0 0x01                // Select ADC channel 0 (AIN0)
#define CH1 0x02                // Select ADC channel 1 (AIN1)
#define CH2 0x04                // Select ADC channel 2 (AIN2)
#define CH3 0x08                // Select ADC channel 3 (AIN3)
// POWER-DOWN CONTROL
#define PDN_BIT (1<<21)         // Set bit 21 to power up the ADC module
// ADC CLOCK DIVIDER CONFIGURATION
#define CLKDIV (CLK_DIV<<8)     // Place the calculated ADC clock divider value in ADCR bits 15:8
// START CONVERSION
#define START_CONV (1<<24)      // Set bit 24 to start the ADC conversion
// CONVERSION COMPLETION STATUS
#define DONE_BIT 31             // Bit 31 indicates whether the ADC conversion is completed
// ADC RESULT CONFIGURATION
#define RESULT 6                // Starting bit position of the 10-bit ADC conversion result
// PIN SELECTION CONFIGURATION
// PINSEL1 function masks for ADC input pins P0.27 (AIN0) to P0.30 (AIN3)
// Configure the corresponding pins to operate as ADC input channels.
#define AIN0 0x00400000         // Configure pin P0.27 as ADC channel 0 (AIN0)
#define AIN1 0x01000000         // Configure pin P0.28 as ADC channel 1 (AIN1)
#define AIN2 0x04000000         // Configure pin P0.29 as ADC channel 2 (AIN2)
#define AIN3 0x10000000         // Configure pin P0.30 as ADC channel 3 (AIN3)

															//KPM CONFIGURATION
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

															//RTC CONFIGURATION
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

															//LCD CONFIGURATION
// Define the LCD data pins, control pins, and HD44780-compatible LCD command values
// LCD PIN DEFINITIONS
#define LCD_DATA 8             // Define P0.8 to P0.15 as the 8-bit LCD data pins
#define RS 16                  // Assign P0.16 as the Register Select (RS) control pin
#define RW 17                  // Assign P0.17 as the Read/Write (RW) control pin
#define EN 18                  // Assign P0.18 as the Enable (EN) control pin
// LCD COMMAND DEFINITIONS
#define CLEAR_LCD     0X01     // Command to clear the LCD display and move the cursor to the home position
#define RET_CUR_HOME   0x02    // Command to return the cursor to the home position
#define MODE_4BIT_1LINE 0X20   // Configure the LCD in 4-bit mode with 1-line display
#define MODE_4BIT_2LINE 0x28   // Configure the LCD in 4-bit mode with 2-line display
#define MODE_8BIT_1LINE 0X30   // Configure the LCD in 8-bit mode with 1-line display
#define MODE_8BIT_2LINE 0x38   // Configure the LCD in 8-bit mode with 2-line display
#define DISP_OFF        0x08   // Turn OFF the LCD display
#define DISP_ON_CUR_OFF 0x0C   // Turn ON the display and turn OFF the cursor
#define DISP_ON_CUR_ON  0x0E   // Turn ON the display and cursor
#define DISP_ON_CUR_BLINK 0x0F // Turn ON the display with a blinking cursor
#define GOTO_LINE1_POS0   0x80 // Move the cursor to the first position of the first line
#define GOTO_LINE2_POS0   0xC0 // Move the cursor to the first position of the second line
#define GOTO_CGRAM        0x40 // Set the LCD address to access Character Generator RAM (CGRAM)
#define SHIFT_CUR_RIGHT   0x06 // Set the cursor to automatically move one position to the right after writing data
