#include "Wire.h"

#define ARDUINO

#define DAC_CONFIG 0x00 //0b00000000
uint16_t data = 0;

const uint8_t ADC_Address[4] = {0x8, 0xA, 0x1A, 0x28};

#define NUM_CELLS 6


// LTC2309 I2C Address                 //  AD1       AD0

// #define LTC2309_I2C_ADDRESS 0x08    //  LOW       LOW
// #define LTC2309_I2C_ADDRESS 0x09    //  LOW       Float
// #define LTC2309_I2C_ADDRESS 0x0A    //  LOW       HIGH
// #define LTC2309_I2C_ADDRESS 0x0B    //  Float     HIGH
// #define LTC2309_I2C_ADDRESS 0x18    //  Float     Float
// #define LTC2309_I2C_ADDRESS 0x19    //  Float     LOW
// #define LTC2309_I2C_ADDRESS 0x1A    //  HIGH      LOW
// #define LTC2309_I2C_ADDRESS 0x1B    //  HIGH      Float
// #define LTC2309_I2C_ADDRESS 0x28    //  High      HIGH

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

uint8_t I2C_ADC_Maglev_BMS_Addresses[3] = {0x19, 0x0B, 0x18};
float cell_voltages[3][NUM_CELLS];
float battery_voltage[3];
float conversion[3][6] = {
  {2.0, 2.0, 3.0, 4.0, 5.02, 5.99},
  {2.0, 2.0, 3.0, 4.0, 5.02, 5.99},
  {2.0, 2.0, 3.0, 4.0, 5.02, 5.99}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
}

void loop() {
  int batt, i, cell;
  float voltages[6];
  float prev_voltage;

  //0x19 FLOAT LOW
  //0x0B FLOAT HIGH
  //0x18 FLOAT FLOAT
  for (batt = 0; batt < 3; batt++) {
    prev_voltage = 0;
    for (i = 0; i < 6; i++) {
      voltages[i] = ADC_read(I2C_ADC_Maglev_BMS_Addresses[batt], i) / 4096.0 * 5.0 * conversion[batt][i];
//      Serial.print(voltages[i]);
//      Serial.print("\t");
      cell_voltages[batt][i] = voltages[i] - prev_voltage;
      prev_voltage = voltages[i];
    }
    battery_voltage[batt] = prev_voltage;
    for (cell = 0; cell < NUM_CELLS; cell++) {
      Serial.print(cell_voltages[batt][cell]);
      Serial.print(" ");
    }
    Serial.print("\t");
  }
  Serial.print("\n");
  /**/



  delay(50);
}

//int calculate_temperature(uint16_t therm_adc_val) {
//  //Calculate thermistor resistance
//  float thermistance = therm_adc_val / 4095.0 * REFERENCE_RESISTANCE / (1 - therm_adc_val / 4095.0);
//
//  //Calculate temperature based on the thermistor resistance (formula based on https://en.wikipedia.org/wiki/Thermistor#B_or_.CE.B2_parameter_equation and datasheet values)
//  return THERMISTOR_BETA / (log(thermistance) - THERMISTOR_OFFSET) - 272;
//}

uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel) {
  uint8_t input_buffer[2];

  Wire.beginTransmission(ADC_address);
  Wire.write(ADC_CHANNEL_SELECT[ADC_channel]);
  Wire.endTransmission(true);
  Wire.requestFrom(ADC_address, 2, true);
  input_buffer[0] = Wire.read();  //D11 D10 D9 D8 D7 D6 D5 D4
  input_buffer[1] = Wire.read();  //D3 D2 D1 D0 X X X X

  uint16_t ADC_value = (input_buffer[0] << 4) | (input_buffer[1] >> 4);
  return ADC_value;
}
