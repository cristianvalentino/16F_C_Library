#include "LCD1602.h"

#define LCD_port_WR							LATD
#define LCD_port_RD							PORTD
#define LCD_port_DD							TRISD

#ifndef LCD_RS_SetHigh
	#define LCD_RS_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
	#define LCD_RS_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
	#define LCD_RS_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
	#define LCD_RS_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#endif

#ifndef LCD_RW_SetHigh
	#define LCD_RW_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
	#define LCD_RW_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
	#define LCD_RW_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
	#define LCD_RW_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#endif

#ifndef LCD_EN_SetHigh
	#define LCD_EN_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
	#define LCD_EN_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
	#define LCD_EN_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
	#define LCD_EN_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#endif


//-------------------------------------------------------------------------------------------------
//	DATO AL DISPLAY
//-------------------------------------------------------------------------------------------------
void LCD_WriteComand( unsigned char b ){

	LCD_port_WR = b;
	__delay_us(10);
	LCD_RS_SetLow();											// comando -> cero
	LCD_RW_SetLow();											// Write -> cero
	LCD_EN_SetHigh();											// enable -> uno
	__delay_us(50);												// Enable pulse width PWeh min 230ns
	LCD_EN_SetLow();											// enable -> cero
	__delay_ms(20);
}
//-------------------------------------------------------------------------------------------------
//	COMANDO AL DISPLAY
//-------------------------------------------------------------------------------------------------
void LCD_WriteData( unsigned char byte ){
	LCD_port_WR = byte;
	__delay_us(10);
	LCD_RS_SetHigh();											// comando -> uno
	LCD_RW_SetLow();											// Write -> cero
	LCD_EN_SetHigh();											// enable -> uno
	__delay_us(30);												// Enable pulse width PWeh min 230ns
	LCD_EN_SetLow();											// enable -> cero
	__delay_us(10);
}

//-------------------------------------------------------------------------------------------------
//	IMPRIME UN STRING EN EL DISPLAY
//-------------------------------------------------------------------------------------------------
void LCD_Printf(const char *array){
unsigned char line;

	LCD_WriteComand(HOME);
	line=0; 
	while(*array){
		// New Line??
		if(*array=='\n'){
			if(line==0)			LCD_WriteComand(LINE2);
			else if(line==1)	LCD_WriteComand(LINE3);
			else if(line==2)	LCD_WriteComand(LINE4);
			else if(line==3)	break;
			line++;
		}
		else LCD_WriteData(*array);
		array++;
	}
}

//-------------------------------------------------------------------------------------------------
//	INICIALIZA EL DISPLAY
//-------------------------------------------------------------------------------------------------
void LCD_Create(void){

	LCD_port_WR = 0;												// puerto a cero
	LCD_port_DD = 0;												// puerto como salida;
	LCD_RS_SetHigh();
	LCD_RW_SetHigh();
	LCD_EN_SetHigh();

	LCD_RS_SetDigitalOutput();										// rs como salida
	LCD_RW_SetDigitalOutput();										// rs como salida
	LCD_EN_SetDigitalOutput();										// rs como salida
	
	__delay_ms(15);
	
	LCD_WriteComand(0x38);										// Initialization of 16X2 LCD in 8bit mode
	LCD_WriteComand(0x0C);										// Display ON Cursor OFF
	LCD_WriteComand(0x06);										// Auto Increment cursor
	LCD_WriteComand(0x01);										// clear display
	LCD_WriteComand(0x80);										// cursor at home position
	LCD_WriteComand(0x01);										// clear display
	LCD_Printf("Init LCD !!        ");							// Imprime en la primera linea
}

