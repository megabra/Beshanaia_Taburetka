#include <HCSR04.h>
#include "include/UartPut.h"// put info

/*const byte triggerPin = 2;
const byte echoCount = 2;
byte echoPins[echoCount] = { 3, 4};

double* distances;
*/
void setup () {
  Serial.begin(9600);
  while(!Serial) {}
  
  arduino::UartInit();

  //HCSR04.begin(triggerPin, echoPins, echoCount);
}

void loop () {
  arduino::PutInfo(true, false, 123.45);
  /*distances = HCSR04.measureDistanceMm();
  
  for (int i = 0; i < echoCount; i++) 
  {
    Serial.print(i+1);
    Serial.print('\t');
    Serial.println(distances[i]);
  }
  */
}
