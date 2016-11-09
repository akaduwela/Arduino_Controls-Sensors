//Hyperloop Hover Engine Monitoring System
//Linear Actuator Control

//Pin Assignments
#define LINEAR_FEEDBACK 5 //Analog
#define H_BRIDGE_0 7 //Digital
#define H_BRIDGE_1 6 //Digital

//Constraints
#define HEIGHT_MIN 148
#define HEIGHT_MAX 1006
#define PRECISION 5

// Helper functions.
void linear_actuator_initialize();
void linear_actuator_set(int destination);
void pullActuatorUntilStop(int destination);
void pushActuatorUntilStop(int destination);
void stopActuator();
void pushActuator();
void pullActuator();
