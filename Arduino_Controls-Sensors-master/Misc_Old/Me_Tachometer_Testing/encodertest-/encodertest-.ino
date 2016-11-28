//Encoder Test 
//This is a basic code that will demonstrate how to read counts from an encoder. 
//To run this code you will need to have the following hardware connected to your Arduino: 
//A DC Motor 
//A Micro Switch 
//A Break-Beam Sensor 
//LCD Screen (If you want to see output) 
//In addition, you will need one of the Lego pulleys (wheel with holes around it) for use as the encoder wheel 
//This wheel should be attached to a rotating axle, directly or indirectly attached to the motor, and placed 
//near the break-beam sensor so that as it turns it alternately blocks and allows the beam through. 
#include <AFMotor.h> 
#include <SoftwareSerial.h> 
//Include the needed libraries 
#define SwitchPin 0 // micro switch is connected to this pin (pin 0) 
#define LCDTxPin 13 // LCD connected to this pin (pin 13) 
#define DummyRxPin 13 // Not used by LCD Board, can be any unused pin 
#define Interrupt0 2 // break-beam sensor connected to this pin (pin 2, must be pin 2 or 3 since they have hardware interrupts 0 and 1, respectively) 
#define Interrupt1 2 // break-beam sensor connected to this pin (pin 2, must be pin 2 or 3 since they have hardware interrupts 0 and 1, respectively) 
#define SPEED 200 // Set Speed to be used for 
#define LowSPEED 150 
#define MediumSPEED 200
#define HighSPEED 255
#define LowPin 15 // when 4 High choose speed as low  
#define MediumPin 16 //
#define HighPin 17 //
#define AnalogIn 18 //Analog Input

SoftwareSerial mySerial = SoftwareSerial(DummyRxPin, LCDTxPin); //Change Tx and Rx Pins to pins of our choosing 
AF_DCMotor Right_Motor(3, MOTOR34_1KHZ); // create right motor on port 3, 1KHz pwm
AF_DCMotor Left_Motor(4, MOTOR34_1KHZ); // create left motor on port 4, 1KHz pwm
int Bump = 0; 
volatile int ticks = 0; //Count of encoder ticks, volatile is used for speed since it will be in interrupt subroutine 
int oldticks = 0; //Last count of ticks 
int tickGoal = 100; //Number of ticks desired
int waiting = 1; // Waiting state; 1 if waiting, 0 if running
int speedt=HighSPEED;
int val;

void setup(){ 
pinMode(LCDTxPin, OUTPUT);//configuring LCD Screen communication 
mySerial.begin(9600);//configuring LCD Screen communication 
mySerial.print("?f"); //Sends clear screen command to LCD 
delay(20); //Gives the LCD time to execute command 
pinMode(SwitchPin, INPUT); //Makes Switch Pin an input 
digitalWrite(SwitchPin, HIGH); //Enables the pull-up resistor on Switch Pin 
pinMode(Interrupt0, INPUT); //Makes Encoder Pin an input 
pinMode(Interrupt1, INPUT); //Makes Encoder Pin an input 

digitalWrite(Interrupt0, HIGH); //Enables the pull-up resistor on Encoder Pin (Pin 2) 
digitalWrite(Interrupt1, HIGH); //Enables the pull-up resistor on Encoder Pin (Pin 3) 

attachInterrupt(digitalPinToInterrupt(Interrupt0), countTick, FALLING); //Set routine to run (countTick) and interrupt trigger: FALLING (when pin 2 voltage goes from high to low, countTick will run) 
attachInterrupt(digitalPinToInterrupt(Interrupt1), countTick, FALLING); //Set routine to run (countTick) and interrupt trigger: FALLING (when pin 3 voltage goes from high to low, countTick will run) 

pinMode(LowPin, INPUT); //Makes Switch Pin an input 
digitalWrite(LowPin, HIGH); //Enables the pull-up resistor on Switch Pin 
pinMode(MediumPin, INPUT); //Makes Switch Pin an input 
digitalWrite(MediumPin, HIGH); //Enables the pull-up resistor on Switch Pin 
pinMode(HighPin, INPUT); //Makes Switch Pin an input 
digitalWrite(HighPin, HIGH); //Enables the pull-up resistor on Switch Pin 

pinMode(AnalogIn,INPUT);

if (!digitalRead(LowPin)){
  speedt=LowSPEED;
}
else if (!digitalRead(MediumPin)){
  speedt=MediumSPEED;
}
else{
  speedt=HighSPEED;
}

Right_Motor.setSpeed(speedt);
Left_Motor.setSpeed(speedt);

val= analogRead(AnalogIn);

tickGoal=val;

//mySerial.print("?f");
//mySerial.print("?x00?y0");//move cursor to beginning of screen 
//mySerial.print(digitalRead(LowPin)); 
//while(digitalRead(SwitchPin)){
//  //
//}


} 

void loop(){ 
  if (waiting){ // If in waiting state
    mySerial.print("?x00?y0");//move cursor to beginning of screen 
    mySerial.print("Bump to Begin..."); 
    Bump = !digitalRead(SwitchPin);
    if (Bump){ // if switch is pressed
      waiting = 0; // stop waiting
      ticks = 0; // reset ticks and old ticks
      oldticks = 0; 
      mySerial.print("?f"); // clear the screen and display counts 
      mySerial.print("Counts:"); 
      DriveForward(); // start motor
    }
  }
  else { // if not in waiting state
    if (ticks != oldticks){ 
      //reprint count if it has changed 
      mySerial.print("?x00?y1"); 
      mySerial.print(ticks); 
      oldticks=ticks; 
    } 
    if (ticks >= tickGoal){ // If tick goal has been reached
      waiting = 1; // Return to waiting state
      Left_Motor.run(RELEASE); //Kill Motor 
      Right_Motor.run(RELEASE); //Kill Motor
    }
  } 
} 

//countTick runs whenver interrupt is triggered, increments ticks each time it is called 
void countTick() 
{ 
++ticks;
}

void DriveForward(){
  Right_Motor.run(FORWARD);
  Left_Motor.run(FORWARD);
}
