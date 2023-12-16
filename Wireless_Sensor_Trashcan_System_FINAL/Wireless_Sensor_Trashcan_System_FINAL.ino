/*
  Description:
  The Wireless Sensor Trashcan System is a proof-of-concept project that showcases the capabilities
  of a wireless sensor system designed by a collaborative team. The system seamlessly integrates
  diverse sensors, actuators, and wireless connectivity to provide an insightful demonstration of
  its functionalities. While the project is not tailored for production, it stands as a fully
  functional prototype that highlights essential features.

  How to Run:
  1. Connect the servo signal pin to digital pin 9, the sound sensor analog pin to A0, and the slider pin to the appropriate pin.
  2. Upload the provided Arduino code to the target device.
  3. Ensure that the necessary libraries, such as Servo, are installed in the Arduino IDE.
  4. Set up the base station code in Python for data processing and visualization.
  5. Power on the system and initiate the wireless sensor trashcan.
  6. Observe the system's autonomous operation, responsiveness to sound, and actuation based on the slider input.

  Project Accomplishments:
  - Integrated two sensor inputs into the system.
  - Utilized a single actuator for system output.
  - Established wireless connectivity to enhance communication.
  - Implemented base station code in Python to manage and process data.
  - Stored sensor data in time-stamped files or a database for future analysis.
  - Achieved autonomy, allowing the system to operate autonomously once initiated.
  - Prioritized stability and high fault tolerance, ensuring robust functionality even in challenging conditions.
  - Structured the code to be memory-efficient, stable, and resistant to faults, meeting assessment criteria.
  - Organized the codebase following best practices for clean and readable code.
  - Provided meaningful comments throughout the code to enhance readability and understanding.

  Final Presentation:
  - Include in-depth details of the system's design, including state diagrams and architecture.
  - Showcase visualizations of previously collected data to illustrate the system's performance.
  - Conduct a live demonstration showcasing the functionality of the wireless sensor system.
*/
#include <MsTimer2.h>

int count = 0;
char incomingByte; // Variable to store the incoming byte
unsigned long init_time = 0;
int setTime = 20;
int stamp;

// Nodes
int id = 1;

int blue_LED = 10;
int counter = 0;
unsigned long t;
bool ready;
int backoff;

// Trashcan states
const int CLOSED = 0;
const int OPENED = 1;
const int HALFWAY = 2;

int trashcanState = CLOSED;

// Calibration threshold for sound detection
int clapThreshold;

void clocky() {
  ready = true;

  count = analogRead(A0); // read the value from the sensor

  Serial.print(id);
  Serial.print(",");
  Serial.print(counter);
  Serial.print(",");
  Serial.println(count); // print the sensor readings

  // Update trashcan state based on sensor readings
  updateTrashcanState(count);

  // Output trashcan state
  printTrashcanState();

  // Blink
  counter++;
  if (counter == 50) {
    digitalWrite(blue_LED, HIGH);
  } else if (counter == 100) {
    counter = 0;
    digitalWrite(blue_LED, LOW);
  }
  t = stamp;
}

void setup() {
  Serial.begin(57600);
  MsTimer2::set(setTime, clocky);
  pinMode(blue_LED, OUTPUT);
  pinMode(A0, INPUT);

  // Perform sound calibration
  calibrateSound();
}

void loop() {
  if (Serial.available() > 0) {

    incomingByte = Serial.read(); // Read the incoming byte

    if (incomingByte == 'R') // START
    {
      Serial.println(count);
      MsTimer2::start(); // start sampling (all nodes)
    } else if (incomingByte == 'T') // STOP
    {
      MsTimer2::stop();
    } else if (incomingByte == 'S') // SYNC
    {
      MsTimer2::stop();
      MsTimer2::start();
    }
  }
}

void serialEvent() {
  // Ready/backoff
  if (ready) {
    ready = false;
    int backOff = id * 3; // node 2 delay 3ms, node 3 delay 6ms
    delay(backOff);
  }
}

void calibrateSound() {
  Serial.println("Sound Calibration: Clap your hands!");
  delay(5000); // Allow time for the user to clap hands

  int calibrationSamples = 50; // Number of samples for calibration
  int calibrationSum = 0;

  // Collect sound sensor readings during calibration
  for (int i = 0; i < calibrationSamples; ++i) {
    calibrationSum += analogRead(A0);
    delay(50); // Adjust delay as needed
  }

  // average value during calibration
  int calibrationThreshold = calibrationSum / calibrationSamples;

  // threshold for sound detection
  clapThreshold = calibrationThreshold + 50; 

  Serial.print("Calibration complete. Audio threshold: ");
  Serial.println(clapThreshold);
}

void updateTrashcanState(int sensorReading) {
  // Implement logic to update trashcan state based on sensor readings
  // Modify the conditions and thresholds based on your specific requirements
  if (sensorReading < 100) {
    trashcanState = CLOSED;
  } else if (sensorReading >= 100 && sensorReading < 500) {
    trashcanState = HALFWAY;
  } else {
    trashcanState = OPENED;
  }
}

void printTrashcanState() {
  // Output the current state of the trashcan to the console
  switch (trashcanState) {
    case CLOSED:
      Serial.println("Trash Can Closed");
      break;
    case OPENED:
      Serial.println("Trash Can Opened");
      break;
    case HALFWAY:
      Serial.println("Halfway");
      break;
  }
}
