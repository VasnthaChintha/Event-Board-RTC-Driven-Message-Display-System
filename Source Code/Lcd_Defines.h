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
