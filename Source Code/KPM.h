#include "types.h"
// KEYPAD (KPM) FUNCTION DECLARATIONS
void InitKPM(void);                     // Function prototype to initialize the 4x4 matrix keypad.
u8 ColScan(void);                       // Function prototype to scan the keypad columns.
u8 RowCheck(void);                      // Function prototype to check which keypad row is pressed.
u8 ColCheck(void);                      // Function prototype to check which keypad column is pressed.
u8 KeyScan(void);                       // Function prototype to identify the pressed keypad key.
u32 ReadNum(void);                      // Function prototype to read a numeric value entered through the keypad.
