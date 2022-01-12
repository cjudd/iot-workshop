#include "FS.h"           // Should be part of the core ESP8266 libs
#include <ESP8266WiFi.h>  // Lib: "WiFiESP" by Bruno Portaluri
#include <PubSubClient.h> // Lib: "PubSubClient" by Nick O'Leary
#include <NTPClient.h>    // Lib: "NTPClient" by Fabrice Weinberg
#include <WiFiUdp.h>      // Should be part of the core ESP8266 libs


// Update these with values suitable for your network.
const char* ssid = "codemash";
const char* password = "";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

const char* AWS_endpoint = "______________-ats.iot.us-west-2.amazonaws.com"; //MQTT broker ip


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}


WiFiClientSecure espClient;
PubSubClient client(AWS_endpoint, 8883, callback, espClient); //set  MQTT port number to 8883 as per //standard
long lastMsg = 0;
char msg[50];
int value = 0;

void setupWifi() {
  delay(10);
  // We start by connecting to a WiFi network
  espClient.setBufferSizes(512, 512);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  while(!timeClient.update()){
    timeClient.forceUpdate();
  }

  espClient.setX509Time(timeClient.getEpochTime());
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection... ");
    // Attempt to connect
    if (client.connect("8c:aa:b5:c5:b9:d8")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf,256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  setupWifi();
  delay(1000);
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());

  // Load certificate file
  File cert = SPIFFS.open("/________-certificate.pem.crt", "r"); // TODO: replace with your uploaded file name
  if (!cert) {
    Serial.println("[ERROR] Failed to open cert file");
  }
  else Serial.println("Successfully opened cert file");

  delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("Cert loaded to ESP Client.");
  else
    Serial.println("[ERROR] Cert not loaded to ESP Client.");

  // Load private key file
  File private_key = SPIFFS.open("/________-private.pem.key", "r"); // TODO: replace with your uploaded file name
  if (!private_key) {
    Serial.println("[ERROR] Failed to open private cert file");
  } else Serial.println("Successfully opened private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("Succesfully loaded private key.");
  else Serial.println("[ERROR] Private key not loaded");


  // Load CA file
  File ca = SPIFFS.open("/AmazonRootCA1.pem", "r"); // TODO: replace with your uploaded CA file name
  if (!ca) {
    Serial.println("[ERROR] Failed to open ca");
  } else Serial.println("Successfully opened ca");

  delay(1000);

  if(espClient.loadCACert(ca)) Serial.println("CA cert loaded.");
  else Serial.println("[ERROR] Failed to load CA cert.");

  Serial.print("Heap: ");
  Serial.println(ESP.getFreeHeap());
}

void loop() {
  if (!client.connected()) { reconnect(); }
  client.loop();

  long now = millis();
  if (now - lastMsg > 10000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "{\"message\": \"Hello World! This is msg #%ld\"}", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("BrandonOutTopic", msg);
    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  }
}
