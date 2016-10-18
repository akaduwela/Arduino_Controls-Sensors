//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

// Global variables.
int recorded_temp[NUM_THERMISTORS];
int res_ref;

void record_temperatures() {
  int ratio, thermistance;
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    ratio = map(analogRead(thermistor_pins[temp_counter]), 0, 1023, 0, 100);
    thermistance = (100 - ratio) * REFERENCE_RESISTANCE / ratio;
    recorded_temp[temp_counter] = (8 * (beta_values[temp_counter] / (log(thermistance) - offset_values[temp_counter]) - 273) + 2 * recorded_temp[temp_counter]) / 10;
  }
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

