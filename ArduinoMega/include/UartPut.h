#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

namespace UltraDigit
{
	bool checking(void);
	void PutInfo(unsigned short val);
	void UartInit(void);
}
