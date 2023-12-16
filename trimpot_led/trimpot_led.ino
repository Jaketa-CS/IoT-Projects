#include <MsTimer2.h>

int val;
bool ok = false;

const int potPin = A0;
const int ledPin = 2; // Use the first LED pin

void fx() {
  val = analogRead(potPin);
  ok = true;
}

void setup() {
  Serial.begin(57600);
  //Set up a timer interrupt to call the 'fx' function every 10 milliseconds
  MsTimer2::set(10, fx);
  MsTimer2::start();

  //Set ledPin as an output pin to control the LED
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (ok) {
    Serial.println(val);
    ok = false;

    //Map the potentiometer value to the LED brightness (0-255)
    int brightness = map(val, 0, 1023, 0, 255);
    analogWrite(ledPin, brightness);
  }
}
