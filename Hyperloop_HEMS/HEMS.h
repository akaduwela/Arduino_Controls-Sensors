//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#include "Arduino.h"
#include "math.h"

#include "calibration.h"

#ifndef HEMS_H_
#define HEMS_H_

#define SERIAL_BAUD_RATE 9600

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

// Global constants.
const int beta_values[] = {
	Engine_Calibration_Data.beta_coils_front,
	Engine_Calibration_Data.beta_coils_back,
	Engine_Calibration_Data.beta_interior_wall_right,
	Engine_Calibration_Data.beta_interior_wall_left
};

const float offset_values[] = {
	Engine_Calibration_Data.offset_coils_front,
	Engine_Calibration_Data.offset_coils_back,
	Engine_Calibration_Data.offset_interior_wall_right,
	Engine_Calibration_Data.offset_interior_wall_left
};

const int thermistor_pins[] = {
	COILS_FRONT, COILS_BACK, INTERIOR_WALL_RIGHT, INTERIOR_WALL_LEFT
};

// Helper functions.
void select_engine(int engine);
void record_temperatures();
void print_calibration_settings();
#endif
