
#include "../include/ControllerStick.h"

PS4 ps4;

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
	ly = deadzone(ps4.Stick(LY));
	lx = deadzone(ps4.Stick(LX));
	ry = deadzone(ps4.Stick(RY));
	rx = deadzone(ps4.Stick(RX));
}

void controller::GetInfo() // print info
{
	Serial.print("LX  =  ");
	Serial.print(lx);
	Serial.print("\tLY  =  ");
	Serial.println(ly);
	Serial.print("RX  =  ");
	Serial.print(rx);
	Serial.print("\tRY  =  ");
	Serial.println(ry);
}

bool controller::CheckController(void) // checking controller
{
	ps4.getPS4();
	if (ps4.Connected)
	{
		return 1;
	}
	else
	{
		delay(2000);
		Serial.println("ERROR - controller doesn't conected");
		return 0;
	}
}
