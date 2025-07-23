#ifndef PIC16F8877_interrupt_H
#define PIC16F8877_interrupt_H

	void Timer2_Initialize(void);
	unsigned long Ticks(void);
	void Timer2_Interrupt(void);
	
#endif