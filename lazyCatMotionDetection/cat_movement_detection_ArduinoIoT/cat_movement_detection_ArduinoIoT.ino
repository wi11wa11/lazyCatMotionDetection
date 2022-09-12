//-------- Interactive System Challenge : lazy cat ---------
//-------- William Wallis s3773723 -------------------------

#include "thingProperties.h" //arduino IoT cloud variable

//-------sensor and led variables
int ledPin = 2; //led pin
int pirPin = 13; //PIR motion sensor pin
int buttonPin = 15; //TEMPORARY FIX FOR PIR NOT WORKING //replace with pirPin

int pirState = 0; //PIR motion sensor state variable
//int pirVal = 0; //PIR motion sensor value   //---> !!!!arduinoIoT variable!!!!

//-------- movement variables over time
//int moveCounter = 0;    //---> !!!!arduinoIoT variable!!!!
unsigned long lastMillis;  //the last millis reading
unsigned long currentMillis; //current time reading
const unsigned long timePeriod = 20000; //time period (30sec)

void setup() {
  lastMillis = millis(); //starting value of millis

  pinMode(ledPin, OUTPUT); //configures the ledPin to output, as we are sending info out to the pin
  pinMode(pirPin, INPUT); //configures PIR motion pin to input
  pinMode(buttonPin, INPUT); //TEMPORARY while PIR not working

  Serial.begin(9600);
  //delay(1500); //no delay so arduinoIoT doesn't break

  initProperties(); //arduino IoT setup
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  currentMillis = millis(); //current millis value

  ArduinoCloud.update(); //arduino IoT cloud update

  //---------what happens when motion is detected
  pirVal = digitalRead(buttonPin); //reads motion sensor pin and sets motion state, 1 (movement), or 0 (no movement) 
                                    //TEMPORARILY READING BUTTON while PIR sensor not working!!!!

  if (pirVal == 1) {         // if motion is detected do this
    digitalWrite(ledPin, 1);  // turn LED ON
    if (pirState == 0) { //if pirState == 0 do this
      Serial.println("Movement began"); //prints when the sensor state is changed to get beginning and end of movement
      moveCounter++; //adds 1 to the moveCounter value
      pirState = 1; //sets the pirState to 1
    }
    Serial.println("Cat movement detected!!! omg so active!"); //prints a line in serial monitor to tell if movement is detected

    //servo code went here

  } else {
    digitalWrite(ledPin, 0); // turn LED OFF if we have no motion
    if (pirState == 1) {  //if the pirState == 1 do this
      Serial.println("Movement ended"); //prints when movement has ended
      pirState = 0; //sets the pirState back to 0
    }
  }

  //---------- graphing movement over time
  if (currentMillis - lastMillis >= timePeriod) { //if the current time elapsed is greater than (timePeriod) do this
    Serial.print("moveCounter value = ");
    Serial.println(moveCounter); //prints the moveCounter value
    moveCounter = 0; //resets the moveCounter back to 0
    lastMillis = currentMillis; //sets the current time to the last elapsed time
  }
}
