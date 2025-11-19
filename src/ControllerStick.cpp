
#include "../include/ControllerStick.h"

int controller::deadzone(int val) // deadzone for controller
{
	const uint8_t zone = 20;
	if (val <= (128 - zone) || val >= (128 + zone))
		return val -= 128;
	else
		return val = 0;
}

void controller::SetInfo() // Set info
{
	LY = deadzone(ps4.Stick(LY));
	LX = deadzone(ps4.Stick(LX));
	RY = deadzone(ps4.Stick(RY));
	RX = deadzone(ps4.Stick(RX));
}

void controller::GetInfo() // print info
{
	Serial.print("LX  =  ");
	Serial.print(LX);
	Serial.print("\tLY  =  ");
	Serial.println(LY);
	Serial.print("RX  =  ");
	Serial.print(RX);
	Serial.print("RY  =  ");
	Serial.println(RY);
}

bool controller::CheckController(void) // checking controller
{
	ps4.getPS4();
	if (ps4.Connected)
	{
		Serial.println("Controller conected");
		return 1;
	}
	else
	{
		delay(2000);
		Serial.println("ERROR - controller doesn't conected");
		return 0;
	}
}