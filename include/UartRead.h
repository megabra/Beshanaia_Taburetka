#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

namespace arduino
{
	void ReadInfo(int &var1, int &var2, float &var3);
	void UartInit(void);
}
