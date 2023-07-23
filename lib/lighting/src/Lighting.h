#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Lighting
{


public:
  Lighting(int pin);

  void begin();

  void enable();
  void disable();

  void decreaseBrightness();
  void increaseBrightness();

  void setColor(uint8_t red, uint8_t green, uint8_t blue);

private:
  Adafruit_NeoPixel strip;

  uint8_t _red;
  uint8_t _green;
  uint8_t _blue;

  uint8_t _brightness;

  bool _enabled;

};