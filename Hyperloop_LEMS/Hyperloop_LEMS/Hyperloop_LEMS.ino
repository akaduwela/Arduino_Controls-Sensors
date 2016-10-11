//Hyperloop Maglev Engine Monitoring System
//Kevin Kha
//
#include "calibration_data.h"

#define 

#define CURRENT_MOTOR cal_data_0

// 0-5
#define CALIBRATION_MOTOR //Motor 0

#define CALIBRATION_MOTOR_1
#define CALIBRATION_MOTOR_2
#define CALIBRATION_MOTOR_3
#define CALIBRATION_MOTOR_4
#define CALIBRATION_MOTOR_5
#define CALIBRATION_MOTOR_6
#define CALIBRATION_MOTOR_7

#if (CALIBRATION_MOTOR == 0)

#define CURRENT_MOTOR MOTOR_1

#define MOTOR_1 1
#define MOTOR_2 2
#define MOTOR_3 3

#define MOTOR_1_ADD_CALIBRATION 5
#define MOTOR_2_ADD_CALIBRATION 6

int getAddCalibrate(int sensorNum) {
  int result;
  switch(CURRENT_MOTOR) {
    case MOTOR_1:
      result = MOTOR_1_ADD_CALIBRATION;
    break;
    case MOTOR_2:

    break;
  }
  return result;
}
case(CURRENT_MOTOR){
}




#endif

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
