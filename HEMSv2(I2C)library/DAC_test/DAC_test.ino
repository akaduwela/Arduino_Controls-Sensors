#include "Wire.h"

#define ARDUINO

#define DAC_CONFIG 0x00 //0b00000000
uint16_t data = 0;

const uint8_t ADC_Address[4] = {0x8, 0xA, 0x1A, 0x28};
#define ADC_CONFIG 0x88    //0b1???10XX

// Single-Ended Channel Configuration
#define LTC2309_CHN_0 0x80
#define LTC2309_CHN_1 0xC0
#define LTC2309_CHN_2 0x90
#define LTC2309_CHN_3 0xD0
#define LTC2309_CHN_4 0xA0
#define LTC2309_CHN_5 0xE0
#define LTC2309_CHN_6 0xB0
#define LTC2309_CHN_7 0xF0

//To select the channel, we can OR ADC_CONFIG with channel selection bits.
const uint8_t ADC_CHANNEL_SELECT[8] = {
  LTC2309_CHN_0 | ADC_CONFIG,
  LTC2309_CHN_1 | ADC_CONFIG,
  LTC2309_CHN_2 | ADC_CONFIG,
  LTC2309_CHN_3 | ADC_CONFIG,
  LTC2309_CHN_4 | ADC_CONFIG,
  LTC2309_CHN_5 | ADC_CONFIG,
  LTC2309_CHN_6 | ADC_CONFIG,
  LTC2309_CHN_7 | ADC_CONFIG
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint16_t i; i < 4096; i++) {
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

    uint16_t ADC_data = ADC_read(ADC_Address[3], 0);

    Serial.print(i);
    Serial.print("\t");
    Serial.print(analogRead(A0) * 4);
    Serial.print("\t");
    Serial.println(ADC_data);
    /**/
    delay(50);
  }
}

uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel) {
#ifdef ARDUINO
  Wire.beginTransmission(ADC_address);
  Wire.write(ADC_CHANNEL_SELECT[ADC_channel]);
  Wire.endTransmission(false);
  Wire.requestFrom(ADC_address, 2, true);
  uint16_t ADC_value = (Wire.read() << 4) | (Wire.read() >> 4);

#else //LPC code

#endif
  return ADC_value;
}
