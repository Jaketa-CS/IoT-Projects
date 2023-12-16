#include <SparkFun_CAP1203.h>
#include <SparkFun_CAP1203_Registers.h>
#include <Wire.h>
#include <Servo.h>

CAP1203 sensor;  // Create an instance of the CAP1203 library
Servo _servo;    // Create an instance of the Servo library

bool touch_detect = false;  //Flag to prevent repeated touch detection

void setup() {
  Wire.begin();       //Initialize I2C communication
  Serial.begin(57600); //Initialize serial communication for debugging
  sensor.begin();      //Initialize the CAP1203 sensor

  _servo.attach(8);    //Attach the servo to pin 8

  // Check if the CAP1203 sensor is connected
  if (sensor.begin() == false) {
    Serial.println("NO CONNECTION");
    while (1);  //Hang the program if there's no connection
  } else {
    Serial.println("\nCONNECTED: ");
  }
}

void loop() {
  // Touch detection logic
  if (touch_detect == true) {
    return;  //If touch is already detected, exit the loop
  } else {
    // 0 Degrees-----------------------------------------------------------------
    if (sensor.isLeftTouched() == true) {
      touch_detect = true;
      Serial.println("0° rotation");

      _servo.write(0);  // Set the servo angle to 0 degrees
      analogWrite(9, map(0, 0, 1023, 0, 255));  // Map and set LED brightness

      touch_detect = false;  // Reset touch detection flag
      delay(150);            // Delay to avoid repeated detection
    }

    // 90 Degrees-----------------------------------------------------------------
    if (sensor.isMiddleTouched() == true) {
      touch_detect = true;
      Serial.println("90° rotation");

      _servo.write(90);  //Set  servo angle to 90 degrees
      analogWrite(9, map(90, 0, 1023, 0, 255));  //Map and set LED brightness

      touch_detect = false;  //Reset touch detection flag
      delay(150);            //Delay to avoid repeated detection
    }

    // 180 Degrees-----------------------------------------------------------------
    if (sensor.isRightTouched() == true) {
      touch_detect = true;  
      Serial.println("180° rotation");

      _servo.write(180);  //Set  servo angle to 180 degrees
      analogWrite(9, map(180, 0, 1023, 0, 255));  //Map and set LED brightness

      touch_detect = false;  //Reset touch detection flag
      delay(150);            //Delay to avoid repeated detection
    }
    delay(150);  //Delay to prevent rapid touch detection
  }
}
