#include <xc.h>
#include "PIC16F18877_pwm.h"

//-------------------------------------------------------------------------------------------------
// Create PWM6 sobre un puerto especifico, si se le pasa un puerto 0, usa la salida por defecto
// Valores de la hoja de datos Tabla:
//										TABLE 13-3: PPS OUTPUT SIGNAL ROUTING OPTIONS
//-------------------------------------------------------------------------------------------------
void Create_PWM6(volatile unsigned char *port){
	*port = 0x0E; 												// no redirecciona si el puerto = 0
	PWM6CON = 0x0;												// PWMPOL active_hi; PWMEN disabled
	PWM6DCH = 0x2;												// PWMDCH 2; 
	PWM6DCL = 0x40;												// PWMDCL 1; 
	CCPTMRS1bits.P6TSEL = 0x1;
}

//-------------------------------------------------------------------------------------------------
// Setea el duty cycle del PWM6
//-------------------------------------------------------------------------------------------------
void DutyValue_PWM6(uint16_t dutyValue) {

	dutyValue = (dutyValue * 10);								// Convierte a porcentual

	PWM6DCH = (uint8_t) ((dutyValue & 0x03FCu) >> 2);			// Writing to 8 MSBs
	PWM6DCL = (uint8_t) ((dutyValue & 0x0003u) << 6);			// Writing to 2 LSBs
}

//-------------------------------------------------------------------------------------------------
// Detiene el PWM6
//-------------------------------------------------------------------------------------------------
void Stop_PWM6(void) {
	PWM6CON &= ~0x80;											// Disable PWM module
}

//-------------------------------------------------------------------------------------------------
// Inicia el PWM6
//-------------------------------------------------------------------------------------------------
void Start_PWM6(void) {
	PWM6CON |= 0x80;											// Enable PWM module

}

//-------------------------------------------------------------------------------------------------
// Create PWM7 sobre un puerto especifico, si se le pasa un puerto 0, usa la salida por defecto
// Valores de la hoja de datos Tabla:
//										TABLE 13-3: PPS OUTPUT SIGNAL ROUTING OPTIONS
//-------------------------------------------------------------------------------------------------
void Create_PWM7(volatile unsigned char *port){

	*port = 0x0F;												// redireccionamiento de puertos
	PWM7CON = 0x0;												// PWMPOL active_hi; PWMEN disabled
	PWM7DCH = 0x2;												// PWMDCH 2; 
	PWM7DCL = 0x40;												// PWMDCL 1; 
	CCPTMRS1bits.P7TSEL = 0x1;
}

//-------------------------------------------------------------------------------------------------
// Setea el duty cycle del PWM7
//-------------------------------------------------------------------------------------------------
void DutyValue_PWM7(uint16_t dutyValue) {
	
	dutyValue = (dutyValue * 10);								// Convierte a porcentual

	PWM7DCH = (uint8_t) ((dutyValue & 0x03FCu) >> 2);			// Writing to 8 MSBs
	PWM7DCL = (uint8_t) ((dutyValue & 0x0003u) << 6);			// Writing to 2 LSBs
}

//-------------------------------------------------------------------------------------------------
// Detiene el PWM7
//-------------------------------------------------------------------------------------------------
void Stop_PWM7(void) {
	PWM7CON &= ~0x80;											// Disable PWM module
}

//-------------------------------------------------------------------------------------------------
// Inicia el PWM7
//-------------------------------------------------------------------------------------------------
void Start_PWM7(void) {
	PWM7CON |= 0x80;											// Enable PWM module

}