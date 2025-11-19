#include <TELEOP.h> // ps4 controller lib
#include <PRIZM.h> // tetrix 
#include "include/ControllerStick.h"
#include "include/Auto1.h"

PRIZM prizm;
PS4 ps4;

controller controller1;

void setup()
{
  Serial.begin(9600);
  Serial.println("Start");
  prizm.PrizmBegin();
}

void loop()
{
  if (controller1.CheckController())
  {
    controller1.SetInfo(); //set controller info
    controller1.GetInfo(); //print controller info

    prizm.setMotorPower(1,controller.LY);
    prizm.setMotorPower(2,controller.LY);
  }
  
}
