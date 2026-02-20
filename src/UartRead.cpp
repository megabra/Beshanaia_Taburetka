#include "../include/UartRead.h"

const uint8_t RX = 9;
const uint8_t TX = 2;

SoftwareSerial mySerial(RX, TX);

void arduino::UartInit(void)
{
	mySerial.begin(9600);
}

void arduino::ReadInfo(int &var1, int &var2, float &var3)
{
	byte receivedBytes[4];

	if(mySerial.available() >= 6) {
		var1 = mySerial.read() == 1; // byte
		var2 = mySerial.read() == 1; // byte

		// float
		for(int i = 0; i < 4; i++) {
			receivedBytes[i] = mySerial.read();
		}

		memcpy(&var3, receivedBytes, 4);

	}
}
