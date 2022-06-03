# CPE461/462-neoherbie
Senior Project

Instructions to flash Herbie:

1. Download the latest Arduino IDE: https://www.arduino.cc/en/software
2. Follow this guide to add the ItsyBitsy compiler to your IDE: https://learn.adafruit.com/introducting-itsy-bitsy-32u4/arduino-ide-setup
3. Download and include the FastLED library: https://github.com/FastLED/FastLED/releases
4. Download the source code from this repository
5. Compile **herbie_led_demo.ino** and upload it to the ItsyBitsy - the LEDs should wait for approximately 5s before displaying either demo mode or a received UART packet!


For testing:

test_driver.ino contains sample commands which are used to change patterns on the LED strip driven by herbie_led_demo.ino.
