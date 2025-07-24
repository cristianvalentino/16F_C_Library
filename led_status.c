#include <xc.h>
#include "led_status.h"
#include "../pinout.h"
#include "PIC16F18877_interrupt.h"


#define _XTAL_FREQ 32000000U

#define INIT            0
#define NORMAL			1


struct {
	uint32_t timeout;
	uint8_t state;
}led_status;


//-------------------------------------------------------------------------------------------------
// Debe cargarse con los ticks de un timmer de 1 ms para que funcione 
//-------------------------------------------------------------------------------------------------
void Led_Status(void){
	switch(led_status.state){
		//-----------------------------------------------------------------------------------------
		case INIT:

			Status_Led_SetDigitalMode();						// Modo digital
			Status_Led_SetLow();								// Encendido
			Status_Led_SetDigitalOutput();						// Salida!
			led_status.timeout = Ticks()+100;					// Set time Led hi
			led_status.state = NORMAL;

		break;
		//----------------------------------------------------------------------------------------
		case NORMAL:
			if(led_status.timeout < Ticks() ){
				if(Status_Led_GetValue()){
					Status_Led_SetLow();						// Apapgo
					led_status.timeout = Ticks()+20;			// Set time Led lo
				}else{
					Status_Led_SetHigh();						// Encendido
					led_status.timeout = Ticks()+980;			// Set time Led hi
				}
			}
		break;
	}
}
//-------------------------------------------------------------------------------------------------
// buzzer - ENCIENDE EL buzzer Y inicia estado
//-------------------------------------------------------------------------------------------------
void Led_StatusSet(uint8_t state){
	led_status.state = state;
}
