//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#define CURRENT_ENGINE 0 //0-5

//Uncomment below if calibrating with computer.
//#define CALIBRATION_MODE

#include "HEMS.h"

#define SERIAL_BAUD_RATE 9600

cal_data calibration;

void setup() {
  //Select appropriate calibration data stored in LEMS.h
  calibration = select_engine(CURRENT_ENGINE);

  #ifdef CALIBRATION_MODE
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Hyperloop Hover Engine Monitoring System");
  Serial.println("Calibration Mode Activated");
  Serial.println("Current Calibration Settings:");

  #endif //CALIBRATION_MODE
}

void loop() {
  // put your main code here, to run repeatedly:

}
