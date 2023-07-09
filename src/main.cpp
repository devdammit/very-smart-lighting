#include <Arduino.h>

#if defined(MASTER_MODE)
#define MASTER_MODE true
#else
#define MASTER_MODE false
#endif

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  delay(1000);
  if (MASTER_MODE)
  {
    Serial.println("I am the master");
  }
  else
  {
    Serial.println("I am the slave");
  }
}