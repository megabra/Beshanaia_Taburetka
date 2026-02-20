/*
programm for put info into tetrix
*/

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

namespace arduino
{
	void PutInfo(bool var1, bool var2, float var3);
	void UartInit(void);
}
