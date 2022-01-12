#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* ssid = "codemash";
const char* password = "";

const char fingerprint[] PROGMEM = "eeaa586d4f1f42f4185b7fb0f20a4cdd97477d99";

//https://api.openweathermap.org/data/2.5/weather?q=London
//https://samples.openweathermap.org/data/2.5/weather?q=London,uk&appid=439d4b804bc8187953eb36d2a8c26a02
const char* host = "samples.openweathermap.org";
const int httpsPort = 443;

void setup() {
  Serial.begin(115200);
  delay(100);

  WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  
  Serial.print("Connecting to " + String(ssid) + " .");
  while(WiFi.status() != WL_CONNECTED) {
        delay(500);
    Serial.print(".");
  }
  Serial.print("\nConnected! IP: ");
  Serial.println(WiFi.localIP()); 
}
  
void loop() {
  WiFiClientSecure client;

  client.setFingerprint(fingerprint);
    client.setTimeout(15000);
    delay(1000);
  
  int retryCount=0;
  while((!client.connect(host, httpsPort)) && (retryCount < 30)){
    delay(100);
    Serial.print(".");
    retryCount++;
  }
  if(retryCount==30) {
      Serial.print("Connection failed: ");
      Serial.println(client.connect(host, httpsPort));
      return;
  }
  
  String url = "/data/2.5/weather?q=London,uk&appid=439d4b804bc8187953eb36d2a8c26a02";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n");

  // parse headers
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("[Headers received]");
      break;
    }
  } 

  // parse body
  String results[3];
  int i = 0;
  while(client.available()) {
    String line = client.readStringUntil('\n');
    Serial.print("Line ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(line);
    results[i] = line;
    i++;
  }

  Serial.println("GET Response:");
  Serial.println(results[1]);
  Serial.println();

  StaticJsonDocument<1024> doc;
    deserializeJson(doc, results[1]);
  
  JsonObject weather_0 = doc["weather"][0];
    const char* weather_0_main = weather_0["main"];
    const char* weather_0_description = weather_0["description"]; 
  JsonObject main = doc["main"];
    float main_temp = main["temp"];
    Serial.print("Weather: ");
    Serial.println(String(weather_0_main));
    Serial.print("Temperature: ");
    Serial.println(String(main_temp));

  delay(10000);
}
