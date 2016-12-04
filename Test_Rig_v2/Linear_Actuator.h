//Hyperloop Hover Engine Management System
//Linear Actuator Control

//Pin Assignments
#define LINEAR_FEEDBACK 3 //Analog
#define H_BRIDGE_0 4 //Digital
#define H_BRIDGE_1 3 //Digital

//Constraints
#define HEIGHT_MIN 4.10
#define HEIGHT_MAX 54.9
#define FEEDBACK_MIN 166 //corresponds to the most retracted state of the linear actuator (should be 54.9mm)
#define FEEDBACK_MAX 1006 //corresponds to the most extended state of the linear actuator (should be 4.1mm)
#define PRECISION 5

// Helper functions.
void linear_actuator_initialize();
void linear_actuator_set(float height_value);
void pullActuatorUntilStop(int destination);
void pushActuatorUntilStop(int destination);
void stopActuator();
void pushActuator();
void pullActuator();
