//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

int beta_values[NUM_THERMISTORS];
float offset_values[NUM_THERMISTORS];
int recorded_temp[NUM_THERMISTORS];
int res_ref;

void select_engine(int engine) {
  cal_data selected_engine;
  switch (engine) {
    case 0 : selected_engine = Engine_0_Calibration_Data;
    case 1 : selected_engine = Engine_1_Calibration_Data;
    case 2 : selected_engine = Engine_2_Calibration_Data;
    case 3 : selected_engine = Engine_3_Calibration_Data;
    case 4 : selected_engine = Engine_4_Calibration_Data;
    case 5 : selected_engine = Engine_5_Calibration_Data;
    case 6 : selected_engine = Engine_6_Calibration_Data;
    case 7 : selected_engine = Engine_7_Calibration_Data;
  }
  //Retrieve beta values
  beta_values[0] = selected_engine.beta_coils_front;
  beta_values[1] = selected_engine.beta_coils_back;
  beta_values[2] = selected_engine.beta_interior_wall_right;
  beta_values[3] = selected_engine.beta_interior_wall_left;

  //Retrieve offset values
  offset_values[0] = selected_engine.offset_coils_front;
  offset_values[1] = selected_engine.offset_coils_back;
  offset_values[2] = selected_engine.offset_interior_wall_right;
  offset_values[3] = selected_engine.offset_interior_wall_left;
}

void record_temperatures() {
  int ratio, thermistance;
  for (int temp_counter = 0; temp_counter < NUM_THERMISTORS; temp_counter++) {
    ratio = map(analogRead(thermistor_pins[temp_counter]), 0, 1023, 0, 100);
    thermistance = (100 - ratio) * REFERENCE_RESISTANCE / ratio;
    recorded_temp[temp_counter] = (8 * (beta_values[temp_counter] / (log(thermistance) - offset_values[temp_counter]) - 273) + 2 * recorded_temp[temp_counter]) / 10;
  }
}

