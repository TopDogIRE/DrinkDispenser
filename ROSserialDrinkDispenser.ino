// Cathal Mullen

#include <Servo.h>
#include <IRremote.h>

#include <ros.h>
#include <std_msgs/String.h>

// Global!!! oops
ros::NodeHandle nh; 
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

const int IRone = A2;
int IRoneState;

bool writeOut = true;

Servo nozzleServo;
const int nozzleOpen = 70;
const int nozzleClosed = 160;
const int nozzleDelay = 500;

const int pump2Pin1 = 32;
const int pump2Pin2 = 33;
const int pump2Enable = 7;

const int pump1Pin1 = 30;
const int pump1Pin2 = 31;
const int pump1Enable = 6;

int pourSize = 2000;

const int limitSwitchOne = 48;
int limitSwitchOneState;
const int limitSwitchTwo = 47;
int limitSwitchTwoState;

const int driveMotorPin1 = 40;
const int driveMotorPin2 = 41;
const int driveMotorEnable = 5;

void Up(){
  if(writeOut){
    nh.loginfo("Start Up");
  }
  limitSwitchOneState = digitalRead(limitSwitchOne);
  while (limitSwitchOneState != HIGH) {
    digitalWrite(driveMotorPin1, LOW);
    digitalWrite(driveMotorPin2, HIGH);
    limitSwitchOneState = digitalRead(limitSwitchOne);
  }
  motorOff();
  delay(1000);
  if(writeOut){
    nh.loginfo("End UP");
  }
}

void CleanPump(){
  digitalWrite(pump2Pin2, HIGH);
  delay(pourSize*2);
  digitalWrite(pump2Pin2, LOW);
  delay(nozzleDelay);
}

void motorOff(){
  if(writeOut){
    nh.loginfo("Motor Off");
  }
  digitalWrite(driveMotorPin1, LOW);
  digitalWrite(driveMotorPin2, LOW);
}

void Down(){
  if(writeOut){
    nh.loginfo("Start Down");
  }
  limitSwitchTwoState = digitalRead(limitSwitchTwo);
  while (limitSwitchTwoState != HIGH) {
    digitalWrite(driveMotorPin1, HIGH);
    digitalWrite(driveMotorPin2, LOW);
    limitSwitchTwoState = digitalRead(limitSwitchTwo);
  }
  motorOff();
  delay(1000);
  if(writeOut){
    nh.loginfo("End Down");
  }
}

void Glass(){
  if(writeOut){
    nh.loginfo("Start Glass");
  }
  while (digitalRead(IRone) != LOW) {
    nh.loginfo("No Glass present");
  }
  delay(1000);
  if(writeOut){
    nh.loginfo("End Glass");
  }
}

void Open(){
  if(writeOut){
    nh.loginfo("Start Open");
  }
  nozzleServo.write(nozzleOpen);
  delay(nozzleDelay);
  if(writeOut){
    nh.loginfo("End Open");
  }
}

void Closed(){
  if(writeOut){
    nh.loginfo("Start Closed");
  }
  nozzleServo.write(nozzleClosed);
  delay(nozzleDelay);
  if(writeOut){
    nh.loginfo("End Closed");
  }
}

void Drink1(int ratio){
  if(writeOut){
    nh.loginfo("Start Drink 1");
  }
  digitalWrite(pump1Pin1, HIGH);
  delay(pourSize * ratio);
  digitalWrite(pump1Pin1, LOW);
  delay(nozzleDelay);
  if(writeOut){
    nh.loginfo("End Drink 1");
  }
}

void Drink2(int ratio){
  if(writeOut){
    nh.loginfo("Start Drink 2");
  }
  digitalWrite(pump2Pin1, HIGH);
  delay(pourSize * ratio);
  digitalWrite(pump2Pin1, LOW);
  delay(nozzleDelay);
  if(writeOut){
    nh.loginfo("End Drink 2");
  }
}


void setup() {
  pinMode(IRone, INPUT);
  nh.initNode();
  nh.advertise(chatter);

  nozzleServo.attach(53);
  nozzleServo.write(nozzleOpen);

  const byte IR_RECEIVE_PIN = 43;
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);


  // Motor Pins
  pinMode(driveMotorPin1, OUTPUT);
  pinMode(driveMotorPin2, OUTPUT);
  pinMode(driveMotorEnable, OUTPUT);

  // Motor Default
  digitalWrite(driveMotorPin1, LOW);
  digitalWrite(driveMotorPin2, LOW);
  digitalWrite(driveMotorEnable, HIGH);
  
  // Default Position of 
  Open();
  Up();  
}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();  // Enable receiving of the next value
  }
  if (IrReceiver.decodedIRData.command != 0) {
    checkIRcode();
  }
  delay(1000);
  IrReceiver.decodedIRData.command = 0; // Reset value
}

void checkIRcode(){
  nh.loginfo(IrReceiver.decodedIRData.command);
  if(IrReceiver.decodedIRData.command == 69){
    nh.loginfo("Remote Reciever 69 selected");
    Glass();
    Down();
    Closed();
    Drink2(1);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 70){
    nh.loginfo("Remote Reciever 70 selected");
    Glass();
    Down();
    Closed();
    Drink2(2);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 71){
    nh.loginfo("Remote Reciever 71 selected");
    Glass();
    Down();
    Closed();
    Drink1(1);
    Drink2(1);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 68){
    nh.loginfo("Remote Reciever 68 selected");
    Glass();
    Down();
    Closed();
    Drink2(3);
    Open();
    Up();
  }
}
