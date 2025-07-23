#include "../../system/system.h"

//-------------------------------------------------------------------------------------------------
//		OneWire
//-------------------------------------------------------------------------------------------------
void OneWireHigh(){
	One_Wire_SetDigitalOutput();								// Set as output
	One_Wire_SetHigh();											// Set high 
}

//-------------------------------------------------------------------------------------------------
//		OneWire Release
//-------------------------------------------------------------------------------------------------
void OneWireRelease(){
	One_Wire_SetDigitalOutput();								// Set as output
	One_Wire_SetLow();											// Set low 
}

//-------------------------------------------------------------------------------------------------
//		OneWire Read
//-------------------------------------------------------------------------------------------------
unsigned char OneWireRead(){
	return One_Wire_GetValue();
}

//-------------------------------------------------------------------------------------------------
//		OneWire Reset
//-------------------------------------------------------------------------------------------------
unsigned int OneWireReset(){
	OneWireRelease();
	__delay_us(240); // 480uS Delay
	__delay_us(240);
	OneWireHigh();
	__delay_us(70); // wait 70 uS before reading
	unsigned int OW = OneWireRead(); // check for OneWire
	__delay_us(205); // 410 uS delay
	__delay_us(205);
	OneWireHigh(); // give bus back to OneWire
	return OW; 
}

//-------------------------------------------------------------------------------------------------
//		OneWire Write Bit
//-------------------------------------------------------------------------------------------------
void OneWireWriteBit(unsigned char b){
	if(b){
		OneWireRelease();
		__delay_us(6); // wait 6uS
		OneWireHigh();
		__delay_us(64); // wait 64uS
	}
	else{
		OneWireRelease();
		__delay_us(60); // wait 60uS
		OneWireHigh();
		__delay_us(10); // wait 10uS
	}
}

//-------------------------------------------------------------------------------------------------
//		OneWire Read Bit
//-------------------------------------------------------------------------------------------------
unsigned char OneWireReadBit(){
	OneWireRelease();
	__delay_us(6); // wait 6uS
	OneWireHigh();
	__delay_us(9); // wait 9uS
	unsigned char out = OneWireRead();
	__delay_us(55); // wait 55uS
	return out;
}

//-------------------------------------------------------------------------------------------------
//		OneWire Write Byte
//-------------------------------------------------------------------------------------------------
void OneWireWriteByte(unsigned char b){
	for(int i = 0; i < 8; i++){
		OneWireWriteBit(b & 0x01); // send LS bit first 
		b = b >> 1;
	}
}

//-------------------------------------------------------------------------------------------------
//		OneWire Read Byte
//-------------------------------------------------------------------------------------------------
unsigned char OneWireReadByte(void){
	unsigned char out; 
	for(int i = 0; i < 8; i++){ // read in LS bit first
		out = out >> 1; // get out ready for next bit
		if(OneWireReadBit() & 0x01) // if its a one 
			out = out | 0x80; // place a 1 
	}
	return out;
}