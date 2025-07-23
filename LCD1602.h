#ifndef LCD1602_H
#define LCD1602_H

//---------------------------------------------------------------------------------------
//		Comandos del LCD
//---------------------------------------------------------------------------------------
#define CLEAR						0x01		// limpieza del display
#define HOME						0x02		// Pone el cursor en 1 caracter
#define ENTRY_MODE					0x04		// ingreso de datos al display
#define INCREMENT					0x01		// cursor incrementado
#define DISPLAY_INC					0X02		// caracteres incrementados
#define DISPLAY_ONOFF				0x08		// encendido y apagado del lcd
#define DISPLAY_ON					0x04		// display encendido
#define CURSOR_ON					0x0E		// cursor encendido
#define CURSOR_OFF					0x0C		// cursor APAGADO
#define BLINK						0x01		// blink del cursor
#define DISPLAY_SHIFT				0X10		// mueve el cursor y shiftea
#define DISPLAY_SHIFTC				0X04		// shift de caracteres
#define BITS8						0x30		// Molde de bus
#define BITS4						0x20		// Molde de bus
#define LINES2						0x08		// displays de 2 y cuatro lineas
#define LINE1						0x80		// Linea 1
#define LINE2						0xC0		// Linea 2
#define LINE3						0x94		// Linea 3
#define LINE4						0xD4		// Linea 4
#define SHIFT_CURSOR_I				0x10		// cursor LCD -1
#define SHIFT_CURSOR_D				0x14		// cursor LCD +1
#define CURSOR_BLINK				0x0F

#define CARACTERES                  20
#define LINEAS                      4


char LCD_buffer[(CARACTERES+1)*LINEAS];

void LCD_Create(void);
void LCD_WriteComand( unsigned char byte );
void LCD_WriteData( unsigned char byte );
void LCD_Printf(const char *array);

void lcd_printf(const char *format, ...);
#endif