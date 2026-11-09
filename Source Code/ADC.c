#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
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
