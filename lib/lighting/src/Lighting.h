#include <Arduino.h>

class Lighting
{
private:
  int _pin;
  int _brightness;
  int _duration;
  int _lastUpdate;
  bool _enabled;

public:
  Lighting(int pin);

  void enable();
  void disable();

  void setBrightness(int brightness);

  void decreaseBrightness();
  void increaseBrightness();

  void setColor(int red, int green, int blue);
};