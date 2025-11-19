#pragma once
#include <Arduino.h>
#include <TELEOP.h>

class controller
{
public:
	void SetInfo(void);
	void GetInfo(void);
	bool CheckController(void);
	int LY;
	int LX;
	int RY;
	int RX;
private:
	int deadzone(int val);
};
