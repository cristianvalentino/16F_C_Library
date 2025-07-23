#include <xc.h>
#include "16F18877_timer2.h"

uint32_t timer2_ticks = 0;

//-------------------------------------------------------------------------------------------------
// TMR2_Initialize 1 ms
//-------------------------------------------------------------------------------------------------
void TMR2_Initialize(void){
	T2CLKCON = (1 << _T2CLKCON_T2CS_POSN);			// T2CS FOSC/4
	T2HLT = (0 << _T2HLT_T2MODE_POSN)				// T2MODE Software control
		| (0 << _T2HLT_T2CKSYNC_POSN)				// T2CKSYNC Not Synchronized
		| (0 << _T2HLT_T2CKPOL_POSN)				// T2CKPOL Rising Edge
		| (0 << _T2HLT_T2PSYNC_POSN);				// T2PSYNC Not Synchronized

	T2RST = (0 << _T2RST_T2RSEL_POSN);				// T2RSEL T2CKIPPS pin
	T2PR = 0xFF;									// Period 0.001024s; Timer Prescaled Frequency 1000000Hz; Count 255; Postscaler 1:4; 
	T2TMR = 0x0;	
	PIR4bits.TMR2IF = 0;

	T2CON = (3 << _T2CON_T2CKPS_POSN)				// T2CKPS 1:8
		| (1 << _T2CON_TMR2ON_POSN)					// TMR2ON on
		| (3 << _T2CON_T2OUTPS_POSN);				// T2OUTPS 1:4

	T2CONbits.TMR2ON = 1;							// Start Timer 2
}


//-------------------------------------------------------------------------------------------------
// Ticks del timer
// Returns the number of ticks since the last reset
//-------------------------------------------------------------------------------------------------
uint32_t Ticks(void){
	return timer2_ticks;
}
//-------------------------------------------------------------------------------------------------
// TMR2_ISR
// Timer 2 Interrupt Service Routine
//-------------------------------------------------------------------------------------------------
void TMR2_ISR(void) {
	if (PIR4bits.TMR2IF) {
		PIR4bits.TMR2IF = 0; // Clear Timer 2 Interrupt Flag
		timer2_ticks++;      // Increment the tick count
	}
}