#include "../include/UartPut.h"

const uint8_t RX = 17;
const uint8_t TX = 16;

SoftwareSerial mySerial(RX, TX);

void UltraDigit::UartInit(void)
{
	mySerial.begin(9600);
}

void UltraDigit::PutInfo(bool var1, bool var2, float var3)
{
	mySerial.write(int(var1));
	mySerial.write(int(var2));
	  
	byte* floatBytes = (byte*) &var3;
	for(int i = 0; i < sizeof(float); i++) {
	mySerial.write(floatBytes[i]);
        }

}
