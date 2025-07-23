#include "../CPUPIC16F18877.X/mcc_generated_files/system/system.h"


struct {
	uint8_t key;
	uint8_t state;
	uint32_t debounce;
}key;


uint8_t Get_Keyboard_Paralelo(void){
	uint8_t k;
	if(key.key){
		k = key.key;
		key.key = 0;
		return k;
	}
	return 0;
}


void Keyboard_Paralelo(void){

	if(key.debounce < Ticks()){
		switch(key.state){
			case 0:
				printf("Inicializado Teclado paralelo\n\r");
				Sw_Cancel_SetDigitalMode();
				Sw_Cancel_SetDigitalInput();
				Sw_Acepta_SetDigitalMode();
				Sw_Acepta_SetDigitalInput();
				Sw_Increment_SetDigitalMode();
				Sw_Increment_SetDigitalInput();
				Sw_Decrement_SetDigitalInput();
				Sw_Decrement_SetDigitalMode();
				Sw_Menu_SetDigitalMode();
				Sw_Menu_SetDigitalInput();				
				Sw_PAD_IR_SetDigitalMode();
				Sw_PAD_IR_SetDigitalInput();
				Sw_Pad_White_SetDigitalMode();
				Sw_Pad_White_SetDigitalInput();
				key.state = 1;
			break;
			case 1:
				     if(!Sw_Cancel_GetValue())		{ key.key = 'C'; key.debounce = Ticks()+500; printf("Teclado = Cancelar\n\r");}
				else if(!Sw_Acepta_GetValue())		{ key.key = 'A'; key.debounce = Ticks()+500; printf("Teclado = Aceptar\n\r");}
				else if(!Sw_Menu_GetValue())		{ key.key = 'M'; key.debounce = Ticks()+500; printf("Teclado = Menu\n\r");}
				else if(!Sw_Increment_GetValue())	{ key.key = '+'; key.debounce = Ticks()+500; printf("Teclado = Incrementar\n\r");}
				else if(!Sw_Decrement_GetValue())	{ key.key = '-'; key.debounce = Ticks()+500; printf("Teclado = Decrementar\n\r");}
				else if(!Sw_PAD_IR_GetValue())		{ key.key = '1'; key.debounce = Ticks()+500; printf("Teclado = Pad IR\n\r");}
				else if(!Sw_Pad_White_GetValue())	{ key.key = '2'; key.debounce = Ticks()+500; printf("Teclado = Pad Blanco\n\r");}
				key.state = 2;
			break;
			case 2:
				if(!key.key && key.debounce < Ticks() ){
					key.state = 1;
				}
			break;
		}
	}
}
