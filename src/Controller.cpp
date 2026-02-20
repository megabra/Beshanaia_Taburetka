
#include "../include/Controller.h"

PS4 ps4;

// deadzone for controller
int controller::deadzone(int val) 
{
	const uint8_t zone = 20;
	if (val <= (128 - zone) || val >= (128 + zone))
		return val - 128;
	else
		return 0;
}

// Set grabber motors speed
void controller::SetGraber(int ly, int r2, float &GlobalKof) 
{
	#define MAX_STICK_VAL 127.0
	#define MAX_BUTTON_VAL 255.0
	#define SPEED_MOD_MIN 50 // minimal val of max stick val 
	#define SPEED_MOD_MAX 180 // maximal val of max stick val

	float MAX_MOTOR_VAL = SPEED_MOD_MIN + ((r2 / MAX_BUTTON_VAL) * (SPEED_MOD_MAX - SPEED_MOD_MIN));
	
	ly = (ly > MAX_STICK_VAL) ? MAX_STICK_VAL : ly;
	ly = (ly < (MAX_STICK_VAL * -1)) ? (MAX_STICK_VAL * -1) : ly;

	GlobalKof = MG = ly / MAX_STICK_VAL * MAX_MOTOR_VAL;
}

// Set wheels motors speed
void controller::SetWheels(int ly, int lx, int rx, int r2, float &KofL1R2, float &KofL2R1, float &Rotate, float &GlobalKof)
{
	#define MAX_STICK_VAL 127.0
        #define MAX_BUTTON_VAL 255.0
        #define SPEED_MOD_MIN 100 // minimal val of max stick val
        #define SPEED_MOD_MAX 600 // maximal val of max stick val
        float MAX_MOTOR_VAL = SPEED_MOD_MIN + ((r2 / MAX_BUTTON_VAL) * (SPEED_MOD_MAX - SPEED_MOD_MIN));

        float hypo = sqrt((lx*lx)+(ly*ly)) + abs(rx);
        hypo = (hypo > MAX_STICK_VAL) ? MAX_STICK_VAL : hypo;

        GlobalKof = hypo / MAX_STICK_VAL * MAX_MOTOR_VAL;

        Rotate = rx / MAX_STICK_VAL;
        Rotate = (Rotate > 1) ? 1 : (Rotate < -1) ? -1 : Rotate;

        KofL1R2 = KofL2R1 = 0;

        if (hypo != 0)
        {
                float sin2 = abs((ly / hypo))*(ly / hypo);
                float cos2 = abs((lx / hypo))*(lx / hypo);

                KofL1R2 =sin2+cos2;
                KofL2R1 =sin2-cos2;
        }

                int RawL1 = (KofL1R2 + Rotate) * GlobalKof;
                int RawR2 = (KofL1R2 - Rotate) * GlobalKof;
                int RawL2 = (KofL2R1 + Rotate) * GlobalKof;
                int RawR1 = (KofL2R1 - Rotate) * GlobalKof;

                ML1 = (RawL1 > MAX_MOTOR_VAL) ? MAX_MOTOR_VAL : (RawL1 < -MAX_MOTOR_VAL) ? -MAX_MOTOR_VAL : RawL1;
                MR2 = (RawR2 > MAX_MOTOR_VAL) ? MAX_MOTOR_VAL : (RawR2 < -MAX_MOTOR_VAL) ? -MAX_MOTOR_VAL : RawR2;
                ML2 = (RawL2 > MAX_MOTOR_VAL) ? MAX_MOTOR_VAL : (RawL2 < -MAX_MOTOR_VAL) ? -MAX_MOTOR_VAL : RawL2;
                MR1 = (RawR1 > MAX_MOTOR_VAL) ? MAX_MOTOR_VAL : (RawR1 < -MAX_MOTOR_VAL) ? -MAX_MOTOR_VAL : RawR1;

                if(hypo == 0 && Rotate == 0)
                        ML1 = ML2 = MR1 = MR2 = 0;

        /*
		Formul:
        m = MAX_MOTOR_VAL
        k = KOF_OF_THE_SPEED = sqrt(lx^2+ly^2)/MAX_STICK_VAL*m
        L1 = min(max((sin(x)*|sin(x)|+cos(x)*|cos(x)|+rx)*k,-m),m)
        L2 = min(max((sin(x)*|sin(x)|-cos(x)*|cos(x)|+rx)*k,-m),m)
        R1 = min(max((sin(x)*|sin(x)|-cos(x)*|cos(x)|-rx)*k,-m),m)
        R2 = min(max((sin(x)*|sin(x)|+cos(x)*|cos(x)|-rx)*k,-m),m)
        */
}

// Set info
void controller::SetInfo() 
{
	ly = deadzone(ps4.Stick(LY));

	if (ps4.Button(R1)){
		ML1 = ML2 = MR1 = MR2 = KofL1R2 = KofL2R1 = Rotate = 0;
		
		SetGraber(ly, r2, GlobalKof);
	}
	else{
		MG = 0;

		lx = deadzone(ps4.Stick(LX));
		rx = deadzone(ps4.Stick(RX));
		r2 = deadzone((ps4.Button(R2T)+128));
		
		SetWheels(ly, lx, rx, r2, KofL1R2, KofL2R1, Rotate, GlobalKof);
	}
}

/*
	WARRING: its a not a finiished wersion of print info
	for ATmel328 it will be too long to doing this
	but it is only for developers, so we'll not going to impruve it (for now)
*/
// print info
void controller::GetInfo()
{
	//Serial.print("\tLX  =  ");
	//Serial.print(lx);
	Serial.print("\tLY  =  ");
	Serial.print(ly);
	//Serial.print("\tRX  =  ");
	//Serial.print(rx);
	//Serial.print("\tRY  =  ");
	//Serial.print(ry);
	//Serial.print("\tR2  =  ");
	//Serial.print(r2);
	//Serial.print("\rMMV  =  ");
	//Serial.print(MAX_MOTOR_VAL);
	Serial.print("\tML1  =  ");
    Serial.print(ML1);
    Serial.print("\tML2  =  ");
    Serial.print(ML2);
    Serial.print("\tMR1  =  ");
    Serial.print(MR1);
    Serial.print("\tMR2  =  ");
    Serial.print(MR2);
	//Serial.print("\tK1  =  ");
    //Serial.print(KofL1R2);
    //Serial.print("\tK2  =  ");
    //Serial.print(KofL2R1);
	//Serial.print("\tRT  =  ");
	//Serial.print(Rotate);
    Serial.print("\tGK  =  ");
    Serial.print(GlobalKof);
	Serial.print("\tr1  =  ");
	Serial.print(ps4.Button(R1));
	Serial.println();
}

// checking controller
bool controller::CheckController(void)
{
	ps4.getPS4();
	if (ps4.Connected)
		return 1;
	else
	{
		delay(2000);
		Serial.println("ERROR - controller doesn't conected");
		return 0;
	}
}
