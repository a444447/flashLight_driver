#include <WiFi.h>
#include "config.h"

const char *ssid = "a44447";
const char *password = "bbssdo8877";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("connecting...");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(WiFi.status());
  }

  Serial.println("connected!");
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
}

void loop() {

}