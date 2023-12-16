#include <MsTimer2.h>
int count = 0;
//pycharm base station: S to start sampling

char incomingByte ; //Variable to store the incoming byte
unsigned long init_time = 0;
int setTime = 20;
int stamp;

//nodes---------
int id = 1;
//int id = 0;
//int id = 1;
//int id = 3;
//----------------

int blue_LED = 10;
int counter = 0;
unsigned long t;
bool ready;
int backoff;

void clocky() { //interrupt
  ready = true;
 
  count = analogRead(A0);  // read the value from the sensor

  Serial.print(id);
  Serial.print(",");
  Serial.print(counter);
  Serial.print(",");
  Serial.println(count); // print the sensor readings


  //blink
  counter++;
  if (counter == 50)
  {
    digitalWrite(blue_LED, HIGH);
  }
  else if (counter == 100)
  {
    counter = 0;
    digitalWrite(blue_LED, LOW);
  }
  t = stamp;
}
void setup()
{
  Serial.begin(57600);
  MsTimer2::set(setTime, clocky);
  pinMode(blue_LED, OUTPUT);
  pinMode(A0, INPUT);

}

void loop()
{
  if (Serial.available() > 0) {
    
    incomingByte = Serial.read();//Read the incoming byte

    if (incomingByte == 'R') //START
    {
      Serial.println(count);
      MsTimer2::start();//start sampling (all nodes)
    }
    else if (incomingByte == 'T') //STOP
    {
      MsTimer2::stop();
    } else if (incomingByte == 'S') //SYNC
    {
      MsTimer2::stop();
      MsTimer2::start();
    }

  }

}

void serialEvent() {
  //ready/backoff
  if (ready) {
    ready = false;
    int backOff = id * 3; //node 2 delay 3ms, node 3 delay 6ms
    delay(backOff);
  }
}
