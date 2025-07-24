#ifndef PINOUT_H
#define	PINOUT_H

	#include <xc.h> // include processor files - each processor file is guarded.  
	#define Buzzer_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
	#define Buzzer_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
	#define Buzzer_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
	#define Buzzer_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)


#endif

