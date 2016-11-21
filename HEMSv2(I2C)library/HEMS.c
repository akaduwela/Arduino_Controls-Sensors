//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.

void initialize_HEMS(){
	#ifdef ARDUINO
	Wire.begin();
	#endif

}

uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel){
	#ifdef ARDUINO

	#else

	#endif
}

void DAC_write(uint8_t DAC_address, uint16_t output_voltage){
	#ifdef ARDUINO
	Wire.beginTransmission(DAC_address);
    Wire.write(output_voltage >> 8);
    Wire.write(output_voltage % 1024);
    Wire.endTransmission();
    #else

    #endif
}

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
