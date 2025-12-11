#include "../include/UartRead.h"

const uint8_t rx = 9;
const uint8_t tx = 2;

SoftwareSerial mySerial(rx, tx);

void UltraDigit::UartInit(void)
{
	mySerial.begin(9600);
}

unsigned short UltraDigit::ReadInfo(void)
{
	uint16_t val;
	
	if (mySerial.available())
		val = mySerial.read() * 255;
	if (mySerial.available())
		val += mySerial.read();
	
	return val;
}
