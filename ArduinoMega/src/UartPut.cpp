#include "../include/UartPut.h"

const uint8_t rx = 19;
const uint8_t tx = 18;

SoftwareSerial mySerial(rx, tx);

void UltraDigit::UartInit(void)
{
	mySerial.begin(9600);
}

void UltraDigit::PutInfo(unsigned short val)
{
	uint8_t buf1 = val / 255;
	uint8_t buf2 = val % 255;
	
	mySerial.write(buf1);
	mySerial.write(buf2);
}
