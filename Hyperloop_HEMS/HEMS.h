//Hyperloop Levitation Engine Monitoring System
//Kevin Kha
#include "Arduino.h"

#ifndef HEMS_H_
#define HEMS_H_

//Pin Assignments
#define THERMISTOR_0 A0
#define THERMISTOR_1 A1
#define THERMISTOR_2 A2
#define THERMISTOR_3 A3
//#define THERMISTOR_4 A4
//#define THERMISTOR_5 A5

#define TACHOMETER_0 2
//#define TACHOMETER_1 3

struct cal_data {
} ;


//Stored Calibration Data:
const cal_data Engine_0_Calibration_Data = {};
const cal_data Engine_1_Calibration_Data = {};
const cal_data Engine_2_Calibration_Data = {};
const cal_data Engine_3_Calibration_Data = {};
const cal_data Engine_4_Calibration_Data = {};
const cal_data Engine_5_Calibration_Data = {};
const cal_data Engine_6_Calibration_Data = {};
const cal_data Engine_7_Calibration_Data = {};


//Helper Functions:
cal_data select_engine(int engine);

#endif
