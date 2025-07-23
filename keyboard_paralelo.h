#ifndef keyboard_paralelo_H
#define keyboard_paralelo_H


// key map

#define MENU								0B0000000000000001
#define DECREMENTO							0B0000000000000010
#define INCREMENTO							0B0000000000000100
#define CANCELAR							0B0000000000001000
#define ACEPTAR								0B0000000000010000
#define PAD_IR								0B0000000001000000
#define PAD_WHITE							0B0000000010000000
#define PADC								0B0000000100000000
#define PADD								0B0000001000000000


void Keyboard_Paralelo(void);
unsigned char Get_Keyboard_Paralelo(void);
#endif