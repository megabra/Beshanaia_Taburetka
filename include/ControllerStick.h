#pragma once
#include <Arduino.h>
#include <TELEOP.h>
#include <math.h>


class controller
{
public:
	void SetInfo(void);
	void GetInfo(void);
	bool CheckController(void);
	int ML1;
	int ML2;
	int MR1;
	int MR2;
private:
	int deadzone(int val);
	int ly;
	int lx;
	int ry;
	int rx;
	double KofL1R2 = 0;
	double KofL2R1 = 0;
	double Rotate = 0;
	double GlobalKof = 0;
};
