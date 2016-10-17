//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#include "Arduino.h"
#include "math.h"

#ifndef HEMS_H_
#define HEMS_H_

#define CURRENT_ENGINE 0 //Select which engine

//Uncomment below if calibrating with computer.
//#define CALIBRATION_MODE

#define NUM_THERMISTORS 4
#define REFERENCE_RESISTANCE 20000 //ohms

//Pin Assignments
#define COILS_FRONT A0
#define COILS_BACK A1
#define INTERIOR_WALL_RIGHT A2
#define INTERIOR_WALL_LEFT A3
//#define THERMISTOR_4 A4
//#define THERMISTOR_5 A5

#define TACHOMETER_0 2
//#define TACHOMETER_1 3

const int thermistor_pins[NUM_THERMISTORS] = {COILS_FRONT, COILS_BACK, INTERIOR_WALL_RIGHT, INTERIOR_WALL_LEFT};

struct cal_data {
  //beta Constants (Default = 3380)
  int beta_coils_front;
  int beta_coils_back;
  int beta_interior_wall_right;
  int beta_interior_wall_left;
  //int beta_thermistor_4;
  //int beta_thermistor_5;

  //lnrinf Constants (Default = -2.126):
  float offset_coils_front;
  float offset_coils_back;
  float offset_interior_wall_right;
  float offset_interior_wall_left;
  //float offset_thermistor_4;
  //float offset_thermistor_5;
} ;

//Stored Calibration Data:
const cal_data Engine_0_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};

const cal_data Engine_1_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_2_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_3_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_4_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_5_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_6_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };
  
const cal_data Engine_7_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
  };


//Helper Functions:
void select_engine(int engine);
void record_temperatures();

#endif
