
#include <SoftwareSerial.h>

SoftwareSerial COM(2, 3);

byte pattern0[] = {0xFF, 0x01, 0x00, 180};
byte pattern1[] = {0xFF, 0x01, 0x11, 30};
byte pattern2[] = {0xFF, 0x01, 0x22, 224};
byte pattern3[] = {0xFF, 0x01, 0x33, 150};
byte pattern4[] = {0xFF, 0x01, 0x44, 40};
byte pattern5[] = {0xFF, 0x01, 0x55, 120};
byte pattern6[] = {0xFF, 0x01, 0x64, 224};
byte pattern7[] = {0xFF, 0x01, 0x73, 0};
byte pattern8[] = {0xFF, 0x01, 0x82, 224};
byte pattern9[] = {0xFF, 0x01, 0x91, 224};
byte patternA[] = {0xFF, 0x01, 0xA2, 0};
byte patternB[] = {0xFF, 0x01, 0xB3, 224};
byte patternC[] = {0xFF, 0x01, 0xC4, 224};
byte patternD[] = {0xFF, 0x01, 0xD5, 0};
byte patternE[] = {0xFF, 0x01, 0xE2, 20};
byte patternF[] = {0xFF, 0x01, 0xF2, 40};

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
  testPatterns();
  Serial.println("done.");
}

void testPatterns() {
//  COM.write(pattern1, sizeof(pattern1));
//  for(int i = 0; i < sizeof(pattern1); i++)
//    Serial.println(pattern1[i], HEX);
//  delay(5000);
//  Serial.write("changing patterns...");
//  COM.write(pattern2, sizeof(pattern2));
//  for(int i = 0; i < sizeof(pattern2); i++)
//    Serial.println(pattern2[i], HEX);
//  delay(5000);
//  COM.write(pattern3, sizeof(pattern3));
//  delay(5000);
//  COM.write(pattern4, sizeof(pattern4));
//  delay(5000);
//  COM.write(pattern5, sizeof(pattern5));
//  delay(5000);
//  COM.write(pattern6, sizeof(pattern6));
//  delay(5000);
//  COM.write(pattern7, sizeof(pattern7));
//  delay(5000);
//  COM.write(pattern8, sizeof(pattern8));
//  delay(5000);
//  COM.write(pattern9, sizeof(pattern9));
//  delay(5000);
//  COM.write(patternA, sizeof(patternA));
//  delay(5000);
//  COM.write(patternB, sizeof(patternB));
//  delay(5000);
//  COM.write(patternC, sizeof(patternC));
//  delay(5000);
//  COM.write(patternD, sizeof(patternD));
//  delay(5000);
  COM.write(patternE, sizeof(patternE));
  delay(1000);
  COM.write(patternF, sizeof(patternF));
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
