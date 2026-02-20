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

  int var1; // digit of length
  int var2; // 2digit of length
  float var3; // val of gyroscope

void setup()
{
  Serial.begin(250000);
  while (!Serial) {}
  Serial.println("Start");

  arduino::UartInit(); //initialization uart
  
  prizm.PrizmBegin(); //initialization prizm controller
}

void loop()
{
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
      //dsh.GetInfo(); //print controller info
    }

    /*
    set wheels speed and grabber motors speed
    */
    exc.setMotorSpeeds(2, (dsh.ML2 * -1), (dsh.ML1 * -1)); 
    exc.setMotorSpeeds(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    exc.setMotorPowers(3, (dsh.MG * -1), (dsh.MG * -1));
    //exc.setMotorPowers(2, (dsh.ML2 * -1), (dsh.ML1 * -1)); 
    //exc.setMotorPowers(1, (dsh.MR1 * -1), (dsh.MR2 * -1));
    
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
