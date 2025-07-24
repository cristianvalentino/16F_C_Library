#ifndef PIC16F8877_interrupt_H
#define PIC16F8877_interrupt_H

#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)



	void Timer2_Initialize(void);
	unsigned long Ticks(void);
	void Timer2_Interrupt(void);
	
#endif