
#include <SoftwareSerial.h>

SoftwareSerial COM(2, 3);

// off
byte pattern0[] = {0xFF, 0x01, 0x00, 180};
// kitt
byte pattern1[] = {0xFF, 0x01, 0x11, 30};
// rainbow kitt
byte pattern2[] = {0xFF, 0x01, 0x22, 224};
// caution
byte pattern3[] = {0xFF, 0x01, 0x33, 150};
// random (star)
byte pattern4[] = {0xFF, 0x01, 0x44, 40};
// triple star
byte pattern5[] = {0xFF, 0x01, 0x55, 120};
// rainbow star
byte pattern6[] = {0xFF, 0x01, 0x64, 224};
// rainbow triple star
byte pattern7[] = {0xFF, 0x01, 0x73, 0};
// marquee
byte pattern8[] = {0xFF, 0x01, 0x82, 224};
// rainbow marquee
byte pattern9[] = {0xFF, 0x01, 0x91, 224};
// double kitt
byte patternA[] = {0xFF, 0x01, 0xA2, 0};
// rainbow double kitt
byte patternB[] = {0xFF, 0x01, 0xB3, 224};
// fade
byte patternC[] = {0xFF, 0x01, 0xC4, 224};
// rainbow fade
byte patternD[] = {0xFF, 0x01, 0xD5, 0};
// change brightness
byte patternE[] = {0xFF, 0x01, 0xE2, 100};
// debug
byte patternF[] = {0xFF, 0x01, 0xF2, 40};
// invalid
byte invalid[] = {0, 0, 0, 0};

void setup() {
  Serial.begin(57600);
  COM.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("ready to send.");
  delay(1000);
}

void loop() {
  Serial.write("testing...");
  //testPatterns();
  COM.write(patternA, sizeof(patternA));
  delay(10000);
  Serial.write("changing patterns...");
  COM.write(pattern8, sizeof(pattern8));
  delay(5000);
  Serial.write("invalid...");
  COM.write(invalid, sizeof(invalid));
  delay(7500);
  Serial.println("done.");
}

void testPatterns() {
  COM.write(pattern1, sizeof(pattern1));
  for (int i = 0; i < sizeof(pattern1); i++)
    Serial.println(pattern1[i], HEX);
  delay(1000);
  Serial.write("changing patterns...");
  COM.write(pattern2, sizeof(pattern2));
  for (int i = 0; i < sizeof(pattern2); i++)
    Serial.println(pattern2[i], HEX);
  delay(1000);
  COM.write(pattern3, sizeof(pattern3));
  delay(1000);
  COM.write(pattern4, sizeof(pattern4));
  delay(1000);
  COM.write(pattern5, sizeof(pattern5));
  delay(1000);
  COM.write(pattern6, sizeof(pattern6));
  delay(1000);
  COM.write(pattern7, sizeof(pattern7));
  delay(1000);
  COM.write(pattern8, sizeof(pattern8));
  delay(1000);
  COM.write(pattern9, sizeof(pattern9));
  delay(1000);
  COM.write(patternA, sizeof(patternA));
  delay(1000);
  COM.write(patternB, sizeof(patternB));
  delay(1000);
  COM.write(patternC, sizeof(patternC));
  delay(1000);
  COM.write(patternD, sizeof(patternD));
  delay(1000);
  COM.write(patternE, sizeof(patternE));
  delay(1000);
  COM.write(patternF, sizeof(patternF));
  delay(1000);
}
