#include <FastLED.h>
#include <SoftwareSerial.h>

// How many leds in your strip?
#define NUM_LEDS 16 

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7

// Define the array of leds
CRGB leds[NUM_LEDS];
byte header[5];
byte input;
bool command_ready = false;
SoftwareSerial COM(9, 10);



void setup() { 
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(84);
  Serial.begin(115200);
  COM.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Ready to Receive.");
}


void loop() {
    
    
  if(COM.available() > 0) {
    header[0] = COM.read();
    if(header[0] == 255){
      uint8_t index = 1;
      while(COM.available()){
        header[index] = COM.read();
        index++;
      }
      command_ready = true;

    }
    //convert_header();
   
    //Serial.println(header[0], HEX);
    //Serial.println(header[1], HEX);
    //Serial.println(header[2], HEX);
    //Serial.println(header[3], HEX);
    //Serial.println(header[4], HEX);

    
  
  }
  
  if(header[2] == 195){
    kit_anim();
  }
  else if(header[2] == 196){
    warning_anim();
  }
  //Serial.println("done");
}

void convert_header(){
  memset(&header, 0, sizeof(header));
  static uint8_t index = 0;
  

   for (int i=0; i<4; i++) {
      //while(!Serial.available()); // wait for a character
    int incomingByte = Serial.read();
    Serial.print(incomingByte,HEX);
    Serial.print(' ');
    }
    Serial.println();
    
  //while(Serial.available() > 0){
    //recv_char = Serial.read();
    //Serial.println("im here");
    //header[index] = recv_char;
    //index++;
    //}
  
}


void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(110); } }

void off() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(1); } }

void kit_anim(){
    static uint8_t hue = 0;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(0, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(0, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
}

void warning_anim(){
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 == 0){
      leds[i] = CHSV(64, 255, 255);
    }
  }
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    off();
    // Wait a little bit before we loop around and do it again
    delay(200);
  

   // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 != 0){
      leds[i] = CHSV(64, 255, 255);
    }
  }
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    off();
    // Wait a little bit before we loop around and do it again
    delay(200);
  
  
}
