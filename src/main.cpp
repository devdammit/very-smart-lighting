#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <esp_now.h>
#include <WiFi.h>
#include <map>
#include <Lighting.cpp>

#if defined(MASTER_MODE)
#define MASTER_MODE true
#else
#define MASTER_MODE false
#endif

const int IR_PIN = 3;
const int LED_PIN = 2;

IRrecv irrecv(IR_PIN);
decode_results results;

Lighting lighting(LED_PIN);

uint8_t broadcastAddress[] = {0xC0, 0x49, 0xEF, 0xCC, 0xB1, 0x78};

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
      lighting.decreaseBrightness();
      break;
    }
    case 1: {
      lighting.increaseBrightness();
      break;
    }
    case 2: {
      lighting.disable();
      break;
    }
    case 3: {
      lighting.enable();
      break;
    }
    case 4: {
      lighting.setColor(255, 0, 0);
      break;
    }
    case 5: {
      lighting.setColor(0, 255, 0);
      break;
    }
    case 6: {
      lighting.setColor(0, 0, 255);
      break;
    }
    case 7: {
      lighting.setColor(255, 255, 255);
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

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);

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

  WiFi.mode(WIFI_STA);

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
      // Serial.println(results.value, HEX);

      if (CodeToButtonMap.find(results.value) != CodeToButtonMap.end()) {
        // Serial.println(CodeToButtonMap[results.value].command);
        executeCommand(&CodeToButtonMap[results.value]);
        sendCommand(CodeToButtonMap[results.value]);
      }

      irrecv.resume(); // Receive the next value
    }

    delay(200);
  }
}
