//#include <TELEOP.h> // ps4 controller lib
#include <PRIZM.h> // tetrix 
#include "include/ControllerStick.h"
#include "include/Auto1.h"

PRIZM prizm;
EXPANSION exc;

controller dsh;

void setup()
{
  if(Serial)
  {
    Serial.begin(250000);
    Serial.println("Start");
  }
  prizm.PrizmBegin();
}

void loop()
{
  if (dsh.CheckController())
  {
    dsh.SetInfo(); //set controller info
    if (Serial)
    {
      Serial.print("V  =  ");
      Serial.print(prizm.readBatteryVoltage());
      dsh.GetInfo(); //print controller info
    }


    exc.setMotorSpeeds(3, (dsh.ML1 * -1), (dsh.ML2 * -1)); 
    exc.setMotorSpeeds(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    //exc.setMotorPowers(3, (dsh.ML1 * -1), (dsh.ML2 * -1)); 
    //exc.setMotorPowers(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    
  }
  else
  {
    exc.setMotorSpeeds(3, 0, 0);
    exc.setMotorSpeeds(1, 0, 0);
    
    //exc.setMotorPowers(3, 0, 0);
    //exc.setMotorPowers(1, 0, 0);
  }
  
}
