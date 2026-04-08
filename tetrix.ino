#define VOLTAGE_MIN 0

//#include <TELEOP.h> // ps4 controller lib
#include <PRIZM.h> // tetrix 
#include "include/Controller.h" // controller
#include "include/Auto1.h" // automode
#include "include/UartRead.h" // info by ArduinoMega

PRIZM prizm;
EXPANSION exc;

controller dsh;

bool CheckVoltage(void);
void ServoInit(void);
void BGrabberServo(void);
void BFrog(void);
void BPawGrab(void);
void PawState(uint8_t a);

int var1; // digit of length
int var2; // 2digit of length
float var3; // val of gyroscope

bool keyX = 0;
bool keyO = 0;
bool keyL1 = 0;
bool LastBX = 0;
bool LastBO = 0;
bool LastBL1 = 0;

void setup()
{
  Serial.begin(250000);
  while (!Serial) {}
  Serial.println("Start");

  arduino::UartInit(); //initialization uart

  prizm.PrizmBegin(); //initialization prizm controller
  ServoInit();
}

void loop()
{
  //Serial.println(exc.readServoPosition(4,1));
  if (dsh.CheckController() && CheckVoltage())
  {
    dsh.SetInfo(); //set controller info

    /*
      WARRING: its a not a finiished wersion of print info
      for ATmel328 it will be too long to doing this
      but it is only for developers, so we'll not going to impruve it (for now)
    */
    if (0)
    {
      Serial.print("V  =  ");
      Serial.print(prizm.readBatteryVoltage());
      //Serial.print("\tEL1  =  ");
      //Serial.print(exc.readEncoderCount(1, 1));
      //Serial.print("\tEL2  =  ");
      //Serial.print(exc.readEncoderCount(1, 2));
      //Serial.print("\tER1  =  ");
      //Serial.print(exc.readEncoderCount(2, 1));
      //Serial.print("\tER2  =  ");
      //Serial.print(exc.readEncoderCount(2, 2));
      arduino::ReadInfo(var1, var2, var3);
      Serial.print("\tV1  =  ");
      Serial.print(var1);
      Serial.print("\tV2  =  ");
      Serial.print(var2);
      Serial.print("\tV3  =  ");
      Serial.println(var3);
      dsh.GetInfo(); //print controller info
    }
    Serial.println(dsh.RPState);
    //set wheels speed and grabber motors speed
    exc.setMotorSpeeds(2, (dsh.ML2 * -1), (dsh.ML1 * -1));
    exc.setMotorSpeeds(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    exc.setMotorPowers(3, (dsh.MG * -1), (dsh.MG * -1));
    //exc.setMotorPowers(2, (dsh.ML2 * -1), (dsh.ML1 * -1));
    //exc.setMotorPowers(1, (dsh.MR1 * -1), (dsh.MR2 * -1));

    //BGrabberServo();
    BFrog();
    BPawGrab();
    BPawState(dsh.RPState);
  }
  else
  {
    exc.setMotorSpeeds(2, 0, 0);
    exc.setMotorSpeeds(1, 0, 0);
    exc.setMotorPowers(3, 0, 0);

    //exc.setMotorPowers(2, 0, 0);
    //exc.setMotorPowers(1, 0, 0);
  }

}

bool CheckVoltage (void)
{
  if (prizm.readBatteryVoltage() >= VOLTAGE_MIN)
    return 1;
  else
  {
    Serial.println("ERROR - NOT ENOUGH VOLTAGE");
    delay(2000);
    return 0;
  }
}

void ServoInit(void)
{
  prizm.setServoPosition(1, 98);
  prizm.setServoSpeed(1, 10);
  prizm.setServoSpeed(2, 10);
  prizm.setServoPosition(1, 98);
  ////////////////////////
  //exc.setServoSpeed(4, 1, 10);
  //exc.setServoPosition(4, 1, 123);
  //exc.setServoPosition(4, 5, 175);
  //exc.setServoPosition(4, 5, 5);
  //exc.setServoSpeed(4,5,50);
}

void BGrabberServo(void)
{
  if (LastBX && !dsh.BX) {
    if (keyX) {
      //exc.setServoPosition(4, 1, 123);
    }
    else {
      exc.setServoPosition(4, 1, 95);
    }
    keyX = !keyX;
  }
  LastBX = dsh.BX;
}

void BFrog(void)
{
  if (LastBO && !dsh.BO) {
    if (keyO) {
      prizm.setMotorTarget(1, 360, 0);
    }
    else {
      prizm.setMotorTarget(1, 360, 990);
    }
    keyO = !keyO;
  }
  LastBO = dsh.BO;
}

void BPawGrab(void)
{
  if (LastBL1 && !dsh.BL1) {
    if (keyL1) {
      exc.setServoPosition(4, 5, 5);
    }
    else {
      exc.setServoPosition(4, 5, 175);
    }
    keyL1 = !keyL1;
  }
  LastBL1 = dsh.BL1;
}

void BPawState(uint8_t a)
{
  switch(a){
    case 0:
      exc.setServoPosition(4, 5 ,90);
      exc.setServoPosition(4, 4 ,0);
      exc.setServoPosition(4, 3 ,72);
      break;
    case 1:
      exc.setServoPosition(4, 5 ,90);
      if (exc.readServoPosition(4,3) > 85)
        exc.setServoPosition(4, 4 ,90);
      exc.setServoPosition(4, 3 ,100);
      break;
    case 2:

      break;
  }
}

