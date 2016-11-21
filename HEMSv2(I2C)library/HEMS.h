//Hyperloop Hover Engine Monitoring System
//Kevin Kha
#define Arduino
#ifdef Arduino
#include "Arduino.h"
#include "Wire.h"
#endif

#include "math.h"

#ifndef HEMS_H_
#define HEMS_H_

#define NUM_THERMISTORS 4
#define REFERENCE_RESISTANCE 5100 //ohms
#define AMMETER_SENSITIVITY 26.4 //mV/A
#define AMMETER_CONVERSION 1/AMMETER_SENSITIVITY
#define AMMETER_VCC 3.3

//Digital Pin Assignments
#define TACHOMETER_0 2

//ADC Channel Assignments
#define COILS_FRONT 0
#define COILS_BACK 1
#define INTERIOR_WALL_RIGHT 2
#define INTERIOR_WALL_LEFT 3
#define AMMETER 4

//Global Constants:
#define TACHOMETER_AVG_WEIGHT 40 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100 Set to 0 if you don't want exponential averaging.
#define THERMISTOR_AVG_WEIGHT 40 //Out of 100 (value = (old_value * AVG_WEIGHT + (100 - AVG_WEIGHT) * new_value)/100
#define TACHOMETER_HANDLER_OVERHEAD_US 0 //approximate overhead time for 

#define THERMISTOR_BETA 3380
#define THERMISTOR_OFFSET -2.126

void initialize_HEMS();
uint16_t ADC_read(uint8_t ADC_address, uint8_t ADC_channel);
uint16_t IOX_read(uint8_t IOX_address);
void DAC_write(uint8_t DAC_address, uint16_t output_voltage);

//Functions Declarations:
void record_temperatures(int *temperature_array);
void record_amps(int * recorded_amps);
#endif
