// Cathal Mullen

#include <Servo.h>
#include <IRremote.h>

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
    Serial.println("Start Up");
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
    Serial.println("End UP");
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
    Serial.println("Motor Off");
  }
  digitalWrite(driveMotorPin1, LOW);
  digitalWrite(driveMotorPin2, LOW);
}

void Down(){
  if(writeOut){
    Serial.println("Start Down");
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
    Serial.println("End Down");
  }
}

void Glass(){
  if(writeOut){
    Serial.println("Start Glass");
  }
  while (digitalRead(IRone) != LOW) {
    Serial.println("No Glass present");
  }
  delay(1000);
  if(writeOut){
    Serial.println("End Glass");
  }
}

void Open(){
  if(writeOut){
    Serial.println("Start Open");
  }
  nozzleServo.write(nozzleOpen);
  delay(nozzleDelay);
  if(writeOut){
    Serial.println("End Open");
  }
}

void Closed(){
  if(writeOut){
    Serial.println("Start Closed");
  }
  nozzleServo.write(nozzleClosed);
  delay(nozzleDelay);
  if(writeOut){
    Serial.println("End Closed");
  }
}

void Drink1(int ratio){
  if(writeOut){
    Serial.println("Start Drink 1");
  }
  digitalWrite(pump1Pin1, HIGH);
  delay(pourSize * ratio);
  digitalWrite(pump1Pin1, LOW);
  delay(nozzleDelay);
  if(writeOut){
    Serial.println("End Drink 1");
  }
}

void Drink2(int ratio){
  if(writeOut){
    Serial.println("Start Drink 2");
  }
  digitalWrite(pump2Pin1, HIGH);
  delay(pourSize * ratio);
  digitalWrite(pump2Pin1, LOW);
  delay(nozzleDelay);
  if(writeOut){
    Serial.println("End Drink 2");
  }
}


void setup() {
  pinMode(IRone, INPUT);
  Serial.begin(9600);

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
  Serial.println(IrReceiver.decodedIRData.command);
  if(IrReceiver.decodedIRData.command == 69){
    Serial.println("Remote Reciever 69 selected");
    Glass();
    Down();
    Closed();
    Drink2(1);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 70){
    Serial.println("Remote Reciever 70 selected");
    Glass();
    Down();
    Closed();
    Drink2(2);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 71){
    Serial.println("Remote Reciever 71 selected");
    Glass();
    Down();
    Closed();
    Drink1(1);
    Drink2(1);
    Open();
    Up();
  }else if(IrReceiver.decodedIRData.command == 68){
    Serial.println("Remote Reciever 68 selected");
    Glass();
    Down();
    Closed();
    Drink2(3);
    Open();
    Up();
  }
}
