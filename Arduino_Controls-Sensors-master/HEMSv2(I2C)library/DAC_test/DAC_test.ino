#include "Wire.h"

#define DAC_CONFIG 0x00 //0b00000000
uint16_t data = 0;

const uint8_t ADC_Address[4] = {0x8, 0xA, 0x1A, 0x28};
#define ADC_CONFIG 0x22    //0b1???10
#define LTC2309_CHN_0 0x0

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint16_t i; i < 3000; i++) {
    /*
      Serial.print(DAC_CONFIG | (i >> 8), BIN);
      Serial.print("\t");
      Serial.println(byte(i % 1024), BIN);
      //delay(1000);
    */
    Wire.beginTransmission(0x63);
    Wire.write(DAC_CONFIG | (i >> 8));
    Wire.write(i % 1024);
    Wire.endTransmission(true);
    
    Wire.beginTransmission(0x8);
    Wire.write(0x88);
    Wire.endTransmission(false);
    delay(1000);
    Wire.requestFrom(0x8, 2, true);
    uint16_t ADC_data = (Wire.read() << 4) | (Wire.read() >> 4);
    
    Serial.print(i);
    Serial.print("\t");
    Serial.print(analogRead(A0)*4);
    Serial.print("\t");
    Serial.println(ADC_data);
    /**/

  }
}
