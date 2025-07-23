#include "16F8877_interrupt.h"


void INTERRUPT_Initialize (void){
	// Clear the interrupt flag
	// Set the external interrupt edge detect
	EXT_INT_InterruptFlagClear();   
	EXT_INT_risingEdgeSet();
	// Set Default Interrupt Handler
	INT_SetInterruptHandler(INT_DefaultInterruptHandler);
	// EXT_INT_InterruptEnable();

}