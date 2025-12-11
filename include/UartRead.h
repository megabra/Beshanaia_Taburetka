#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

namespace UltraDigit
{
	bool checking(void);
	unsigned short ReadInfo(void);
	void UartInit (void);
}
