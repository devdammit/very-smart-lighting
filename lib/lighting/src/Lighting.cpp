#include <Arduino.h>
#include <Lighting.h>


Lighting::Lighting(int pin)
{
  Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, pin, NEO_GRB + NEO_KHZ800);

  _red = 255;
  _green = 255;
  _blue = 255;
  _brightness = 100;
  _enabled = true;

}

void Lighting::begin()
{
  strip.begin();
  strip.setBrightness(_brightness);
  strip.show();
}

void Lighting::enable()
{
  _enabled = true;

  Serial.println("Lighting enabled");
}

void Lighting::disable()
{
  _enabled = false;

  Serial.println("Lighting disabled");
}

void Lighting::decreaseBrightness()
{
  if (_brightness == 0) return;
  else _brightness -= 10;

  strip.setBrightness(_brightness);

  Serial.print("Setting brightness to ");
  Serial.println(_brightness);
}

void Lighting::increaseBrightness()
{
  if (_brightness == 100) return;
  else _brightness += 10;

  strip.setBrightness(_brightness);

  Serial.print("Setting brightness to ");
  Serial.println(_brightness);
}

void Lighting::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
  _red = red;
  _green = green;
  _blue = blue;

  strip.fill(strip.Color(_red, _green, _blue), 0, strip.numPixels());
  strip.show();
}


