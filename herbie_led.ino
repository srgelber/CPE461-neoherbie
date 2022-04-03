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

enum State{
  START, KIT, CAUTION, OFF
  };



void setup() { 
  FastLED.addLeds<WS2812B,DATA_PIN,GRB>(leds,NUM_LEDS);
  FastLED.setBrightness(100);
  Serial.begin(57600);
  COM.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Ready to Receive.");
}


void loop() {

  static State state = START;
  static int anim_speed = 1;
  static int color = 0;

  memset(&header, 0, sizeof(header));
    
  if(COM.available() > 3) {
      //uint8_t index = 0;
      //while(COM.available()){
        //header[index] = COM.read();
        //index++;
      //}
      for(int i = 0; i < 4; i++){
        header[i] = COM.read();
      }
      
    
    //convert_header();
    Serial.print(header[0], HEX);
    Serial.print(", ");
    Serial.print(header[1], HEX);
    Serial.print(", ");
    Serial.print(header[2], HEX);
    Serial.print(", ");
    Serial.println(header[3], HEX);
    
    
    
    parseHeader(state, header, anim_speed, color);

    
    
  }

  switch(state){
    case KIT:
      kit_anim(anim_speed, color);
      break;
    case CAUTION:
      caution_anim(anim_speed, color);
      break;
    case START:
      break;
    case OFF:
      off();
      FastLED.show(); 
      break;
    default:
      break;
    
  }
  //Serial.println("done");
}


void parseHeader(State &state, byte header[], int &anim_speed, int &color){
  if(header[0] == 0xFF){
    if(header[1] == 0x01){
      //Get Pattern
      switch(header[2] >> 4){
        case 0x01:
          state = KIT;
          break;
        case 0x02:
          state = CAUTION;
          break;
        case 0x00:
          state = OFF;
          break;
        default:
          state = START;
          break;
      }
      
      //Get Animation Speed(1-16)
      if((header[2] & 0x0F) == 0){
        anim_speed = 1;
      }else{
        anim_speed = (header[2] & 0x0F);
      }
      

      //Get Color(0-255)
      color = header[3];
      
    }else{
      state = START;
    }
  }else{
    state = START;
  }
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(110); } }

void off() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(1); } }

void kit_anim(int anim_speed, int color){
    static uint8_t hue = 0;
    int temp_speed = 100 / anim_speed;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(color, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(color, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
  }
}


void rainbow_kit_anim(int anim_speed){
    static uint8_t hue = 0;
    int temp_speed = 100 / anim_speed;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
    hue++;
  }

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to red 
    leds[i] = CHSV(hue, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
    hue++;
  }
}

void caution_anim(int anim_speed, int color){
  int temp_speed = 400 / anim_speed;
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 == 0){
      leds[i] = CHSV(color, 255, 255);
    }
  }
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    off();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
  

   // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    if(i % 2 != 0){
      leds[i] = CHSV(color, 255, 255);
    }
  }
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    off();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
  
  
}
