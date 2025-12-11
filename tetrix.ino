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
    if (Serial)
    {
      Serial.print("V  =  ");
      Serial.print(prizm.readBatteryVoltage());
      Serial.print("\tD1  =  ");
      Serial.print(UltraDigit::ReadInfo());
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