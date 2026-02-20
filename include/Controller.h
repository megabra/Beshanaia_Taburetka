#pragma once
#include <Arduino.h>
#include <TELEOP.h> // controller lib
#include <math.h>


class controller
{
public:
	void SetInfo(void);
	void GetInfo(void);
	bool CheckController(void);
	int ML1; // val of back left motor
	int ML2; // val of top left motor
	int MR1; // val of back right motor
	int MR2; // val of top right motor
	int MG; // val of grabber motor
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
