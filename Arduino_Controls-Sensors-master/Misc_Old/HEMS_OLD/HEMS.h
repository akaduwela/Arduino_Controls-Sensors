//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#include "Arduino.h"[
#include "math.h"
#include "DAC_shield.h"

#include "calibration.h"

#ifndef HEMS_H_
#define HEMS_H_

#define SERIAL_BAUD_RATE 9600

#define NUM_THERMISTORS 4
#define REFERENCE_RESISTANCE 5100 //ohms
#define AMMETER_SENSITIVITY 26.4 //mV/A
#define AMMETER_CONVERSION 1/AMMETER_SENSITIVITY
#define AMMETER_VCC 3.3

//Pin Assignments
#define TACHOMETER_0 2
#define AMMETER A0
#define COILS_FRONT A1
#define COILS_BACK A2
#define INTERIOR_WALL_RIGHT A3
#define INTERIOR_WALL_LEFT A4
#define LINEAR_FEEDBACK A5


#define THROTTLE_DAC_PORT 2


// Global constants.
#define TACHOMETER_AVG_WEIGHT 20 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100 Set to 0 if you don't want exponential averaging.
#define THERMISTOR_AVG_WEIGHT 20 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100
#define TACHOMETER_HANDLER_OVERHEAD_US 0 //approximate overhead time for 

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
void record_amps();
void print_amps();
void print_motor_current();
void print_temperatures();
void print_RPM();
void print_calibration_settings();
void tachometer_handler();
#endif
