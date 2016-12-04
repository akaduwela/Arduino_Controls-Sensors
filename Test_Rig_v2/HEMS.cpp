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

  IOX_setup(engine->bus, engine->IOX_0_device_address);

  engine->throttle_voltage = 0;
  engine->timestamp = 0;
  engine->tachometer_counter = 0;
  engine->alarm = 0;

  return engine;
}

void update_HEMS(HEMS* engine) {
  //Set throttle;
  DAC_write(engine->bus, engine->DAC_0_device_address, engine->throttle_voltage * 4095 / 5);

  //Record Temperatures
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    float ratio = ADC_read(engine->bus, engine->ADC_0_device_address, temp_counter);

    //Calculate thermistor resistance
    float thermistance = (4095 - ratio) * REFERENCE_RESISTANCE / ratio;

    //Calculate temperature based on the thermistor resistance (formula based on https://en.wikipedia.org/wiki/Thermistor#B_or_.CE.B2_parameter_equation and datasheet values)
    int new_temperature = THERMISTOR_BETA / (log(thermistance) - THERMISTOR_OFFSET) - 272;

    //Exponential average and record new temperature
    engine->temperatures[temp_counter] = ((1 - THERMISTOR_AVG_WEIGHT) * new_temperature + THERMISTOR_AVG_WEIGHT * engine->temperatures[temp_counter]);

    if (new_temperature > SAFE_TEMPERATURE)
      engine->alarm |= 0b00000001;
  }

  //Record Motor Controller Current
  //With no current, the ACS759x150B should output 3.3V/2
  uint16_t blah = ADC_read(engine->bus, engine->ADC_0_device_address, AMMETER_CHANNEL);
  int new_amps = abs(blah * 5000.0 / 4095 - 1000 * AMMETER_VCC / 2) * AMMETER_CONVERSION; //Done in mV
  engine->amps = new_amps;

  if (new_amps > SAFE_CURRENT)
    engine->alarm |= 0b00000010;

  //Record Motor RPM
  uint16_t current_tachometer_counter = IOX_read(engine->bus, engine->IOX_0_device_address);
  float current_time = runtime();
  uint16_t current_rpm = 60.0 / TACHOMETER_TICKS * (current_tachometer_counter - engine->tachometer_counter) / (current_time - engine->timestamp);
  engine->rpm = (1 - TACHOMETER_AVG_WEIGHT) * current_rpm + TACHOMETER_AVG_WEIGHT * engine->rpm;
  engine->timestamp = current_time;
  engine->tachometer_counter = current_tachometer_counter;
}

uint16_t ADC_read(uint8_t bus, uint8_t ADC_address, uint8_t ADC_channel) {
  uint8_t input_buffer[2];

#ifdef ARDUINO
  Wire.beginTransmission(ADC_address);
  Wire.write(ADC_CHANNEL_SELECT[ADC_channel]);
  Wire.endTransmission(true);
  Wire.requestFrom(ADC_address, 2, true);
  input_buffer[0] = Wire.read();  //D11 D10 D9 D8 D7 D6 D5 D4
  input_buffer[1] = Wire.read();  //D3 D2 D1 D0 X X X X
#else #ifdef LPC
  Chip_I2C_MasterRead(I2C_ID_SELECT[bus], ADC_address, input_buffer, 2);
#endif //ARDUINO

  uint16_t ADC_value = (input_buffer[0] << 4) | (input_buffer[1] >> 4);
  return ADC_value;
}




void DAC_write(uint8_t bus, uint8_t DAC_address, uint16_t output_voltage) {
  uint8_t output_buffer[2] = {DAC_CONFIG | (output_voltage >> 8), output_voltage % 256};

#ifdef ARDUINO
  Wire.beginTransmission(DAC_address);
  Wire.write(output_buffer, 2);   //output the two bytes
  Wire.endTransmission(true);
#else #ifdef LPC
  Chip_I2C_MasterSend(I2C_ID_SELECT[bus], DAC_address, output_buffer, 2);
#endif //ARDUINO

}




void IOX_setup(uint8_t bus, uint8_t IOX_address) {
  uint8_t output_buffer[2] = {MCP23017_IOCONA, IOX_CONFIG};

#ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(output_buffer, 2); //IOCON register location, Configuration Byte
  Wire.endTransmission(true);
#else #ifdef LPC
  Chip_I2C_MasterSend(I2C_ID_SELECT[bus], IOX_address, output_buffer, 2);
#endif //ARDUINO

}

uint16_t IOX_read(uint8_t bus, uint8_t IOX_address) {
  uint8_t input_buffer[2];

#ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_GPIOA); //GPIOAB register location
  Wire.endTransmission(false);
  Wire.requestFrom(IOX_address, 2, true);
  input_buffer[0] = Wire.read();	//A7 A6 A5 A4 A3 A2 A1 A0
  input_buffer[1] = Wire.read();  //B7 B6 B5 B4 B3 B2 B1 B0
#else #ifdef LPC
  Chip_I2C_MasterRead(I2C_ID_SELECT[bus], IOX_address, input_buffer, 2);
#endif //ARDUINO

  uint16_t IOX_value = (input_buffer[0] << 8) | (input_buffer[1] >> 0);
  return IOX_value;
}



float runtime() {
  float runtime_in_seconds;

#ifdef ARDUINO
  runtime_in_seconds = millis() / 1000.0;
#else #ifdef LPC

#endif

  return runtime_in_seconds;
}
