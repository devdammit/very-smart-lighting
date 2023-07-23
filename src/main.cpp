#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <esp_now.h>
#include <WiFi.h>
#include <map>
#include <Lighting.h>
#include <Adafruit_NeoPixel.h>



#if defined(MASTER_MODE)
#define MASTER_MODE true
#else
#define MASTER_MODE false
#endif

#define SIMPLE_LED_PIN 18


Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, 5, NEO_GRB + NEO_KHZ800);

IRrecv irrecv(17);
decode_results results;


uint8_t slaveAddress[] = {0xB0, 0xA7, 0x32, 0xDB, 0x1E, 0x1C};

typedef struct command_struct {
  int8_t command;
} command_struct;

std::map<int64_t, command_struct> CodeToButtonMap = {
  { 0xF700FF, { 0 } },
  { 0xF7807F, { 1 } },
  { 0xF740BF, { 2 } },
  { 0xF7C03F, { 3 } },
  { 0xF720DF, { 4 } },
  { 0xF7A05F, { 5 } },
  { 0xF7609F, { 6 } },
  { 0xF7E01F, { 7 } },
};

esp_now_peer_info_t peerInfo;

void executeCommand(command_struct* command) {
  switch(command->command) {
    case 0: {
      Serial.println("Decreasing brightness");
      break;
    }
    case 1: {
      Serial.println("Increasing brightness");
      break;
    }
    case 2: {
      Serial.println("Disabling lighting");
      break;
    }
    case 3: {
      Serial.println("Enabling lighting");
      break;
    }
    case 4: {
      strip.fill(strip.Color(255, 0, 0), 0, strip.numPixels());
      strip.show();
      break;
    }
    case 5: {
      strip.fill(strip.Color(0, 255, 0), 0, strip.numPixels());
      strip.show();
      break;
    }
    case 6: {
      strip.fill(strip.Color(0, 0, 255), 0, strip.numPixels());
      strip.show();
      break;
    }
    case 7: {
      strip.fill(strip.Color(159, 3, 226), 0, strip.numPixels());
      strip.show();
      break;
    }
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  command_struct *receivedCommand = (command_struct *) data;

  Serial.print("Command received: ");
  Serial.println(receivedCommand->command);

  executeCommand(receivedCommand);
}

void sendCommand(command_struct command) {
  esp_err_t result = esp_now_send(0, (uint8_t *) &command, sizeof(command));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
}

void masterSetup() {
  Serial.println("I am the master");

  irrecv.enableIRIn();
  Serial.println("IR Receiver ready");

  esp_now_register_send_cb(OnDataSent);

  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  memcpy(peerInfo.peer_addr, slaveAddress, 6);

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void slaveSetup() {
  Serial.println("I am the slave");

  esp_now_register_recv_cb(OnDataRecv);

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void setup()
{
  Serial.begin(9600);
  strip.begin();
  strip.show();
  WiFi.mode(WIFI_STA);

  pinMode(SIMPLE_LED_PIN, OUTPUT);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  if (MASTER_MODE) {
    masterSetup();
  } else {
    slaveSetup();
  }
}

void loop()
{
  if (MASTER_MODE)
  {

    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      digitalWrite(SIMPLE_LED_PIN, HIGH);

      if (CodeToButtonMap.find(results.value) != CodeToButtonMap.end()) {
        Serial.println(CodeToButtonMap[results.value].command);
        executeCommand(&CodeToButtonMap[results.value]);
        sendCommand(CodeToButtonMap[results.value]);
      }

      irrecv.resume(); // Receive the next value
    }

    delay(200);
    digitalWrite(SIMPLE_LED_PIN, LOW);
    delay(200);
  }
}
