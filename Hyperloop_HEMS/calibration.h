// Calibration data for the engine sensors.

#define ENGINE_NUMBER	0	// Select the engine this code is running on.

/* ------------------------------------------------ TEMPLATE */
typedef struct {
  //beta Constants (Default = 3380)
  int beta_coils_front;
  int beta_coils_back;
  int beta_interior_wall_right;
  int beta_interior_wall_left;
  //int beta_thermistor_4;
  //int beta_thermistor_5;

  //lnrinf Constants (Default = -2.126):
  float offset_coils_front;
  float offset_coils_back;
  float offset_interior_wall_right;
  float offset_interior_wall_left;
  //float offset_thermistor_4;
  //float offset_thermistor_5;
} cal_data;

/* ------------------------------------------------ ENGINE 0 */
#if (ENGINE_NUMBER == 0)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 0

/* ------------------------------------------------ ENGINE 1 */
#if (ENGINE_NUMBER == 1)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 1

/* ------------------------------------------------ ENGINE 2 */
#if (ENGINE_NUMBER == 2)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 2

/* ------------------------------------------------ ENGINE 3 */
#if (ENGINE_NUMBER == 3)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 3

/* ------------------------------------------------ ENGINE 4 */
#if (ENGINE_NUMBER == 4)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 4

/* ------------------------------------------------ ENGINE 5 */
#if (ENGINE_NUMBER == 5)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 5

/* ------------------------------------------------ ENGINE 6 */
#if (ENGINE_NUMBER == 6)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 6

/* ------------------------------------------------ ENGINE 7 */
#if (ENGINE_NUMBER == 7)
const cal_data Engine_Calibration_Data = {
  .beta_coils_front = 3380,
  .beta_coils_back = 3380,
  .beta_interior_wall_right = 3380,
  .beta_interior_wall_left = 3380,
  //int beta_thermistor_4 = 3380,
  //int beta_thermistor_5 = 3380,

  .offset_coils_front = -2.126,
  .offset_coils_back = -2.126,
  .offset_interior_wall_right = -2.126,
  .offset_interior_wall_left = -2.126,
  //.offset_thermistor_4 = -2.126,
  //.offset_thermistor_5 = -2.126,
};
#endif // ENGINE_NUMBER == 7
