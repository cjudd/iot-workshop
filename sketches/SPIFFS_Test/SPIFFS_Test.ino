#include <FS.h>

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Starting up.");
}

void loop() {
  int count = 0;

  while(true) {
    delay(5000);
    Serial.println();
    Serial.println();
    bool success = SPIFFS.begin();
  
    if(!success) {
      Serial.println("[ERROR] Failed to mount the file system");
      return;
    } else {
      Serial.println("[SUCCESS] File system mounted.");
    }
  
  
    File file2 = SPIFFS.open("/wifi.txt", "r");
    if(!file2) {
      Serial.println("[ERROR] Failed to open '/file.txt' for reading");
      return;
    }
  
    Serial.println("File content: ");
  
    while(file2.available()) {
      Serial.write(file2.read());
    }
  
    file2.close();
  }
}
