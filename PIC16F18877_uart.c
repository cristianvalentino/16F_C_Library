#include <xc.h>
#include <stdint.h>
#include "PIC16F18877_uart.h"

//-------------------------------------------------------------------------------------------------
//		Configuración del UART
//-------------------------------------------------------------------------------------------------
void EUSART_Initialize(void) {
	// 1. Configurar pines
	RXPPS = 0xA;									//	RB2->EUSART:RX;
	RB3PPS = 0x10;									//	RB3->EUSART:TX;

	// 2. Configurar baud rate (115200 a 32MHz)
	SPBRGH = 0;
	SPBRG = 16;										//	Cálculo: (32,000,000/(4*115200))-1 = 16.36

	
    //ABDEN disabled; WUE disabled; BRG16 16bit_generator; SCKP Non-Inverted; 
    BAUD1CON = 0x48; 
    //ADDEN disabled; CREN enabled; SREN disabled; RX9 8-bit; SPEN enabled; 
    RC1STA = 0x90; 
    //TX9D 0x0; BRGH hi_speed; SENDB sync_break_complete; SYNC asynchronous; TXEN enabled; TX9 8-bit; CSRC client; 
    TX1STA = 0x26; 
    //SPBRGL 64; 
    SP1BRGL = 0x40; 
    //SPBRGH 3; 
    SP1BRGH = 0x3; 



	// 3. Configurar registros de control
	TXSTAbits.SYNC = 0;								//	Modo asíncrono
	TXSTAbits.BRGH = 1;								//	High baud rate
	RCSTAbits.SPEN = 1;								//	Habilitar puerto serial
	TXSTAbits.TXEN = 1;								//	Habilitar transmisión
	RCSTAbits.CREN = 1;								//	Habilitar recepción
}
//-------------------------------------------------------------------------------------------------
//		Enviar un carácter por UART
//-------------------------------------------------------------------------------------------------
void UART_Write(char data) {
	while(!TXIF);  // Esperar hasta que el buffer esté libre
	TXREG = data;
}
//-------------------------------------------------------------------------------------------------
//		Enviar una cadena por UART
//-------------------------------------------------------------------------------------------------
void UART_Write_Text(const char *text) {
	while(*text) {
		UART_Write(*text++);
	}
}
//-------------------------------------------------------------------------------------------------
//		Función necesaria para printf
//-------------------------------------------------------------------------------------------------
void putch(char data) {
	UART_Write(data);
}
//-------------------------------------------------------------------------------------------------
//		Rutina de interrupción RX UART
//-------------------------------------------------------------------------------------------------
void __interrupt() ISR() {
	if(RCIF) {
		static uint8_t buffer[10], idx = 0;
		buffer[idx++] = RCREG;
		
		// Verificar si es un comando de touch (0x5A 0xA5 ...)
		if(idx >= 2 && buffer[0] == 0x5A && buffer[1] == 0xA5) {
			// Procesar comando de touch
			// Los switches enviarán su estado cuando cambien
		}
		
		if(idx >= 10) idx = 0;
	}
}