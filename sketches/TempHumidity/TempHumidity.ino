#include "DHT.h"

#define DHT_PIN 0
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();          // Begin reading from the DHT11
}

void loop() {
  delay(5000);  // Wait 5 seconds between measurements.

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();      // Read temperature as Celsius (the default)
  float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("[ERROR] Failed to read from DHT sensor."));
    return;
  }
  
  Serial.print(F("Humidity: "));    // F(string) uses FLASH memory, freeing up dynamic RAM
  Serial.print(h);
  Serial.println("%");
  
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println(F("°F"));
  
  float hif = dht.computeHeatIndex(f, h);           // Compute heat index in Fahrenheit (the default)
  float hic = dht.computeHeatIndex(t, h, false);    // Compute heat index in Celsius (isFahreheit = false)

  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  Serial.println();
}
