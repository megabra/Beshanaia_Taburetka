#pragma once

#include <Arduino.h>

#include <Wire.h>
#include <MPU6050.h>

const int calibrationSamples = 500;

const float alpha = 0.998;

namespace Gyro
{
	void Init(float a);
	float Angle(void);
	void calibrateGyroZ(void);
	float normalizeAngle(float angle);
}
