#include "../include/Gyro.h"

namespace Gyro{
	MPU6050 mpu;

	float angleZ = 0;
	float gyroZrate = 0;
	float gyroZbias = 0;
}
unsigned long timer = 0;

void Gyro::Init(float a)
{
	Wire.begin();
 
	//MPU6050
	mpu.initialize();
 
	if (!mpu.testConnection()) {
		Serial.println("error");
		while (1);
	}
 
	Serial.println("calibrate");
	calibrateGyroZ();
	Serial.println("calibrate is done");

	timer = micros();
	angleZ = a; //start angle
}

void Gyro::calibrateGyroZ(void)
{
	long sum = 0;
	for (int i = 0; i < calibrationSamples; i++) {
		int16_t gx, gy, gz;
		mpu.getRotation(&gx, &gy, &gz);
		sum += gz;
		delay(3);
	}
	gyroZbias = sum / (float)calibrationSamples;
 
	Serial.println(gyroZbias);
}

float Gyro::normalizeAngle(float angle)
{
	angle = fmod(angle, 360.0);
	if (angle < 0) angle += 360.0;
	return angle;
}

float Gyro::Angle(void)
{
	int16_t gx, gy, gz;
	mpu.getRotation(&gx, &gy, &gz);

	float gyroRawZ = (gz - gyroZbias) / 131.0;

	gyroZrate = gyroZrate * 0.9 + gyroRawZ * 0.1;

	unsigned long now = micros();
	float dt = (now - timer) / 1000000.0;
	timer = now;

	if (dt > 0.1) dt = 0.1; 

	angleZ += gyroZrate * dt;

	angleZ = normalizeAngle(angleZ);	

	return angleZ;
}
