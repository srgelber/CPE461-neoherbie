
#include <SoftwareSerial.h>

SoftwareSerial COM(2, 3);

byte pattern1[] = {0xFF, 0x01, 0xC3, 0xB4, 13};
byte pattern2[] = {0xFF, 0x01, 0xC4, 0xB4, 13};

void setup() {
  Serial.begin(115200);
  COM.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("ready to send.");
  delay(1000);
}


void loop() {
  Serial.write("testing...");
  testPatterns();
  Serial.println("done.");
}

void testPatterns() {
  COM.write(pattern1, sizeof(pattern1));
  delay(5000);
  Serial.write("changing patterns...");
  COM.write(pattern2, sizeof(pattern2));
  delay(5000);
}


void patternOff() {
//  Serial.println("turning LEDs off...");
//  command = {0xFF, 0x01, 0xC3, 0xB4};
//  Serial.println("done.");
}


void patternOn() {
//  Serial.println("turning LEDs on...");
//  command = [0xFF, 0x01, 0xC3, 0xB4];
//  Serial.println("done.");
}
