//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.

void initialize_HEMS(){
	Wire.begin();

}

void read_ADC(ADC myadc, int *analog_data_array){
	Wire.beginTransmission(myadc->ADC_DEVICE_ADDRESS);
	Wire.write(ANALOG_DATA_ADDRESS);
	Wire.endTransmission(0);
	Wire.requestFrom(myadc->ADC_DEVICE_ADDRESS, NUMBER_OF_BYTES, 1);
	
}

/*
void write_DAC(DAC mydac, int output){
	Wire.beginTransmission(mydac->DAC_DEVICE_ADDRESS);
	Wire.write(ANALOG_OUTPUT_ADDRESS);
	Wire.write(output);
	Wire.endTransmission(0);
}
*/

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
