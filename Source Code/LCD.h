#include "types.h"
// LCD FUNCTION DECLARATIONS
void WriteLCD(u8 data);                 // Function prototype to send data to the LCD.
void CmdLCD(u8 cmd);                    // Function prototype to send a command to the LCD.
void CharLCD(u8 ascii);                 // Function prototype to display a single ASCII character on the LCD.
void InitLCD(void);                     // Function prototype to initialize the LCD.
void StrLCD(u8* str);                   // Function prototype to display a string on the LCD.
void U32LCD(u32 n);                     // Function prototype to display an unsigned integer on the LCD.
void BuildCGRAM(u8* ,u8);              	// Function prototype to create custom characters in LCD CGRAM.
