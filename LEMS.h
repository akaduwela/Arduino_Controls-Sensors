//Hyperloop Levitation Engine Monitoring System
//Kevin Kha
#include "Arduino.h"

#ifndef LEMS_H_
#define LEMS_H_

//#define thermistor_0 Winding
//#define thermistor_1 Casing
//#define thermistor_2
//#define thermistor_3
//#define thermistor_4
//#define thermistor_5

class LEMS
{
public:
	void select_motor();

private:

	//Pin Assignments
	const int thermistor_0 = A0;
	const int thermistor_1 = A1;
	const int thermistor_2 = A2;
	const int thermistor_3 = A3;
	const int thermistor_4 = A4;
	const int thermistor_5 = A5;
};

struct calibration_data{

}


#endif