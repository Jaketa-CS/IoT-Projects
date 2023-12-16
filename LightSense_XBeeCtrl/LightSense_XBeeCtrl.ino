/*
  Jake Teeter
   Project: XBee LED Controller
   Summary: This project enables wireless control of LEDs using XBee radios.
            The system samples a photoresistor, wirelessly transmits the data,
            and responds to user commands ('B' for blue, 'R' for red, 'Y' for yellow, 'G' for green)
            to toggle the corresponding LEDs.
*/
#include <Wire.h>
#include <XBee.h>

// 4 LED pins
const int blueLedPin = 8;
const int redLedPin = 9;
const int yellowLedPin = 10;
const int greenLedPin = 11;

const int photoresistorPin = A0;
XBee xbee = XBee();

void setup() {
  // Initialize serial communication
  Serial.begin(57600);
  // Initialize XBee
  xbee.begin(Serial);

  // Set LED pins as outputs
  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  // Read photoresistor value
  int photoresistorValue = analogRead(photoresistorPin);

  // Create an XBee packet to transmit photoresistor data
  XBeeTx(photoresistorValue);

  // Check for incoming XBee packets
  checkXBeeRx();
}

void XBeeTx(int data) {
  // Create an XBee packet
  ZBTxRequest zbTx = ZBTxRequest(0xFFFF, ZB_BROADCAST_ADDRESS, (uint8_t*)&data, sizeof(data));

  // Send the packet
  xbee.send(zbTx);
}

void checkXBeeRx() {
  // Create an XBee response object
  XBeeResponse response = XBeeResponse();

  // Wait for a response
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    // Get the response
    xbee.getResponse().getRx16Response(response);

    // Process the received data
    processData(response);
  }
}

void processData(XBeeResponse response) {
  // Extract the received data
  uint8_t* data = response.getData();
  int command = *data;

  // Toggle LEDs based on the received command
  switch (command) {
    case 'B':
      toggleLED(blueLedPin);
      break;
    case 'R':
      toggleLED(redLedPin);
      break;
    case 'Y':
      toggleLED(yellowLedPin);
      break;
    case 'G':
      toggleLED(greenLedPin);
      break;
    default:
      // Handle unknown command
      Serial.println("Unknown command!!!");
      break;
  }
}

void toggleLED(int ledPin) {
  // Toggle the specified LED
  digitalWrite(ledPin, !digitalRead(ledPin));
}
