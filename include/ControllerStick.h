#pragma once
#include <Arduino.h>
#include <TELEOP.h>

class controller
{
public:
	void SetInfo(void);
	void GetInfo(void);
	bool CheckController(void);
	int ly;
	int lx;
	int ry;
	int rx;
private:
	int deadzone(int val);
};
