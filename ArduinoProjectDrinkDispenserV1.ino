#include <Servo.h>

const int IRone = A2;
int IRoneState;

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
  limitSwitchOneState = digitalRead(limitSwitchOne);
  while (limitSwitchOneState != HIGH) {
    digitalWrite(driveMotorPin1, LOW);
    digitalWrite(driveMotorPin2, HIGH);
    limitSwitchOneState = digitalRead(limitSwitchOne);
  }
  motorOff();
  delay(5000);
}

void motorOff(){
  digitalWrite(driveMotorPin1, LOW);
  digitalWrite(driveMotorPin2, LOW);
}

void Down(){
  limitSwitchTwoState = digitalRead(limitSwitchTwo);
  while (limitSwitchTwoState != HIGH) {
    digitalWrite(driveMotorPin1, HIGH);
    digitalWrite(driveMotorPin2, LOW);
    limitSwitchTwoState = digitalRead(limitSwitchTwo);
  }
  motorOff();
  delay(5000);
}

void Glass(){
  while (digitalRead(IRone) != LOW) {
    Serial.println("No Glass present");
  }
  delay(1000);
}

void Open(){
  nozzleServo.write(nozzleOpen);
  delay(nozzleDelay);
}

void Closed(){
  nozzleServo.write(nozzleClosed);
  delay(nozzleDelay);
}

void Drink1(){
  digitalWrite(pump1Pin1, HIGH);
  delay(pourSize);
  digitalWrite(pump1Pin1, LOW);
  delay(nozzleDelay);
}

void Drink2(){
  digitalWrite(pump2Pin1, HIGH);
  delay(pourSize);
  digitalWrite(pump2Pin1, LOW);
  delay(nozzleDelay);
}

void setup() {
  pinMode(IRone, INPUT);
  Serial.begin(9600);
  nozzleServo.attach(42);

  // Motor Pins
  pinMode(driveMotorPin1, OUTPUT);
  pinMode(driveMotorPin2, OUTPUT);
  pinMode(driveMotorEnable, OUTPUT);

  // Motor Default
  digitalWrite(driveMotorPin1, LOW);
  digitalWrite(driveMotorPin2, LOW);
  digitalWrite(driveMotorEnable, HIGH);

  Open();
  Up();
  Glass();
  Down();
  Closed();
  Drink2();
  Open();
  Up();
}

void loop() {
  Serial.println("END");
}
