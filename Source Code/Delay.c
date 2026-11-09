#include<LPC21xx.h>
#include"types.h"
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
