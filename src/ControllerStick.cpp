
#include "../include/ControllerStick.h"

PS4 ps4;

int controller::deadzone(int val) // deadzone for controller
{
	const uint8_t zone = 20;
	if (val <= (128 - zone) || val >= (128 + zone))
		return val - 128;
	else
		return 0;
}

void controller::SetInfo() // Set info
{
	ly = deadzone(ps4.Stick(LY));
	lx = deadzone(ps4.Stick(LX));
	//ry = deadzone(ps4.Stick(RY));
	rx = deadzone(ps4.Stick(RX));
	
	/////////////////For wheels//////////////////
	double hypo = (sqrt((lx*lx)+(ly*ly)) > 128) ? 128 : sqrt((lx*lx)+(ly*ly));
	
	GlobalKof = hypo / 128 * 720;

	Rotate = rx / 128;

	if (hypo != 0 && Rotate != 0)
	{
		if (hypo != 0)
		{
			double sin2 = ((ly / hypo)>=0) ? (ly / hypo)*(ly / hypo) : (ly / hypo)*(ly / hypo)*-1;
			double cos2 = ((lx / hypo)>=0) ? (lx / hypo)*(lx / hypo) : (lx / hypo)*(lx / hypo)*-1;
			
			KofL1R2 =sin2+cos2; 
			KofL2R1 =sin2-cos2;
		}
		else
		{
			KofL1R2 = 0;
                        KofL2R1 = 0;
		}

		int RawL1 = (KofL1R2 + Rotate) * GlobalKof;
		int RawR2 = (KofL1R2 - Rotate) * GlobalKof;
		int RawL2 = (KofL2R1 + Rotate) * GlobalKof;
		int RawR1 = (KofL2R1 - Rotate) * GlobalKof;
	
		ML1 = (RawL1 > 720) ? 720 : (RawL1 < -720) ? -720 : RawL1;
        	MR2 = (RawR2 > 720) ? 720 : (RawR2 < -720) ? -720 : RawR2;
        	ML2 = (RawL2 > 720) ? 720 : (RawL2 < -720) ? -720 : RawL2;
        	MR1 = (RawR1 > 720) ? 720 : (RawR1 < -720) ? -720 : RawR1;
	}
	else 
	{
		KofL1R2 = 0;
                KofL2R1 = 0;

		ML1 = ML2 = MR1 = MR2 = 0;
	}
	//L1 = (Sin * |Sin| + Cos * |Cos| + rotation (max=1, min=-1)) * MaxMotorVal
	//L2 = (Sin * |Sin| - Cos * |Cos| + rotation (max=1, min=-1)) * MaxMotorVal
	//R1 = (Sin * |Sin| - Cos * |Cos| - rotation (max=1, min=-1)) * MaxMotorVal
	//R2 = (Sin * |Sin| + Cos * |Cos| - rotation (max=1, min=-1)) * MaxMotorVal
	/////////////////////////////////////////////
}

void controller::GetInfo() // print info
{
	Serial.print("LX  =  ");
	Serial.print(lx);
	Serial.print("\tLY  =  ");
	Serial.print(ly);
	Serial.print("\tRX  =  ");
	Serial.print(rx);
	//Serial.print("\tRY  =  ");
	//Serial.print(ry);
	Serial.print("\tML1  =  ");
        Serial.print(ML1);
        Serial.print("\tML2  =  ");
        Serial.print(ML2);
        Serial.print("\tMR1  =  ");
        Serial.print(MR1);
        Serial.print("\tMR2  =  ");
        Serial.print(MR2);
	Serial.print("\tK1  =  ");
        Serial.print(KofL1R2);
        Serial.print("\tK2  =  ");
        Serial.print(KofL2R1);
	Serial.print("\tRT  =  ");
	Serial.print(Rotate);
        Serial.print("\tGK  =  ");
        Serial.print(GlobalKof);
	Serial.println();
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
