#include <Arduino.h>
#include <Adafruit_NeoPixel.h>



#define STRIP_PIN 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, STRIP_PIN, NEO_GRB + NEO_KHZ800);




void setup() {
  Serial.begin(115200);
  Serial.println("Hello World!");
  
  strip.begin();
}

void loop() {
  strip.setPixelColor(0, 255, 0, 0);
  strip.show();
  delay(1000);
  strip.setPixelColor(0, 0, 255, 0);
  strip.show();
  delay(1000);
  strip.setPixelColor(0, 0, 0, 255);
  strip.show();
  delay(1000);
}