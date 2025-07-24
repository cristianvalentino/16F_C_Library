#include <xc.h>
#include "buzzer.h"
#include "../bios.h"
#include "PIC16F18877_interrupt.h"

#define		ENCODER_SOUND								3		// milisecond
#define		KEY_SOUND									200		// milisecond
#define		ERROR_SOUND									500		// milisecond

struct {
	uint32_t timeout;
	uint8_t state;
}buzzer;

//-------------------------------------------------------------------------------------------------
// Debe cargarse con los ticks de un timmer de 1 ms para que funcione 
//-------------------------------------------------------------------------------------------------
void Buzzer_Main(void){

	switch(buzzer.state){
		//-----------------------------------------------------------------------------------------
		case BUZZER_INIT:
			Buzzer_SetDigitalMode();							// Modo digital
			Buzzer_SetLow();									// Apagado
			Buzzer_SetDigitalOutput();							// Salida!
			buzzer.timeout = 0;
			buzzer.state = BUZZER_KEY;
		break;
		//-----------------------------------------------------------------------------------------
		case BUZZER_NORMAL:
		break;
		//----------------------------------------------------------------------------------------
		case BUZZER_ENCODER:
			buzzer.timeout	= Ticks() + ENCODER_SOUND;			// set timer
			buzzer.state	= BUZZER_NORMAL_WAIT;				// voy a espera
			Buzzer_SetHigh();									// enciende buzzer
		break;
		//----------------------------------------------------------------------------------------
		case BUZZER_KEY:
			buzzer.timeout	= Ticks() + KEY_SOUND;				// set timer
			buzzer.state	= BUZZER_NORMAL_WAIT;				// voy a espera
			Buzzer_SetHigh();									// enciende buzzer
		break;
		//----------------------------------------------------------------------------------------
		case BUZZER_NORMAL_WAIT:
			if(buzzer.timeout < Ticks()){						// paso el tiempo?
				Buzzer_SetLow();								// Apaga buzzer
				buzzer.state	= BUZZER_NORMAL;				// paso a inactivo
			}
		break;
		//----------------------------------------------------------------------------------------
		case BUZZER_ERROR:
			if(buzzer.timeout < Ticks()){						// paso el tiempo?
				buzzer.timeout	= Ticks() + ERROR_SOUND;		// set timer
				buzzer.state	= BUZZER_ERROR_LOOP;			// voy a error loop
				Buzzer_SetHigh();								// enciende buzzer
			}
		break;
		//----------------------------------------------------------------------------------------
		case BUZZER_ERROR_LOOP:
			if(buzzer.timeout < Ticks()){						// paso el tiempo?
				buzzer.timeout	= Ticks() + ERROR_SOUND;		// set timer
				buzzer.state	= BUZZER_ERROR;					// voy a error loop
				Buzzer_SetHigh();								// enciende buzzer
			}
		break;
	}
}
//-------------------------------------------------------------------------------------------------
// buzzer - ENCIENDE EL buzzer Y inicia estado
//-------------------------------------------------------------------------------------------------
void Buzzer_Set(uint8_t state){
	buzzer.state = state;
}
