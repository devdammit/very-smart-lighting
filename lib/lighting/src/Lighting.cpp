#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Lighting
{
private:
  Adafruit_NeoPixel NeoPixel;

  int _red;
  int _green;
  int _blue;

  int _brightness;

  bool _enabled;

public:
  Lighting(int pin)
  {
    Adafruit_NeoPixel NeoPixel = Adafruit_NeoPixel(84, pin, NEO_GRB + NEO_KHZ800);

    _red = 255;
    _green = 255;
    _blue = 255;
    _brightness = 50;

    NeoPixel.begin();
    NeoPixel.setBrightness(_brightness);
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
    if (_brightness == 0) return;

    _brightness -= 10;
    NeoPixel.setBrightness(_brightness);
  }

  void increaseBrightness()
  {
    if (_brightness == 100) return;

    _brightness += 10;
    NeoPixel.setBrightness(_brightness);
  }

  void setColor(int red, int green, int blue)
  {
    for (int i = 0; i < NeoPixel.numPixels(); i++) {
      NeoPixel.setPixelColor(i, red, green, blue);
    }
    
    NeoPixel.show();
  }
};