#include "Wire.h"

#define DAC_CONFIG 0x00 //0b01000000
uint16_t data = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint16_t i; i < 4096; i++){
    /*
    Serial.print(DAC_CONFIG | (i >> 8), BIN);
    Serial.print("\t");
    Serial.println(byte(i % 1024), BIN);
    //delay(1000);
    */
    Wire.beginTransmission(0x63);
    Wire.write(i >> 8);
    Wire.write(i % 1024);
    Wire.endTransmission();
    Serial.println(analogRead(A0));
    /**/
  }
}
