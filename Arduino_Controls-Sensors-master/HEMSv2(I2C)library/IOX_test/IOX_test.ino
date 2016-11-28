#include "Wire.h"
#include "HEMS.h"

#define ARDUINO

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  IOX_setup(0x20);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(IOX_read(0x20));
  delay(1000);
}
