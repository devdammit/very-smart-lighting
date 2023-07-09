#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

IRrecv irrecv(3);

decode_results results;

void setup() {
  Serial.begin(115200);
  irrecv.enableIRIn();
  Serial.println("IR Receiver ready");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(300);
  Serial.println("loop");
}