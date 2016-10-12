//Hyperloop Hover Engine Monitoring System
//Kevin Kha

#include "HEMS.h"

cal_data select_engine(int engine) {
  switch (engine) {
    case 0 : return Engine_0_Calibration_Data;
    case 1 : return Engine_1_Calibration_Data;
    case 2 : return Engine_2_Calibration_Data;
    case 3 : return Engine_3_Calibration_Data;
    case 4 : return Engine_4_Calibration_Data;
    case 5 : return Engine_5_Calibration_Data;
    case 6 : return Engine_6_Calibration_Data;
    case 7 : return Engine_7_Calibration_Data;
  }
}
