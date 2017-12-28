
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "SparkleState.h"
#include "RainbowState.h"
#include "ColormapCycleState.h"

const char* ssid = "RnB";
const char* password = "waaromwij";

void printDebugMessage(String message);

DisplayState *displayStates[] = {
  new SparkleState(),
  new RainbowState(),
  new ColormapCycleState()
};

uint8_t displayStateIndex = 0;
DisplayState *currentDisplayState = displayStates[displayStateIndex];
uint8_t nDisplayStates = sizeof(displayStates) / sizeof(displayStates[0]);

#include "telnet.h"

void setup() {

  DisplayState::strip.begin();
  DisplayState::strip.setBrightness(100);
  for (int iPixel = 0; iPixel < NPIXELS; iPixel++)
    DisplayState::strip.setPixelColor(iPixel, 0x00443322);
  DisplayState::strip.show(); // Initialize all pixels to 'off'



  Serial.begin(115200);
  Serial.println("Booting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  ArduinoOTA.begin();
  initTelnet();
}

void loop() {

  handleTelnet();

  if ((millis() % 10) == 0) {    
    currentDisplayState->update(0.01);
    currentDisplayState->showPixelArray();
  }


  ArduinoOTA.handle();
}


