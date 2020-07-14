
// this code is written to check the send function designed for msp430.
// arduino with pc: 115200 baudrate
//arduino with msp430: 9600 baudrate
// msp430g2553 cannot with with higher baudrate than 9600

#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX


void setup() {
  
  // put your setup code here, to run once:
  
  mySerial.begin(9600);
  Serial.begin(115200);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
  
}
