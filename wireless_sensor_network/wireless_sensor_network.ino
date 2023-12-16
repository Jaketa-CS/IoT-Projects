#include <SparkFun_CAP1203.h>
#include <SparkFun_CAP1203_Registers.h>
#include <Wire.h>
#include <Servo.h>
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

#define NODE_1 01
#define NODE_2 02
#define NODE_3 03
#include <XBee.h>
XBee xbee = XBee();
#define servoPin 8

Servo servo_;
int angle;

String led_call;
String led_call_OFF;
RF24 radio(10, 9);
RF24Network network(radio);
const uint16_t this_node = 00;   
const uint16_t node01 = NODE_1;      
const uint16_t node02 = NODE_2;
const uint16_t node03 = NODE_3;
void setup()
{
 SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);

  Serial.begin(57600);

}

void loop()
{
  //recive print statements
  network.update();
    while ( network.available() ) {     
    RF24NetworkHeader header;
    unsigned long data;
    network.read(header, &data, sizeof(data)); 
  }


  //send-------
  unsigned long pot_val = analogRead(8);
  unsigned long angle = map(pot_val, 0, 1023, 0, 180); 
  RF24NetworkHeader header2(node01);     
  String input_node =  Serial.readString();

  Serial.println(" ");
  Serial.print("COMMAND: ");
  input_node = Serial.readString();
  
  bool sender = network.write(header2, &angle, sizeof(angle)); 
  

  

}
