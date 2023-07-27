#include <Arduino.h>
#include <Lighting.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(84, 5, NEO_GRB + NEO_KHZ800);

Lighting::Lighting()
{
  _red = 255;
  _green = 255;
  _blue = 255;
  _brightness = 255;
  _enabled = true;
}

void Lighting::begin()
{
  strip.begin();
  strip.setBrightness(_brightness);
  strip.show();
  Serial.println("Lighting initialized");
}

void Lighting::enable()
{
  _enabled = true;

  strip.fill(strip.Color(_red, _green, _blue), 0, strip.numPixels());
  strip.setBrightness(_brightness);
  strip.show();

  Serial.println("Lighting enabled");
}

void Lighting::disable()
{
  _enabled = false;

  strip.clear();
  strip.show();

  Serial.println("Lighting disabled");
}

void Lighting::decreaseBrightness()
{
  if (!_enabled) return;

  if (_brightness == 0) return;
  else _brightness -= 15;

  strip.setBrightness(_brightness);
  strip.show();

  Serial.print("Setting brightness to ");
  Serial.println(_brightness);
}

void Lighting::increaseBrightness()
{
  if (!_enabled) return;

  if (_brightness == 255) return;
  else _brightness += 15;

  strip.setBrightness(_brightness);
  strip.show();

  Serial.print("Setting brightness to ");
  Serial.println(_brightness);
}

void Lighting::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
  if (!_enabled) return;

  _red = red;
  _green = green;
  _blue = blue;

  Serial.print("Setting color to ");
  Serial.print(_red);
  Serial.print(", ");
  Serial.print(_green);
  Serial.print(", ");
  Serial.println(_blue);

  strip.fill(strip.Color(_red, _green, _blue), 0, strip.numPixels());
  strip.show();
}


