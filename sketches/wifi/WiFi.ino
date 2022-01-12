// Included Library: "WiFiESP" by Bruno Portaluri
#include <ESP8266WiFi.h>

// Replace these with your WiFi network settings
const char* ssid = "codemash";
const char* password = "";

/*  WiFi Status Codes
 *      WL_CONNECTED: 3
 *      WL_DISCONNECTED: 7
 *      WL_IDLE_STATUS: 0
 *      WL_NO_SSID_AVAIL: 1
 *      WL_SCAN_COMPLETED: 2
 *      WL_CONNECT_FAILED: 4
 *      WL_CONNECTION_LOST: 5
 *      WL_NO_SHIELD: 255
 */

void setup() {
  delay(1000);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println("Connecting...");
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if(counter++ >= 29) {
      Serial.println();
      counter = 0;
    }
    Serial.print(".");
  }

  Serial.println(" success!");
  Serial.print("IP Address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
