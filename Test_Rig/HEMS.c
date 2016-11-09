//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.
int error_flag = 0;

void record_temperatures(int *temperature_array) {
  unsigned long int ratio, thermistance, temperature;
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    ratio = analogRead(thermistor_pins[temp_counter]);
    thermistance = (1023 - ratio) * REFERENCE_RESISTANCE / ratio;
    temperature = ((100 - THERMISTOR_AVG_WEIGHT) * (THERMISTOR_BETA / (log(thermistance) - THERMISTOR_OFFSET) - 272) + THERMISTOR_AVG_WEIGHT * temperature_array[temp_counter]) / 100;
    temperature_array[temp_counter] = temperature;
    if(temperature > TEMPERATURE_ALARM)
      error_flag = 1;
  }
}

void record_amps(int* recorded_amps) {
  int amps = (analogRead(AMMETER) * 5000.0 / 1023 - AMMETER_VCC / 2) * AMMETER_CONVERSION;
  *recorded_amps = amps;
  if(amps > AMPS_ALARM)
      error_flag = 1;
}
