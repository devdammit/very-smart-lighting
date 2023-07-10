#include <Arduino.h>

class Lighting
{
private:
  bool _enabled;

  int _pin;

  int _brightness;

public:
  Lighting(int pin)
  {
    _pin = pin;
  }

  void enable()
  {
    _enabled = true;

    Serial.println("Lighting enabled");
  }

  void disable()
  {
    _enabled = false;

    Serial.println("Lighting disabled");
  }

  void setBrightness(int brightness)
  {
    Serial.print("Setting brightness to ");
    Serial.println(brightness);
  }

  void decreaseBrightness()
  {
    Serial.println("Decreasing brightness");
  }

  void increaseBrightness()
  {
    Serial.println("Increasing brightness");
  }

  void setColor(int red, int green, int blue)
  {
    Serial.print("Setting color to ");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.println(blue);
  }
};