./*
  Sample code to control the position of an actuator with potentiometer feedback using a MegaMoto.

  The main loop of this program checks the potentiometer, and moves the actuator accordingly. 

  Written by Progressive Automations

  This example code is in the public domain.
*/

const int feedback = A0; //potentiometer from actuator
const int pot = A1; //pot from throttle

const int R1 = 2;
const int R2 = 3;


int actMax = 148; //extended Actuator; based off measured value at Max limit (convted to 10 bit scale)
int actMin = 1006; //retracted Actuator;  based off measured values 

int potMin = 0;
int potMax = 1023;

int precision = 5;//how close to final value to get
int checkingInterval = 50;//how often position is checked (milliseconds)

int rawcurrentPosition = 0;
int currentPosition = 0;
int rawdestination = 0;
int destination = 0;
int difference = 0;//values for knowing location

void setup()
{
  pinMode(feedback, INPUT);//feedback from actuator
  pinMode(pot, INPUT);//feedback from potentiometer
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  digitalWrite(R1,HIGH);
  digitalWrite(R2,HIGH);
  Serial.begin(9600);
}

void loop()
{   
    destination = getDestination(); 
    currentPosition = analogRead(feedback);//check where you are
    Serial.print("Position    ");
    Serial.println(analogRead(feedback));
    difference = destination - currentPosition;//find out how far you are from the destination
    if (currentPosition < destination) pullActuatorUntilStop(destination);// choose what action to take
    else if (currentPosition > destination) pushActuatorUntilStop(destination);
    else if (difference < precision && difference > -precision) stopActuator();
}//end void loop
/*******************************************************************/
/********************* Function Start *****************************/
/*******************************************************************/
/****************************************/
/* Function: getDestination()          */
/*                                      */
/* Parameters: none                     */
/*                                      */
/* Return:     int                      */
/*                                      */
/* Description:                         */
/*   Map potentiometer reading to       */
/*   actuator range.                    */
/****************************************/
int getDestination()
{
    rawdestination = analogRead(pot);//read the potentiometer to get the destination
    destination = map(rawdestination, potMin,potMax,actMin,actMax);//convert the potentiometer feedback to match the actuator
    return(destination);
}//end getDestination
/****************************************/
/* Function: pushActuatorUnilStop       */
/*                                      */
/* Parameters: int; desitnation         */
/*                                      */
/* Return:     void                     */
/*                                      */
/* Description:                         */
/*   Pushes Actuator until stop         */
/*   destination reached.               */
/****************************************/
void pushActuatorUntilStop(int destination)
{
  destination = getDestination();
  int temp = analogRead(feedback); 
  difference = destination - temp;//check difference to see if continue moving, or stop

  while (difference > precision || difference < -precision)
  {
    destination = getDestination();
    temp = analogRead(feedback); //continue checking difference
    difference = destination - temp;
    pushActuator();
  }//end while
  
  delay(25);
  stopActuator();
}//end pushActuatorUntilStop
/****************************************/
/* Function:   pullActuatorUnilStop     */
/*                                      */
/* Parameters: int; desitnation         */
/*                                      */
/* Return:     void                     */
/*                                      */
/* Description:                         */
/*   Pulls Actuator until stop          */
/*   destination reached.               */
/****************************************/
void pullActuatorUntilStop(int destination)
{
  destination = getDestination();
  int temp = analogRead(feedback); //check difference to see if continue moving, or stop
  difference = destination - temp;

  while (difference > precision || difference < -precision)
  {
    destination = getDestination();
    temp = analogRead(feedback); //continue checking difference
    difference = destination - temp;
    pullActuator();
  }//end while
  
  delay(25);
  stopActuator();
}//end pullActuatorUntilStop
/****************************************/
/* Function:   stopActuator             */
/*                                      */
/* Parameters: none                     */
/*                                      */
/* Return:     void                     */
/*                                      */
/* Description:                         */
/*   Sends stop signal to actuator.     */
/*                                      */
/****************************************/
void stopActuator()
{
 digitalWrite(R1,HIGH);
 digitalWrite(R2,HIGH);
}//end stopActuator
/****************************************/
/* Function:   pushActuator             */
/*                                      */
/* Parameters: none                     */
/*                                      */
/* Return:     void                     */
/*                                      */
/* Description:                         */
/*   Sends push signal to actuator.     */
/*                                      */
/****************************************/
void pushActuator()
{ 
  digitalWrite(R1,HIGH);
  digitalWrite(R2,LOW);
}//end pushActuator
/****************************************/
/* Function:   pullActuator             */
/*                                      */
/* Parameters: none                     */
/*                                      */
/* Return:     void                     */
/*                                      */
/* Description:                         */
/*   Sends pull signal to actuator.     */
/*                                      */
/****************************************/
void pullActuator()
{
  digitalWrite(R1,LOW);
  digitalWrite(R2,HIGH);
}//end pullActuator


