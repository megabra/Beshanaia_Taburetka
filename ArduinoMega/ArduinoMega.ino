#include <HCSR04.h>
#include "include/UartPut.h"

const byte triggerPin = 2;
const byte echoCount = 2;
byte echoPins[echoCount] = { 3, 4};

double* distances;

void setup () {
  Serial.begin(9600);
  while(!Serial) {}
  
  //UltraDigit::UartInit();

  HCSR04.begin(triggerPin, echoPins, echoCount);
}

void loop () {
  distances = HCSR04.measureDistanceMm();
  
  for (int i = 0; i < echoCount; i++) 
  {
    //UltraDigit::PutInfo(uint16_t(distances[i]));
    Serial.print(i+1);
    Serial.print('\t');
    Serial.println(distances[i]);
  }
  
}
