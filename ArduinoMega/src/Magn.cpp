#include "../include/Magn.h"

const int QMC5883P_ADDR = 0x2C;

const int MODE_REG   = 0x0A;
const int CONFIG_REG = 0x0B;
const int X_LSB_REG  = 0x01;
const int STATUS_REG = 0x09;

int16_t x, y, z;
float angle;

void Magn::Init(void)
{
	Wire.begin();
  
	Wire.beginTransmission(QMC5883P_ADDR);
 	Wire.write(MODE_REG);
 	Wire.write(0xCF);
 	Wire.endTransmission();

 	Wire.beginTransmission(QMC5883P_ADDR);
 	Wire.write(CONFIG_REG);
 	Wire.write(0x08);
 	Wire.endTransmission();
}

float Magn::Angle(void)
{
  
	Wire.beginTransmission(QMC5883P_ADDR);
	Wire.write(X_LSB_REG);
	Wire.endTransmission(false);
	Wire.requestFrom(QMC5883P_ADDR, 6);

	if (Wire.available() == 6) {
		byte x_lsb = Wire.read();
		byte x_msb = Wire.read();
		byte y_lsb = Wire.read();
		byte y_msb = Wire.read();
		byte z_lsb = Wire.read();
		byte z_msb = Wire.read();
    	
		x = (int16_t)((x_msb << 8) | x_lsb);
		y = (int16_t)((y_msb << 8) | y_lsb);
		z = (int16_t)((z_msb << 8) | z_lsb);
	}
	angle = atan2(y, x) * 180.0 / PI;

	if (angle < 0)
		angle += 360;

	return angle;
}
