#include "Display_I2C.h"

uint8_t backlight = 0;

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void LCD_I2C_Backligth_Set(uint8_t b){
	if(b)	backlight = BACKLIGHT;
	else 	backlight = 0;
	PCF8574_Write(backlight);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void PCF8574_Write(uint8_t byte){
	I2C_Start();
	I2C_Write(PCF8574_ADDRESS);
	I2C_Write(byte);
	I2C_Stop();
}

//-------------------------------------------------------------------------------------------------
//	Enviar un byte de comando al controlador hitachi HD44780
//-------------------------------------------------------------------------------------------------
void LCD_I2C_WriteCommand(uint8_t command){ 
				
	PCF8574_Write((uint8_t)( command & 0xF0 ) | PIN_EN | backlight);	
	PCF8574_Write( backlight );
	PCF8574_Write((uint8_t)( command << 4 )   | PIN_EN | backlight);
	PCF8574_Write( backlight );
	__delay_ms(10);
}

//-------------------------------------------------------------------------------------------------
//	Enviar un byte de datos al controlador hitachi HD44780
//-------------------------------------------------------------------------------------------------
void LCD_I2C_WriteData(uint8_t data){ 

	PCF8574_Write((uint8_t)( data & 0xF0 ) | PIN_EN | PIN_RS | backlight);	
	PCF8574_Write( PIN_RS | backlight );
	PCF8574_Write((uint8_t)( data << 4 )   | PIN_EN | PIN_RS | backlight);
	PCF8574_Write( PIN_RS | backlight );
}

//-------------------------------------------------------------------------------------------------
//	Inicializa el Display I2C
//-------------------------------------------------------------------------------------------------
void LCD_I2C_Init(void){
	__delay_ms(15);							// Esperar a que el LCD se inicie
	LCD_I2C_WriteCommand(0x03);
	__delay_ms(5);
	LCD_I2C_WriteCommand(0x03);
	__delay_us(150);
	LCD_I2C_WriteCommand(0x03);
	LCD_I2C_WriteCommand(0x02);									// Configurar en modo de 4 bits
	LCD_I2C_WriteCommand(0x28);									// Configurar en modo de 2 l�neas y 5x8 puntos
	LCD_I2C_WriteCommand(0x0C);									// Encender el display, sin cursor
	LCD_I2C_WriteCommand(0x06);			// Incrementar el cursor
	LCD_I2C_WriteCommand(0x01);			// Limpiar el display
	__delay_ms(2);
	LCD_I2C_Printf("LCD I2C Start !!");							// Imprime en la primera linea
	LCD_I2C_Backligth_SetOn();
	__delay_ms(1000);
}



//TEXTO
void LCD_I2C_Printf(char* string){
uint8_t	line=0; 
	LCD_I2C_WriteCommand(HOME);
	while(*string){
		// New Line??
		if(*string =='\n'){
			if(line==0)			LCD_I2C_WriteCommand(LINE2);
			else if(line==1)	LCD_I2C_WriteCommand(LINE3);
			else if(line==2)	LCD_I2C_WriteCommand(LINE4);
			else if(line==3)	break;
			line++;
		}
		else LCD_I2C_WriteData(*string);
		string++;
	}
}