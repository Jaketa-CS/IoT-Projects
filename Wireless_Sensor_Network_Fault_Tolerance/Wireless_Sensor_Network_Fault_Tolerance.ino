/*
  Wireless Sensor Network Fault Tolerance 
  Author: Jake Teeter

  Description:
  This project simulates a wireless sensor network with fault-tolerance mechanisms!
  Includes: disjoint multipath routing, braided multipath routing, retransmission, and replication.

 How to Run:
  1. Upload this to Arduino board.
  2. Open the serial monitor to view simulation output.
  3. The program simulates data transmission from Node 1 to Node 3.
  4. Explore different fault-tolerance mechanisms by uncommenting the corresponding function in sendData.
  5. Observe the simulated behavior and outputs for each fault-tolerance mechanism.

   Notes:
  - Fault tolerance is crucial in wireless sensor networks to ensure reliable data transmission.
  - Multipath routing provides redundancy but comes with trade-offs like increased power consumption.
  - Disjoint multipath routing creates alternative paths that are disjoint with the primary path.
  - Braided multipath routing overlays alternate paths partially on the primary path.
  - Retransmission involves resending data packets using different paths to minimize interruptions.
  - Replication introduces redundancy by transmitting multiple copies of the same packet along different paths.
  - Each fault-tolerance mechanism has its advantages and drawbacks, such as energy consumption and overhead.

*/

#include <Wire.h>

// Constants
const int numNodes = 3;
const int maxHops = 5;

// Node structure
struct Node {
  int id;
  int batteryLevel;
  bool isActive;
};

// Function prototypes
void sendData(int source, int destination, String data);
void disjointMultipathRouting(int source, int destination);
void braidedMultipathRouting(int source, int destination);
void retransmission(int source, int destination, String data);
void replication(int source, int destination, String data);

  // Initialize nodes (global)
  Node nodes[numNodes];

// Main setup
void setup() {
  Serial.begin(9600);

  for (int i = 0; i < numNodes; ++i) {
    nodes[i].id = i + 1;
    nodes[i].batteryLevel = 100;
    nodes[i].isActive = true;
  }
}

// Main loop --------------------------------------------------------------
void loop() {
  // Simulate data generation at node 1
  sendData(1, 3, "SensorData123");
  delay(5000); // Simulate time delay between data transmissions
}
//--------------------------------------------------------------------------


// Simulate sending data from source to destination
void sendData(int source, int destination, String data) {
  replication(source, destination, data);
}

void disjointMultipathRouting(int source, int destination) {
  // Implement disjoint multipath routing logic here
  Serial.print("Disjoint Multipath Routing from Node ");
  Serial.print(source);
  Serial.print(" to Node ");
  Serial.println(destination);

  // Simulate path discovery and transmission
  Serial.println("Path 1: [Node 1 -> Node 2 -> Node 3]");
  Serial.println("Path 2: [Node 1 -> Node 4 -> Node 3]");
}

void braidedMultipathRouting(int source, int destination) {
  // Implement braided multipath routing logic here
  Serial.print("Braided Multipath Routing from Node ");
  Serial.print(source);
  Serial.print(" to Node ");
  Serial.println(destination);

  // Simulate path discovery and transmission
  Serial.println("Path 1: [Node 1 -> Node 2 -> Node 3]");
  Serial.println("Path 2: [Node 1 -> Node 4 -> Node 3]");
}

void retransmission(int source, int destination, String data) {
  // Implement retransmission logic here
  Serial.print("Retransmission from Node ");
  Serial.print(source);
  Serial.print(" to Node ");
  Serial.println(destination);

  // Simulate retransmission attempts
  for (int attempt = 1; attempt <= 3; ++attempt) {
    Serial.print("Attempt ");
    Serial.print(attempt);
    Serial.print(": ");
    Serial.println(data);
    delay(1000); // Simulate time delay between attempts
  }
}

void replication(int source, int destination, String data) {
  // Implement replication logic here
  Serial.print("Replication from Node ");
  Serial.print(source);
  Serial.print(" to Node ");
  Serial.println(destination);

  // Simulate transmitting multiple copies of the same packet
  for (int copy = 1; copy <= 3; ++copy) {
    Serial.print("Copy ");
    Serial.print(copy);
    Serial.print(": ");
    Serial.println(data);
    delay(500); // Simulate time delay between copies
  }
}