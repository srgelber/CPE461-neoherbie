#include <FastLED.h>
#include <SoftwareSerial.h>

// How many leds in your strip?
#define NUM_LEDS 9

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

enum State {
  START, OFF, KIT, RAINBOW_KIT, CAUTION, 
  RANDOM, RANDOM_TRIPLE, RANDOM_RAINBOW, RANDOM_TRIPLE_RAINBOW, 
  MARQUEE, RAINBOW_MARQUEE, 
  CENTER_OUT, RAINBOW_CENTER_OUT, 
  FADE, RAINBOW_FADE,
  BRIGHTNESS, DEBUG
};


void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(57600);
  COM.begin(57600);
}


void loop() {
//  for (int i = 0; i < 3; i++)
//    kit_anim(1, 224);
//  for (int i = 0; i < 5; i++)
//    caution_anim(3, 0);
//  for (int i = 0; i < 20; i++)
//    rainbow_kit_anim(2);
//  rainbow_marquee(1, 224);
//  for (int i = 0; i < 2; i++)
//    fade(1, 224);
//  for (int i = 0; i < 2; i++)
//    rainbow_fade(1, 0);
    for (int i = 0; i < 5; i++)
    star(1, 0);
  for (int i = 0; i < 5; i++)
    rainbow_star(1, 0);
  for (int i = 0; i < 5; i++)
    star(1, 0);
  for (int i = 0; i < 5; i++)
    rainbow_star(1, 0);


//  static State state = START;
//  static int anim_speed = 1;
//  static int color = 0;
//
//  memset(&header, 0, sizeof(header));
//
//  if (COM.available() > 3) {
//    for (int i = 0; i < 4; i++) {
//      header[i] = COM.read();
//    }
//    parseHeader(state, header, anim_speed, color);
//  }
//
//  switch (state) {
//    case KIT:
//      kit_anim(anim_speed, color);
//      break;
//    case CAUTION:
//      caution_anim(anim_speed, color);
//      break;
//    case START:
//      break;
//    case OFF:
//      off();
//      FastLED.show();
//      break;
//    default:
//      break;
//  }
}


void parseHeader(State &state, byte header[], int &anim_speed, int &color) {
  if (header[0] == 0xFF) {
    if (header[1] == 0x01) {
      //Get Pattern
      switch (header[2] >> 4) {
        case 0x00:
          state = OFF;
          break;
        case 0x01:
          state = KIT;
          break;
        case 0x02:
          state = RAINBOW_KIT;
          break;
        case 0x03:
          state = CAUTION;
          break;
        case 0x04:
          state = RANDOM;
          break;
        case 0x05:
          state = RANDOM_TRIPLE;
          break;
        case 0x06:
          state = RANDOM_RAINBOW;
          break;
        case 0x07:
          state = RANDOM_TRIPLE_RAINBOW;
          break;
        case 0x08:
          state = MARQUEE;
          break;
        case 0x09:
          state = RAINBOW_MARQUEE;
          break;
        case 0x0A:
          state = CENTER_OUT;
          break;
        case 0x0B:
          state = RAINBOW_CENTER_OUT;
          break;
        case 0x0C:
          state = FADE;
          break;
        case 0x0D:
          state = RAINBOW_FADE;
          break;
        case 0x0E:
          state = BRIGHTNESS;
          break;
        case 0x0F:
          state = DEBUG;
          break;
        default:
          state = START;
          break;
      }

      //Get Animation Speed(1-15)
      if ((header[2] & 0x0F) == 0) {
        anim_speed = 1;
      } else {
        anim_speed = (header[2] & 0x0F);
      }

      //Get Color(0-255)
      color = header[3];

    } else {
      state = START;
    }
  } else {
    state = START;
  }
}


void center_out(uint8_t anim_speed, uint8_t color) {
  for (int i = NUM_LEDS/2; i >= 0; i--) {
    leds[i] = CHSV(color/10, 255, 255);
    
  }
}


void fade(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 100 / anim_speed;
  static int val = 0;
  for (int i = 0; i < 256; i += 3) {
    val += 3;
    if (val > 255) {
      val = 255;
    }
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(color, 255, val);
      FastLED.show();
    }
  }
  for (int i = 256; i > 0; i -= 5) {
    val -= 5;
    if (val < 0) {
      val = 0;
    }
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(color, 255, val);
      FastLED.show();
    }
  }
  delay(temp_speed);
}

void rainbow_fade(uint8_t anim_speed, uint8_t color) {
  static uint8_t hue = color;
  int temp_speed = 100 / anim_speed;
  static int val = 0;
  for (int i = 0; i < 256; i += 3) {
    val += 3;
    if (val > 255) {
      val = 255;
    }
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(hue, 255, val);
      FastLED.show();
      hue++;
    }
  }
  for (int i = 256; i > 0; i -= 5) {
    val -= 5;
    if (val < 0) {
      val = 0;
    }
    for (int j = 0; j < NUM_LEDS; j++) {
      leds[j] = CHSV(hue, 255, val);
      FastLED.show();
      //delay(temp_speed);
      hue--;
    }
  }
  delay(temp_speed);
}


void star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  off();
  leds[random(NUM_LEDS)] = CHSV(color, 255, 255);
  FastLED.show();
  delay(temp_speed);
  off();
  delay(temp_speed);
}


void rainbow_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  off();
  leds[random(NUM_LEDS)] = CHSV(random(255), 255, 255);
  FastLED.show();
  delay(temp_speed);
  off();
  delay(temp_speed);
}

void triple_star(uint8_t anim_speed, uint8_t color) {
  int index = random(NUM_LEDS);
  int temp_speed = 300 / anim_speed;
  off();
  leds[index] = CHSV(color, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(color, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(color, 255, 255);
  FastLED.show();
  delay(temp_speed);
  off();
  delay(temp_speed);
}


void triple_rainbow_star(uint8_t anim_speed, uint8_t color) {
  int index = random(NUM_LEDS);
  int hue = random(color);
  int temp_speed = 300 / anim_speed;
  off();
  leds[index] = CHSV(hue, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(hue, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(hue, 255, 255);
  FastLED.show();
  delay(temp_speed);
  off();
  delay(temp_speed);
}


void marquee(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 100 / anim_speed;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j+k] = CHSV(color, 255, 255);
      }
      FastLED.show();
      delay(temp_speed);

      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j+k] = CHSV(color, 0, 0);
      }
    }
  }
}

void rainbow_marquee(uint8_t anim_speed, uint8_t color) {
  static uint8_t hue = color;
  int temp_speed = 100 / anim_speed;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j+k] = CHSV(hue, 255, 255);
      }
      FastLED.show();
      delay(temp_speed);
      hue = (hue + 1) % 255;

      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j+k] = CHSV(hue, 0, 0);
      }
    }
  }
}


void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(110);
  }
}


void off() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(1);
  }
}

void kit_anim(int anim_speed, int color) {
  static uint8_t hue = 0;
  int temp_speed = 100 / anim_speed;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
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
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
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


void rainbow_kit_anim(int anim_speed) {
  static uint8_t hue = 0;
  int temp_speed = 100 / anim_speed;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
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
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
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

void caution_anim(int anim_speed, int color) {
  int temp_speed = 400 / anim_speed;
  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
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
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 != 0) {
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
