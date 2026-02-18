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
	int MG;
private:
	void SetWheels(int ly, int lx, int rx, int r2, float &KofL1R2, float &KofL2R1, float &Rotate, float &GlobalKof);
	void SetGraber(int ly, int r2, float &GloabalKof);
	int deadzone(int val);
	int ly;
	int lx;
	//int ry;
	int rx;
	int r2;
	float KofL1R2 = 0;
	float KofL2R1 = 0;
	float Rotate = 0;
	float GlobalKof = 0;
};
