// Jake T -- NUMBER GUESS -- IoT 

int magicNumber = 20; //Magic number to be guessed
int guess;

void setup() {
  Serial.begin(9600); //Serial baud rate 9600 <- 57600
  
  // Display the magic number (for testing purposes)
  Serial.print("[The number is: "); 
  Serial.print(magicNumber);
  Serial.println("]");
  Serial.println("--------------------------"); 
  
  //Prompt user to enter an int
  Serial.println("GUESS THE NUMBER!"); 
  Serial.println("ENTER A NUMBER BETWEEN 0 AND 100:");
}

void loop() {
  // Wait for user input
  while (!Serial.available());
  
  //Read user's guess
  int guess = Serial.parseInt();
  
  //Ensure the guess is within the valid range
  if (guess < 0 || guess > 100) {
    Serial.println("INVALID ENTRY! NUMBER MUST BE BETWEEN 0 AND 100");
  } else if (guess < magicNumber) {
    //User's guess is too low
    Serial.print(guess);
    Serial.println(" = Too low. (Try again)\n");
  } else if (guess > magicNumber) {
    //User's guess is too high
    Serial.print(guess);
    Serial.println(" = Too high. (Try again)\n");
  } else {

    //User guessed correctly
    Serial.println(":) Congratulations! You guessed it!");
    
    // Halt the program 
    while (true);
  }
}
