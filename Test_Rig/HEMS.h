//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#include "Arduino.h"
#include "math.h"

#ifndef HEMS_H_
#define HEMS_H_

#define NUM_THERMISTORS 4
#define REFERENCE_RESISTANCE 5100 //ohms
#define AMMETER_SENSITIVITY 26.4 //mV/A
#define AMMETER_CONVERSION 0.0379 //A/mV
#define AMMETER_VCC 3300 //mV

//Digital Pin Assignments
#define TACHOMETER_0 2

//Analog Pin Assignments
#define AMMETER 0
#define COILS_FRONT 1
#define COILS_BACK 2
#define INTERIOR_WALL_RIGHT 3
#define INTERIOR_WALL_LEFT 4
const int thermistor_pins[] = {
  COILS_FRONT, COILS_BACK, INTERIOR_WALL_RIGHT, INTERIOR_WALL_LEFT
};

//Safety Thresholds:
#define TEMPERATURE_ALARM 100
#define AMPS_ALARM 70

// Global constants.
#define TACHOMETER_AVG_WEIGHT 70 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100 Set to 0 if you don't want exponential averaging.
#define THERMISTOR_AVG_WEIGHT 0 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100
#define TACHOMETER_HANDLER_OVERHEAD_US 48 //approximate overhead time for 

#define THERMISTOR_BETA 3380
#define THERMISTOR_OFFSET -2.126

extern int error_flag;

// Helper functions.
void record_temperatures(int *temperature_array);
void record_amps(int * recorded_amps);
#endif
