#include <FastLED.h>
#include <SoftwareSerial.h>

// How many leds in your strip?
#define NUM_LEDS 9

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 7
#define BRIGHTNESS_VAL  80

// Define the array of leds
CRGB leds[NUM_LEDS];
byte header[5];
SoftwareSerial COM(10, 11);

enum State {
  START, OFF, KITT, RAINBOW_KITT, CAUTION,
  RANDOM, RANDOM_TRIPLE, RANDOM_RAINBOW, RANDOM_TRIPLE_RAINBOW,
  MARQUEE, RAINBOW_MARQUEE,
  CENTER_OUT, RAINBOW_CENTER_OUT,
  FADE, RAINBOW_FADE,
  BRIGHTNESS, DEBUG
};


void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS_VAL);
  Serial.begin(57600);
  COM.begin(57600);
  randomSeed(analogRead(A0));
}


void loop() {
  static State state = START;
  static uint8_t anim_speed = 1;
  static uint8_t color = 0;
  static uint8_t brightness = BRIGHTNESS_VAL;
  static uint8_t battery_life = 70;
  static uint8_t _;
  
  off(_, _);
  FastLED.show();

  memset(&header, 0, sizeof(header));

  if (COM.available()) {
    for (int i = 0; i < 4; i++) {
      header[i] = COM.read();
    }
    parseHeader(state, header, anim_speed, color);
  }

  switch (state) {
    case START:
      demo_mode();
      break;
    case OFF:
      off(_, _);
      FastLED.show();
      break;
    case KITT:
      kitt_anim(anim_speed, color);
      break;
    case RAINBOW_KITT:
      rainbow_kitt_anim(anim_speed, _);
    case CAUTION:
      caution_anim(anim_speed, color);
      break;
    case RANDOM:
      star(anim_speed, color);
      break;
    case RANDOM_TRIPLE:
      triple_star(anim_speed, color);
      break;
    case RANDOM_RAINBOW:
      rainbow_star(anim_speed, color);
      break;
    case RANDOM_TRIPLE_RAINBOW:
      rainbow_triple_star(anim_speed, color);
      break;
    case MARQUEE:
      marquee(anim_speed, color);
      break;
    case RAINBOW_MARQUEE:
      rainbow_marquee(anim_speed, color);
      break;
    case CENTER_OUT:
      middle_kitt_anim(anim_speed, color);
      break;
    case RAINBOW_CENTER_OUT:
      break;
    case FADE:
      fade(anim_speed, color);
      break;
    case RAINBOW_FADE:
      rainbow_fade(anim_speed, color);
      break;
    case BRIGHTNESS:
      set_brightness(anim_speed, _);
      break;
    case DEBUG:
      debug_mode(anim_speed, _);
      break;
    default:
      demo_mode();
      break;
  }
}


void parseHeader(State &state, byte header[], uint8_t &anim_speed, uint8_t &color) {
  if (header[0] == 0xFF) {
    if (header[1] == 0x01) {
      //Get Pattern
      switch (header[2] >> 4) {
        case 0x00:
          state = OFF;
          break;
        case 0x01:
          state = KITT;
          break;
        case 0x02:
          state = RAINBOW_KITT;
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


// Declare the type of function pointers.
// Here a function that takes two ints and returns an int.
typedef void (*funptr) (uint8_t, uint8_t);

// The array with all the functions.
funptr patterns[] = {
    kitt_anim,
    rainbow_kitt_anim,
    caution_anim,
    star,
    triple_star,
    rainbow_star,
    rainbow_triple_star,
    marquee,
    rainbow_marquee,
    middle_kitt_anim,
    fade,
    rainbow_fade,
    debug_mode,
};


void demo_mode() {
  static int i = 0;
  for (int j = 0; j < random(2, 6); j++) {
    patterns[i](random(5), random(255));
  }
  FastLED.show();
  i = (i + 1) % 13;
}


void off(uint8_t anim_speed, uint8_t color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(1);
  }
}


void kitt_anim(uint8_t anim_speed, uint8_t color) {
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


void rainbow_kitt_anim(uint8_t anim_speed, uint8_t color) {
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


void caution_anim(uint8_t anim_speed, uint8_t color) {
  uint8_t _;
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
  off(_, _);
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
  off(_, _);
  // Wait a little bit before we loop around and do it again
  delay(temp_speed);
}


void star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  leds[random(NUM_LEDS)] = CHSV(color, 255, 255);
  FastLED.show();
  delay(temp_speed);
  fadeall();
  delay(temp_speed);
}


void triple_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  int num1 = random(NUM_LEDS);
  int num2 = random(NUM_LEDS);
  int num3 = random(NUM_LEDS);
  int rainbow = random(255);
  //leds[i] = CHSV(random(255), 255, 255);

  for (int x = 0; x < 255; x++) {
    leds[num1] = CHSV(color, 255, x);
    leds[num2] = CHSV(color, 255, x);
    leds[num3] = CHSV(color, 255, x);
    FastLED.show();

  }
  for (int x = 255; x >= 0; x--) {
    leds[num1] = CHSV(color, 255, x);
    leds[num2] = CHSV(color, 255, x);
    leds[num3] = CHSV(color, 255, x);
    FastLED.show();

  }
}


void rainbow_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  leds[random(NUM_LEDS)] = CHSV(random(255), 255, 255);
  FastLED.show();
  delay(temp_speed);
  fadeall();
  delay(temp_speed);
}


void rainbow_triple_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  int num1 = random(NUM_LEDS);
  int num2 = random(NUM_LEDS);
  int num3 = random(NUM_LEDS);
  int rainbow = random(255);
  //leds[i] = CHSV(random(255), 255, 255);

  for (int x = 0; x < 255; x++) {
    leds[num1] = CHSV(rainbow, 255, x);
    leds[num2] = CHSV(rainbow, 255, x);
    leds[num3] = CHSV(rainbow, 255, x);
    FastLED.show();

  }
  for (int x = 255; x >= 0; x--) {
    leds[num1] = CHSV(rainbow, 255, x);
    leds[num2] = CHSV(rainbow, 255, x);
    leds[num3] = CHSV(rainbow, 255, x);
    FastLED.show();

  }
}


void marquee(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 100 / anim_speed;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j + k] = CHSV(color, 255, 255);
      }
      FastLED.show();
      delay(temp_speed);

      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j + k] = CHSV(color, 0, 0);
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
        leds[j + k] = CHSV(hue, 255, 255);
      }
      FastLED.show();
      delay(temp_speed);
      hue = (hue + 1) % 255;

      for (int k = 0; k < NUM_LEDS; k += 3) {
        leds[j + k] = CHSV(hue, 0, 0);
      }
    }
  }
}


void middle_kitt_anim(int anim_speed, int color) {
  static uint8_t hue = 0;
  int temp_speed = 85 / anim_speed;
  int i = 0;
  int left = 4;
  int right = 4;
  // First slide the led in one direction
  while (i < 4) {
    // Set the i'th led to red
    leds[left] = CHSV(color, 255, 255);
    leds[right] = CHSV(color, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
    left--;
    right++;
    i++;
  }

  int j = 0;
  // Now go in the other direction.
  while (j < 4) {
    // Set the i'th led to red
    leds[left] = CHSV(color, 255, 255);
    leds[right] = CHSV(color, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, reset the i'th led to black
    // leds[i] = CRGB::Black;
    fadeall();
    // Wait a little bit before we loop around and do it again
    delay(temp_speed);
    left++;
    right--;
    j++;
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


void set_brightness(uint8_t brightness, uint8_t color) {
  FastLED.setBrightness(brightness);
  FastLED.show();
}


void debug_mode(uint8_t battery_life, uint8_t color) {
  int battery = int(battery_life) / 10;
  for (int i = 0; i < battery; i++) {
    leds[i] = CHSV(92, 255, 255);
    FastLED.show();
  }
}


// helper function
void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(110);
  }
}


// currently unused
void center_out(uint8_t anim_speed, uint8_t color) {
  for (int i = NUM_LEDS / 2; i >= 0; i--) {
    leds[i] = CHSV(color / 10, 255, 255);

  }
}


void single_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  int i = random(NUM_LEDS);
  int rainbow = random(255);
  //leds[i] = CHSV(random(255), 255, 255);

  for (int x = 0; x < 255; x++) {
    leds[i] = CHSV(color, 255, x);
    FastLED.show();

  }
  for (int x = 255; x >= 0; x--) {
    leds[i] = CHSV(color, 255, x);
    FastLED.show();

  }
}


void rainbow_single_star(uint8_t anim_speed, uint8_t color) {
  int temp_speed = 300 / anim_speed;
  int i = random(NUM_LEDS);
  int rainbow = random(255);
  //leds[i] = CHSV(random(255), 255, 255);

  for (int x = 0; x < 255; x++) {
    leds[i] = CHSV(rainbow, 255, x);
    FastLED.show();

  }
  for (int x = 255; x >= 0; x--) {
    leds[i] = CHSV(rainbow, 255, x);
    FastLED.show();

  }
}


void triple_rainbow_star(uint8_t anim_speed, uint8_t color) {
  uint8_t _;
  int index = random(NUM_LEDS);
  int hue = random(color);
  int temp_speed = 300 / anim_speed;
  off(_, _);
  leds[index] = CHSV(hue, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(hue, 255, 255);
  index = (index + 1) % NUM_LEDS;
  leds[index] = CHSV(hue, 255, 255);
  FastLED.show();
  delay(temp_speed);
  off(_, _);
  delay(temp_speed);
}
