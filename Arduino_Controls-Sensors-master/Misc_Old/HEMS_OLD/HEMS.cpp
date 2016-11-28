//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.
int recorded_temp[NUM_THERMISTORS];
int recorded_amps = 0;
unsigned long int current_time_us = 0;
unsigned long int previous_time_us = 0;
volatile unsigned int tach_period_us = 0;

void tachometer_handler() {
  //This function uses micros(), which overflows (resets back to 0) after ~70 minutes.
  current_time_us = micros();
  tach_period_us = (tach_period_us * TACHOMETER_AVG_WEIGHT + (10 - TACHOMETER_AVG_WEIGHT) * (current_time_us - previous_time_us)) / 10;
  previous_time_us = current_time_us + TACHOMETER_HANDLER_OVERHEAD_US;
}

void record_temperatures() {
  unsigned long int ratio, thermistance;
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    ratio = analogRead(thermistor_pins[temp_counter]);
    thermistance = (1023 - ratio) * REFERENCE_RESISTANCE / ratio;
    recorded_temp[temp_counter] = ((100 - THERMISTOR_AVG_WEIGHT) * (beta_values[temp_counter] / (log(thermistance) - offset_values[temp_counter]) - 273) + THERMISTOR_AVG_WEIGHT * recorded_temp[temp_counter]) / 100;
  }
}

void record_amps() {
  recorded_amps = (analogRead(AMMETER) * 5000.0 / 1023 - AMMETER_VCC / 2) * AMMETER_CONVERSION;
}

void print_amps(){
  Serial.print(recorded_amps);
  Serial.print("A\t");
}

void print_temperatures() {
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    Serial.print(recorded_temp[temp_counter]);
    Serial.print("C\t");
  }
}

void print_RPM() {
  Serial.print(tach_period_us);
  Serial.print("RPM\t");
}

void print_calibration_settings() {
  Serial.print("Calibration settings for Engine ");
  Serial.println(ENGINE_NUMBER);

  Serial.print("beta_coils_front:\t");
  Serial.println(Engine_Calibration_Data.beta_coils_front);
  Serial.print("beta_coils_back:\t");
  Serial.println(Engine_Calibration_Data.beta_coils_back);
  Serial.print("beta_interior_wall_right:\t");
  Serial.println(Engine_Calibration_Data.beta_interior_wall_right);
  Serial.print("beta_interior_wall_left:\t");
  Serial.println(Engine_Calibration_Data.beta_interior_wall_left);

  Serial.print("offset_coils_front:\t");
  Serial.println(Engine_Calibration_Data.offset_coils_front, 3);
  Serial.print("offset_coils_back:\t");
  Serial.println(Engine_Calibration_Data.offset_coils_back, 3);
  Serial.print("offset_interior_wall_right:\t");
  Serial.println(Engine_Calibration_Data.offset_interior_wall_right, 3);
  Serial.print("offset_interior_wall_left:\t");
  Serial.println(Engine_Calibration_Data.offset_interior_wall_left, 3);
}

