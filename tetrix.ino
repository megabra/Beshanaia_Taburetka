#define VOLTAGE_MIN 0

//#include <TELEOP.h> // ps4 controller lib
#include <PRIZM.h> // tetrix 
#include "include/ControllerStick.h"
#include "include/Auto1.h"
#include "include/UartRead.h"

PRIZM prizm;
EXPANSION exc;

controller dsh;

bool CheckVoltage(void);

 int var1;
  int var2;
  float var3;

void setup()
{
  Serial.begin(250000);
  while (!Serial) {}
  Serial.println("Start");

  UltraDigit::UartInit(); //initialization uart
  
  prizm.PrizmBegin();
}

void loop()
{
  if (dsh.CheckController() && CheckVoltage())
  {
    dsh.SetInfo(); //set controller info
    if (0)
    {
      Serial.print("V  =  ");
      Serial.print(prizm.readBatteryVoltage());
      //Serial.print("\tD1  =  ");
      //Serial.print(UltraDigit::ReadInfo());
      //Serial.print("\tD2  =  ");
      //Serial.print(UltraDigit::ReadInfo());
      Serial.print("\tEL1  =  ");
      Serial.print(exc.readEncoderCount(1, 1));
      Serial.print("\tEL2  =  ");
      Serial.print(exc.readEncoderCount(1, 2));
      Serial.print("\tER1  =  ");
      Serial.print(exc.readEncoderCount(2, 1));
      Serial.print("\tER2  =  ");
      Serial.print(exc.readEncoderCount(2, 2));
      //dsh.GetInfo(); //print controller info
      UltraDigit::ReadInfo(var1, var2, var3);
      Serial.print("\tV1  =  ");
      Serial.print(var1);
      Serial.print("\tV2  =  ");
      Serial.print(var2);
      Serial.print("\tV3  =  ");
      Serial.println(var3);
    }


    exc.setMotorSpeeds(2, (dsh.ML2 * -1), (dsh.ML1 * -1)); 
    exc.setMotorSpeeds(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    exc.setMotorSpeeds(3, dsh.MG, dsh.MG);
    //exc.setMotorPowers(3, (dsh.ML2 * -1), (dsh.ML1 * -1)); 
    //exc.setMotorPowers(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    
  }
  else
  {
    exc.setMotorSpeeds(2, 0, 0);
    exc.setMotorSpeeds(1, 0, 0);
    exc.setMotorSpeeds(3, 0, 0);
    
    //exc.setMotorPowers(3, 0, 0);
    //exc.setMotorPowers(1, 0, 0);
  }
  
}

bool CheckVoltage (void)
{
  if (prizm.readBatteryVoltage() >= VOLTAGE_MIN)
    return 1;
  else
  {
    Serial.println("ERROR - NOR ENOUGH VOLTAGE");
    delay(2000);
    return 0;
  }
}
