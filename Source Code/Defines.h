#define SETBIT(WORD,BP) (WORD|=(1<<BP))		// Macro to set a specific bit in a register (make the bit HIGH)
#define CLRBIT(WORD,BP) (WORD&=~(1<<BP))	// Macro to clear a specific bit in a register (make the bit LOW)
#define STATUSBIT(WORD,BP) ((WORD>>BP)&1) // Macro to read the status of a specific bit (returns 0 or 1)
#define WRITEBIT(WORD,BP,BIT) (WORD=((WORD&~(1<<BP))|(BIT<<BP))) // Macro to write a specified value (0 or 1) to a particular bit
#define WRITENIBBLE(WORD,SBP,NIBBLE) (WORD=((WORD&~(0xf<<SBP))|(NIBBLE<<SBP))) // Macro to write a 4-bit nibble at the specified bit position
#define READNIBBLE(WORD,SBP) ((WORD>>SBP)&15) // Macro to read a 4-bit nibble from the specified bit position
#define WRITEBYTE(WORD,SBP,BYTE) (WORD=((WORD&~(0xff<<SBP))|(BYTE<<SBP))) // Macro to write an 8-bit byte at the specified bit position
#define WRITEHWORD(WORD,SBP,HWORD) (WORD=((WORD&~(0xffff<<SBP))|(HWORD<<SBP))) // Macro to write a 16-bit half-word at the specified bit position
#define SSETBIT(WORD,BP) (WORD=1<<BP); // Macro to set a specific bit by assigning a bit mask to the register
#define SCLRBIT(WORD,BP) (WORD=1<<BP); // Macro to clear a specific bit by assigning a bit mask to the register
