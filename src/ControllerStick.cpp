
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
	ry = deadzone(ps4.Stick(RY));
	rx = deadzone(ps4.Stick(RX));
	
	double hypo = sqrt((lx*lx)+(ly*ly));
	
	if (hypo != 0)
	{
		double sin2 = ((ly / hypo)>=0) ? (ly / hypo)*(ly / hypo) : (ly / hypo)*(ly / hypo)*-1;
		double cos2 = ((lx / hypo)>=0) ? (lx / hypo)*(lx / hypo) : (lx / hypo)*(lx / hypo)*-1;
		KofL1R2 =sin2+cos2; 
		KofL2R1 =sin2-cos2;
	
		ML1 = KofL1R2 * hypo;
        	MR2 = ML1;
        	ML2 = KofL2R1 * hypo;
        	MR1 = ML2;
	}
	else 
	{
		KofL1R2 = 0;
		KofL2R1 = 0;

		ML1 = ML2 = MR1 = MR2 = 0;
	}

	// GlobalKof = hypo / 128;
}

void controller::GetInfo() // print info
{
	Serial.print("LX  =  ");
	Serial.print(lx);
	Serial.print("\tLY  =  ");
	Serial.print(ly);
	Serial.print("\tRX  =  ");
	Serial.print(rx);
	Serial.print("\tRY  =  ");
	Serial.print(ry);
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
        //Serial.print("\tGK  =  ");
        //Serial.println(hypo);
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
