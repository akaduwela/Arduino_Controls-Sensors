//Hyperloop Hover Engine Management System
//Kevin Kha
//If using on the Arduino, this should be saved as a .cpp file. Otherwise it should be saved as a .c

#include "HEMS.h"

// Global variables.

HEMS* initialize_HEMS(uint8_t I2C_BUS, uint8_t I2C_DIP) {
  HEMS* engine = malloc(sizeof(HEMS));
  engine->bus = I2C_BUS;
  engine->ADC_0_device_address = ADC_Address_Select[(I2C_DIP >> 6) & 0b11];
  engine->DAC_0_device_address = DAC_Address_Select[(I2C_DIP >> 3) & 0b1];
  engine->IOX_0_device_address = IOX_Address_Select[(I2C_DIP >> 0) & 0b111];

  IOX_setup(engine->IOX_0_device_address);

  return engine;
}

void update_HEMS(HEMS* engine) {
  //Set throttle;
  DAC_write(engine->DAC_0_device_address, map(engine->throttle_voltage, DAC_MIN, DAC_MAX, 0, 4095));

  //Record Temperatures
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    uint16_t ratio = ADC_read(engine->ADC_0_device_address, temp_counter);
    uint16_t thermistance = (4095 - ratio) * REFERENCE_RESISTANCE / ratio;    //Calculate thermistor resistance
    int new_temperature = THERMISTOR_BETA / (log(thermistance) - THERMISTOR_OFFSET) - 272;
    engine->temperatures[temp_counter] = ((100 - THERMISTOR_AVG_WEIGHT) * new_temperature + THERMISTOR_AVG_WEIGHT * engine->temperatures[temp_counter]) / 100;

    if (new_temperature > SAFE_TEMPERATURE)
      engine->alarm |= 0b00000001;
  }

  //Record Motor Controller Current
  int new_amps = (ADC_read(engine->ADC_0_device_address, AMMETER_CHANNEL) * 5000.0 / 4095 - AMMETER_VCC / 2) * AMMETER_CONVERSION;
  engine->amps = new_amps;

  if (new_amps > SAFE_CURRENT)
    engine->alarm |= 0b00000010;

  //Record Motor RPM
  uint16_t current_tachometer_counter = IOX_read(engine->IOX_0_device_address);
  float current_time = runtime();
  uint16_t current_rpm = 60.0 * (current_tachometer_counter - engine->tachometer_counter) / (current_time - engine->timestamp) / TACHOMETER_TICKS;
  engine->rpm = ((100 - TACHOMETER_AVG_WEIGHT) * current_rpm + TACHOMETER_AVG_WEIGHT * engine->rpm) / 100;
  engine->timestamp = current_time;
  engine->tachometer_counter = current_tachometer_counter;
}

uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel) {
#ifdef ARDUINO
  Wire.beginTransmission(ADC_address);
  Wire.write(ADC_CHANNEL_SELECT[ADC_channel]);
  Wire.endTransmission(false);
  Wire.requestFrom(ADC_address, 2, true);
  uint16_t ADC_value = (Wire.read() << 4) | (Wire.read() >> 4);

#else #ifdef LPC


#endif //ARDUINO
  return ADC_value;
}


void IOX_setup(uint8_t IOX_address) {
#ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_IOCONA); //IOCON register location
  Wire.write(IOX_CONFIG);
  Wire.endTransmission(true);

#else #ifdef LPC


#endif //ARDUINO
}

uint16_t IOX_read(uint8_t IOX_address) {
#ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_GPIOA); //GPIOAB register location
  Wire.endTransmission(false);
  Wire.requestFrom(IOX_address, 2, true);
  uint16_t IOX_value = (Wire.read() << 8) | Wire.read();	//A7 A6 A5 A4 A3 A2 A1 A0 B7 B6 B5 B4 B3 B2 B1 B0

#else #ifdef LPC


#endif //ARDUINO
  return IOX_value;
}


void DAC_write(uint8_t DAC_address, uint16_t output_voltage) {
#ifdef ARDUINO
  Wire.beginTransmission(DAC_address);
  Wire.write(DAC_CONFIG | (output_voltage >> 8));   //output the rightmost 8 bits
  Wire.write(output_voltage % 1024);                //output the leftmost 8 bits
  Wire.endTransmission(true);

#else #ifdef LPC


#endif //ARDUINO
}

float runtime() {
  float runtime_in_seconds;
#ifdef ARDUINO
  runtime_in_seconds = micros() / 1000000.0;

#else #ifdef LPC


#endif
  return runtime_in_seconds;
}
