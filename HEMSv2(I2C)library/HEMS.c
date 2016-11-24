//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.

void initialize_HEMS(){
	#ifdef ARDUINO
	Wire.begin();

	#else //LPC code


	#endif //ARDUINO
}

uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel){
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


void IOX_setup(uint8_t IOX_address){
	#ifdef ARDUINO
	Wire.beginTransmission(IOX_address);
	Wire.write(MCP23017_IOCONA); //IOCON register location
	Wire.write(IOX_CONFIG);
	Wire.endTransmission(true);
	
	#else //LPC code

	#endif //ARDUINO
}

uint16_t IOX_read(uint8_t IOX_address){
  #ifdef ARDUINO
  Wire.beginTransmission(IOX_address);
  Wire.write(MCP23017_GPIOA); //GPIOAB register location
  Wire.endTransmission(false);
  Wire.requestFrom(IOX_address, 2, true);
  uint16_t IOX_value = (Wire.read() << 8) | Wire.read();	//A7 A6 A5 A4 A3 A2 A1 A0 B7 B6 B5 B4 B3 B2 B1 B0
  #else //LPC code

  #endif //ARDUINO
  return IOX_value;
}


void DAC_write(uint8_t DAC_address, uint16_t output_voltage){
	#ifdef ARDUINO
	Wire.beginTransmission(DAC_address);
    Wire.write(DAC_CONFIG | (output_voltage >> 8));
    Wire.write(output_voltage % 1024);
    Wire.endTransmission(true);
    
    #else //LPC code

    #endif //ARDUINO
}

/*
void record_temperatures(int *temperature_array) {
  unsigned long int ratio, thermistance;
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    ratio = analogRead(thermistor_pins[temp_counter]);
    thermistance = (1023 - ratio) * REFERENCE_RESISTANCE / ratio;
    temperature_array[temp_counter] = ((100 - THERMISTOR_AVG_WEIGHT) * (THERMISTOR_BETA / (log(thermistance) - THERMISTOR_OFFSET) - 272) + THERMISTOR_AVG_WEIGHT * temperature_array[temp_counter]) / 100;
  }
}

void record_amps(int* recorded_amps) {
  *recorded_amps = (analogRead(AMMETER) * 5000.0 / 1023 - AMMETER_VCC / 2) * AMMETER_CONVERSION;
}
*/