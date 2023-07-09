#include <Arduino.h>

class Lighting
{

  Lighting(int pin);

private:
  int _pin;
  int _brightness;
  int _duration;
  int _lastUpdate;
  bool _enabled;

public:
  void enable();
  void disable();

  void setBrightness(int brightness);

  void setColor(int red, int green, int blue);
};