//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#include "DAC_shield.h"
#include "Linear_Actuator.h"

extern "C" {
#include "HEMS.h"
}

#define SERIAL_BAUD_RATE 9600

//Pin Assignments
#define THROTTLE_DAC_PORT 0

//Constraints
#define RPM_MIN 0
#define RPM_MAX 255
#define DAC_OUT_MIN 0.00 //Lowest output voltage from DAC
#define DAC_OUT_MAX 3.56 //Highest output voltage from DAC
#define MIN_PERIOD_US 25000

// Helper functions.
void rig_initialize();
void print_amps(int amps);
void print_temperatures(int *recorded_temps);
void print_RPM(int RPM);
void tachometer_handler();
void set_RPM(int target_RPM);
void set_Height(int target_Height);
void emergency_shutdown(int error);
void serialEvent();
