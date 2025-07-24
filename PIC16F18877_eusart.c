#include <xc.h> // include processor files - each processor file is guarded.
#include "PIC16F18877_eusart.h"




void Create_EUSART(void){

	PIE3bits.RCIE = 0;   
	PIE3bits.TXIE = 0; 

	//ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; 
	BAUD1CON = 0x48; 
	//ADDEN disabled; CREN enabled; SREN disabled; RX9 8-bit; SPEN enabled; 
	RC1STA = 0x90; 
	//TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
	TX1STA = 0x26; 
	SP1BRGL = 0x44; 
	SP1BRGH = 0x0; 
	PIE3bits.RCIE = 1; 
}