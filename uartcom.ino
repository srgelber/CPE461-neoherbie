#include <SoftwareSerial.h>




void setup() {

  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  Serial.println("Goodnight moon!");
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  Serial.print(10);
  delay(1000);
        

}
