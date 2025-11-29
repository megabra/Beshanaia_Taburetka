//#include <TELEOP.h> // ps4 controller lib
#include <PRIZM.h> // tetrix 
#include "include/ControllerStick.h"
#include "include/Auto1.h"

PRIZM prizm;
EXPANSION exc;

controller dsh;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  prizm.PrizmBegin();
}

void loop()
{
  if (dsh.CheckController())
  {
    dsh.SetInfo(); //set controller info
    dsh.GetInfo(); //print controller info

    exc.setMotorPowers(3, dsh.ML1, dsh.ML2); 
    exc.setMotorPowers(1, dsh.MR1, dsh.MR2);
  }
  else
  {
    exc.setMotorPowers(3, 0, 0);
    exc.setMotorPowers(1, 0, 0);
  }
  
}
