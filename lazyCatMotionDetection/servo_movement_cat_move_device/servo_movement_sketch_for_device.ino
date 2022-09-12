bool catMovement = true;

#include "thingProperties.h"

#include <ESP32Servo.h> //servo variables 
Servo myservo;
int pos = 0;
int servoPin = 12;
int movementRange = 30;

int ledPin = 2;

//bool catMoveState = 0; //---> !!!!arduino IoT variable!!!

void setup() {
  Serial.begin(9600);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  myservo.attach(servoPin); //servo attachment

  pinMode(servoPin, OUTPUT); //configures to output
  pinMode(ledPin, OUTPUT); //configures to output
}

void loop() {
  ArduinoCloud.update();

  if (catMovement == true) {
    digitalWrite(ledPin, 1);
    if (catMoveState == 0) {
      Serial.println("catMoving! 😸");
      catMoveState = 1;
    }
    //------------ servo movement
    for (pos = 0; pos <= movementRange; pos += 2) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = movementRange; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  } else {
    digitalWrite(ledPin, 0);
    if (catMoveState == 1) {
      Serial.println("catInactive!!! 🙀");
      catMoveState = 0;
    }
  }
}
